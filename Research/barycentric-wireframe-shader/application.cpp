#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Umfeld.h"
#include "PShader.h"
#include "ShaderSource.h"
#include "VertexBuffer.h"
#include "Geometry.h"

// see https://tchayen.github.io/posts/wireframes-with-barycentric-coordinates

using namespace umfeld;

ShaderSource shader_source_barycentric_wireframe{
    .vertex   = R"(
layout(location = 0) in vec4 aPosition;
layout(location = 1) in vec4 aNormal;
layout(location = 2) in vec4 aColor;
layout(location = 3) in vec3 aTexCoord;
layout(location = 4) in uint a_transform_id;

layout(std140) uniform Transforms {
    mat4 uModel[256];
};

out vec4 vColor;
out vec2 vTexCoord;
out vec3 v_barycentric;

uniform mat4 u_model_matrix;
uniform mat4 u_projection_matrix;
uniform mat4 u_view_matrix;
uniform mat4 u_view_projection_matrix;

void main() {
    mat4 M;
    if (a_transform_id == 0u) {
        M = u_model_matrix;
    } else {
        M = uModel[a_transform_id - 1u];
    }
    gl_Position = u_projection_matrix * u_view_matrix * M * aPosition;
    vColor = aColor;
    vTexCoord = aTexCoord.xy;
    v_barycentric = aNormal.xyz;
}
    )",
    .fragment = R"(
in vec4 vColor;
in vec2 vTexCoord;
in vec3 v_barycentric;

out vec4 FragColor;

uniform float line_width;
uniform float feather_width;

uniform sampler2D u_texture_unit;

float edgefactor(vec3 bary, float width) {
    vec3 d = fwidth(bary);
    vec3 a3 = smoothstep(d * (width - 0.5), d * (width + 0.5), bary);
    return 1.0 - min(min(a3.x, a3.y), a3.z);
}

float edgefactor_feather(vec3 bary, float width, float feather) {
    float w1 = width - feather * 0.5;
    vec3 d = fwidth(bary);
    vec3 a3 = smoothstep(d * w1, d * (w1 + feather), bary);
    return 1.0 - min(min(a3.x, a3.y), a3.z);
}

void main() {
    float alpha = edgefactor(v_barycentric, line_width);
    //float alpha = edgefactor_feather(v_barycentric, line_width, feather_width);
    alpha = clamp(alpha, 0.0, 1.0);
    //FragColor = texture(u_texture_unit, vTexCoord) * vec4(vColor.rgb, vColor.a * alpha);
    FragColor = vec4(vColor.rgb, vColor.a * alpha);
}
    )"};

PShader*      shader_barycentric_wireframe;
VertexBuffer* mesh_sphere;
int           frame_counter = 0;

void settings() {
    size(1024, 768);
    // antialiasing     = 8;
    // render_to_buffer = false;
    // retina_support   = true;
}

void setup() {
    shader_barycentric_wireframe = loadShader(shader_source_barycentric_wireframe.get_vertex_source(),
                                              shader_source_barycentric_wireframe.get_fragment_source());
    shader_barycentric_wireframe->set_auto_update_uniforms(true); // NOTE this attempts to update uniforms whenever a shape is drawn

    /* use convenience function to generate a sphere */
    std::vector<Vertex> sphere_vertices;
    generate_sphere(sphere_vertices, 10, 10);

    /* compile list of vertices with attributes like color */
    const glm::vec4 scale{height / 3.0f, height / 3.0f, height / 3.0f, 1.0f};
    int             cycle = 0;
    glm::vec4       color;
    for (auto& vertex: sphere_vertices) {
        if (cycle == 0) {
            color = glm::vec4{random(1.0f), random(1.0f), 1.0f, 1.0f};
        }
        vertex.position *= scale; // NOTE component 4 i.e `w` must not be scaled
        vertex.color = {color.r, color.g, color.b, color.a};
        /*
         * each vertex in a triangle needs to have barycentric coordinates (1,0,0), (0,1,0), or (0,0,1).
         * we use the normal information in the vertex to transmit them to the shader
         */
        vertex.normal = {
            cycle == 0 ? 1.0f : 0.0f,
            cycle == 1 ? 1.0f : 0.0f,
            cycle == 2 ? 1.0f : 0.0f,
            0.0f};
        cycle = (cycle + 1) % 3;
    }

    mesh_sphere = new VertexBuffer();
    mesh_sphere->set_transparent(false);
    mesh_sphere->set_shape(TRIANGLES);
    mesh_sphere->add_vertices(sphere_vertices);
    mesh_sphere->update();

    g->set_render_mode(RENDER_MODE_IMMEDIATELY);
}

void draw() {
    background(0.85f);

    fill(0);
    debug_text("FPS: " + nf(frameRate, 2), 20, 20);

    pushMatrix();
    translate(width / 2.0f, height / 2.0f);
    rotateX(frame_counter * 0.01f);
    rotateY(frame_counter * 0.027f);
    rotateZ(frame_counter * 0.043f);

    if (isKeyPressed && key == ' ') {
        frame_counter++;
    }

    shader(shader_barycentric_wireframe);
    /* set the line width */
    shader_barycentric_wireframe->set_uniform("line_width", map(mouseX, 0, width, 0.1, 20));
    /* matrices need to be set every frame for the transforms to work */
    // shader_barycentric_wireframe->set_uniform("u_projection_matrix", g->projection_matrix);
    // shader_barycentric_wireframe->set_uniform("u_view_matrix", g->view_matrix);
    /* before drawing the mesh the model matrix needs to be sent to the shader */
    // shader_barycentric_wireframe->set_uniform("u_model_matrix", g->model_matrix);
    mesh(mesh_sphere);

    pushMatrix();
    translate(height / 3.0f, 0);
    scale(0.5f);
    /* before drawing the mesh the model matrix needs to be sent to the shader */
    // shader_barycentric_wireframe->set_uniform("u_model_matrix", g->model_matrix);
    mesh(mesh_sphere);
    popMatrix();

    pushMatrix();
    translate(0, 100);
    scale(2.0f);
    /* before drawing the mesh the model matrix needs to be sent to the shader */
    // shader_barycentric_wireframe->set_uniform("u_model_matrix", g->model_matrix);
    mesh(mesh_sphere);
    popMatrix();

    fill(0, 0, 0);
    noStroke();
    pushMatrix();
    scale(0.25f);
    beginShape(TRIANGLES);
    normal(1, 0, 0);
    vertex(-width, -height, 0);
    normal(0, 1, 0);
    vertex(width, -height, 0);
    normal(0, 0, 1);
    vertex(width, height, 0);
    normal(1, 0, 0);
    vertex(width, height, 0);
    normal(0, 1, 0);
    vertex(-width, height, 0);
    normal(0, 0, 1);
    vertex(-width, -height, 0);
    endShape();
    popMatrix();

    /* reset the shader */
    shader();

    popMatrix();
}