#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Umfeld.h"
#include "Geometry.h"

using namespace umfeld;

int                    frame_counter = 0;
std::vector<glm::vec3> line_points;
float                  line_width = 20;

void settings() {
    size(1024, 768);
}

// std::vector<glm::vec3> generateRibbonTriangles(
//     const std::vector<glm::vec3>& points,
//     const glm::mat4&              modelMatrix,
//     const glm::mat4&              viewMatrix,
//     float                         width  = 0.1f,
//     bool                          closed = false) {
//     std::vector<glm::vec3> ribbonVertices;
//     size_t                 n = points.size();
//     if (n < 2) {
//         return ribbonVertices;
//     }
//
//     glm::vec3 camForward_world = glm::normalize(glm::vec3(-viewMatrix[0][2], -viewMatrix[1][2], -viewMatrix[2][2]));
//     auto      normalMatrix     = glm::mat3(glm::transpose(glm::inverse(modelMatrix)));
//     glm::vec3 camForward_model = glm::normalize(normalMatrix * camForward_world);
//
//     std::vector<glm::vec3> offsetPoints;
//     glm::vec3              prevNormal;
//
//     constexpr float epsilon = 1e-4f;
//
//     for (size_t i = 0; i < n; ++i) {
//         glm::vec3 tangent;
//         if (i == 0) {
//             tangent = closed ? glm::normalize(points[1] - points[n - 1]) : glm::normalize(points[1] - points[0]);
//         } else if (i == n - 1) {
//             tangent = closed ? glm::normalize(points[0] - points[n - 2]) : glm::normalize(points[n - 1] - points[n - 2]);
//         } else {
//             tangent = glm::normalize(points[i + 1] - points[i - 1]);
//         }
//
//         glm::vec3 normal;
//
//         if (i == 0) {
//             normal = glm::normalize(glm::cross(tangent, camForward_model));
//         } else {
//             glm::vec3 projected = prevNormal - tangent * glm::dot(prevNormal, tangent);
//             float     len       = glm::length(projected);
//
//             if (len < epsilon) {
//                 normal = glm::normalize(glm::cross(tangent, camForward_model));
//             } else {
//                 normal = projected / len;
//             }
//         }
//
//         prevNormal = normal;
//
//         // ensure offset isn't too small
//         glm::vec3 offset = normal * (width * 0.5f);
//
//         // fallback if offset is still too small (edge case)
//         if (glm::length(offset) < epsilon) {
//             offset = glm::normalize(glm::cross(tangent, camForward_model)) * (width * 0.5f);
//         }
//
//         glm::vec3 left  = points[i] - offset;
//         glm::vec3 right = points[i] + offset;
//
//         offsetPoints.push_back(left);
//         offsetPoints.push_back(right);
//     }
//
//     size_t maxIndex = closed ? n : n - 1;
//     for (size_t i = 0; i < maxIndex; ++i) {
//         size_t i0 = i;
//         size_t i1 = (i + 1) % n;
//
//         glm::vec3 v0 = offsetPoints[2 * i0];
//         glm::vec3 v1 = offsetPoints[2 * i0 + 1];
//         glm::vec3 v2 = offsetPoints[2 * i1];
//         glm::vec3 v3 = offsetPoints[2 * i1 + 1];
//
//         // triangle 1
//         ribbonVertices.push_back(v0);
//         ribbonVertices.push_back(v2);
//         ribbonVertices.push_back(v1);
//
//         // triangle 2
//         ribbonVertices.push_back(v1);
//         ribbonVertices.push_back(v2);
//         ribbonVertices.push_back(v3);
//     }
//
//     return ribbonVertices;
// }
//
// void triangulate_line(const glm::vec3& lineStart, const glm::vec3& lineEnd, glm::vec3& resulting_normal) {
//     // 1. Transform Line Endpoints to View Space:
//     // • Multiply each endpoint of the line by the Model-View matrix to convert their coordinates from Model Space to View Space.
//     const glm::vec4 viewSpaceStart = g->view_matrix * g->model_matrix * glm::vec4(lineStart, 1.0);
//     const glm::vec4 viewSpaceEnd   = g->view_matrix * g->model_matrix * glm::vec4(lineEnd, 1.0);
//
//     // 2. Compute the Line Direction in View Space:
//     // • Subtract the transformed start point from the end point to get the direction vector of the line in View Space.
//     const glm::vec3 lineDir = glm::normalize(glm::vec3(viewSpaceEnd - viewSpaceStart));
//
//     // 3. Determine the Up Vector:
//     // • Choose an arbitrary up vector in View Space.
//     auto upVector = glm::vec3(0.0f, 0.0f, 1.0f);
//
//     // 4. Calculate the Normal Vector:
//     // • Compute the normal vector by taking the cross product of the line direction and the up vector. This vector will be perpendicular to both and lie in the plane defined by them.
//     glm::vec3 normal = glm::normalize(glm::cross(lineDir, upVector));
//
//     // 5. Handle Edge Cases:
//     // If the line direction is parallel to the up vector, the cross product will be zero, resulting in a zero normal vector. To handle this, you can choose an alternative up vector, such as the Z-axis.
//     if (glm::length(normal) < 0.001f) {
//         upVector = glm::vec3(0.0f, 0.0f, 1.0f);
//         normal   = glm::normalize(glm::cross(lineDir, upVector));
//     }
//
//     // 6. Transform the Normal Back to Model Space (Optional):
//     // If you need the normal in Model Space, multiply it by the inverse transpose of the Model matrix.
//     const glm::mat3 normalMatrix     = glm::transpose(glm::inverse(glm::mat3(g->model_matrix)));
//     const glm::vec3 modelSpaceNormal = glm::normalize(normalMatrix * normal);
//     // resulting_normal                 = normal;
//     resulting_normal = modelSpaceNormal;
// }
//
// void triangulate_line_strip(const std::vector<glm::vec3>& line_vertices, std::vector<Vertex>& vertices) {
//     if (line_vertices.size() < 2) {
//         return;
//     }
//
//     vertices.clear();
//
//     glm::vec3 normal;
//     for (int i = 0; i < line_vertices.size() - 1; ++i) {
//         glm::vec3 p0 = line_vertices[i];
//         glm::vec3 p1 = line_vertices[i + 1];
//         triangulate_line(p0, p1, normal);
//         normal *= line_width;
//         vertices.emplace_back(p0 - normal, glm::vec4(1, 0, 0, 1));
//         vertices.emplace_back(p1 - normal, glm::vec4(1, 0, 0, 1));
//         vertices.emplace_back(p1 + normal, glm::vec4(1, 0, 0, 1));
//
//         vertices.emplace_back(p1 + normal, glm::vec4(0, 1, 0, 1));
//         vertices.emplace_back(p0 + normal, glm::vec4(0, 1, 0, 1));
//         vertices.emplace_back(p0 - normal, glm::vec4(0, 1, 0, 1));
//     }
// }

void create_line_strip_random() {
    line_points.clear();
    float x = 0;
    float y = 0;
    float z = 0;
    for (int i = 0; i < 10; ++i) {
        x += random(-200, 200);
        y += random(-200, 200);
        z += random(-50, 50);
        line_points.emplace_back(x, y, z);
    }
}

void create_line_strip_rect() {
    line_points.clear();
    line_points.emplace_back(-200, -200, 0);
    line_points.emplace_back(200, -200, 0);
    line_points.emplace_back(300, 0, 0);
    line_points.emplace_back(200, 200, 0);
    line_points.emplace_back(-200, 200, 0);
    line_points.emplace_back(-300, 0, 0);
}

glm::vec3 computeScreenAlignedNormalModelSpace(
    const glm::vec3& p0,
    const glm::vec3& p1,
    const glm::mat4& modelMatrix,
    const glm::mat4& viewMatrix,
    const glm::mat4& projectionMatrix) {
    const auto      p0s          = glm::vec3(modelMatrix * viewMatrix * projectionMatrix * glm::vec4(p0, 1.0));
    const auto      p1s          = glm::vec3(modelMatrix * viewMatrix * projectionMatrix * glm::vec4(p1, 1.0));
    const glm::vec3 segmentDir   = glm::normalize(p1s - p0s);
    const auto      normal       = glm::vec3(segmentDir.y, -segmentDir.x, 0.0f);
    const auto      normalMatrix = glm::mat3(glm::transpose(glm::inverse(modelMatrix)));
    return glm::normalize(normal * normalMatrix);
}

std::vector<glm::vec3> extrudeLineStripToRibbon(
    const std::vector<glm::vec3>& points,
    float                         width,
    const glm::mat4&              modelMatrix,
    const glm::mat4&              viewMatrix,
    const glm::mat4&              projectionMatrix,
    bool                          closed = true) {

    std::vector<glm::vec3> ribbonVertices;
    size_t                 n = points.size();
    if (n < 2) {
        return ribbonVertices;
    }

    // compute per-point normals (averaged from adjacent segments)
    std::vector<glm::vec3> normals(n);

    for (size_t i = 0; i < n; ++i) {
        size_t iPrev = (i == 0) ? (closed ? n - 1 : 0) : i - 1;
        size_t iNext = (i == n - 1) ? (closed ? 0 : n - 1) : i + 1;

        if (i == 0 && !closed) {
            normals[i] = computeScreenAlignedNormalModelSpace(points[0], points[1], modelMatrix, viewMatrix, projectionMatrix);
        } else if (i == n - 1 && !closed) {
            normals[i] = computeScreenAlignedNormalModelSpace(points[n - 2], points[n - 1], modelMatrix, viewMatrix, projectionMatrix);
        } else {
            glm::vec3 n0 = computeScreenAlignedNormalModelSpace(points[iPrev], points[i], modelMatrix, viewMatrix, projectionMatrix);
            glm::vec3 n1 = computeScreenAlignedNormalModelSpace(points[i], points[iNext], modelMatrix, viewMatrix, projectionMatrix);
            normals[i]   = glm::normalize(n0 + n1);
        }
    }

    // number of segments
    size_t segmentCount = closed ? n : n - 1;
    ribbonVertices.reserve(segmentCount * 6);

    for (size_t i = 0; i < segmentCount; ++i) {
        size_t i0 = i;
        size_t i1 = (i + 1) % n;

        const glm::vec3& p0 = points[i0];
        const glm::vec3& p1 = points[i1];

        const glm::vec3& n0 = normals[i0];
        const glm::vec3& n1 = normals[i1];

        glm::vec3 offset0 = n0 * (width * 0.5f);
        glm::vec3 offset1 = n1 * (width * 0.5f);

        glm::vec3 p0a = p0 + offset0;
        glm::vec3 p0b = p0 - offset0;
        glm::vec3 p1a = p1 + offset1;
        glm::vec3 p1b = p1 - offset1;

        // triangle 1
        ribbonVertices.push_back(p0a);
        ribbonVertices.push_back(p1a);
        ribbonVertices.push_back(p0b);

        // triangle 2
        ribbonVertices.push_back(p0b);
        ribbonVertices.push_back(p1a);
        ribbonVertices.push_back(p1b);
    }

    return ribbonVertices;
}

std::vector<glm::vec3> _extrudeLineStripToRibbon(
    const std::vector<glm::vec3>& points,
    float                         width,
    const glm::mat4&              modelMatrix,
    const glm::mat4&              viewMatrix,
    const glm::mat4&              projectionMatrix) {
    std::vector<glm::vec3> allQuads;

    if (points.size() < 2) {
        return allQuads;
    }

    allQuads.reserve((points.size() - 1) * 6); // 6 vertices per segment

    for (size_t i = 0; i < points.size() - 1; ++i) {
        const glm::vec3& p0 = points[i];
        const glm::vec3& p1 = points[i + 1];

        glm::vec3 normal = computeScreenAlignedNormalModelSpace(p0, p1, modelMatrix, viewMatrix, projectionMatrix);
        glm::vec3 offset = normal * (width * 0.5f);

        glm::vec3 p0a = p0 + offset;
        glm::vec3 p0b = p0 - offset;
        glm::vec3 p1a = p1 + offset;
        glm::vec3 p1b = p1 - offset;

        // triangle 1
        allQuads.push_back(p0a);
        allQuads.push_back(p1a);
        allQuads.push_back(p0b);

        // triangle 2
        allQuads.push_back(p0b);
        allQuads.push_back(p1a);
        allQuads.push_back(p1b);
    }

    return allQuads;
}

// std::vector<glm::vec3> extrudeSegmentToQuad(const glm::vec3& p0,
//                                             const glm::vec3& p1,
//                                             const float      width) {
//     const glm::vec3        normal = computeScreenAlignedNormalModelSpace(p0, p1, g->model_matrix, g->view_matrix, g->projection_matrix);
//     std::vector<glm::vec3> quadVertices;
//     quadVertices.reserve(6); // 2 triangles
//
//     const glm::vec3 offset = normal * (width * 0.5f);
//
//     const glm::vec3 p0a = p0 + offset;
//     const glm::vec3 p0b = p0 - offset;
//     const glm::vec3 p1a = p1 + offset;
//     const glm::vec3 p1b = p1 - offset;
//
//     // triangle 1
//     quadVertices.push_back(p0a);
//     quadVertices.push_back(p1a);
//     quadVertices.push_back(p0b);
//
//     // triangle 2
//     quadVertices.push_back(p0b);
//     quadVertices.push_back(p1a);
//     quadVertices.push_back(p1b);
//
//     return quadVertices;
// }

std::vector<glm::vec3> _generateTubeMesh(
    const std::vector<glm::vec3>& points,
    float                         radius = 0.05f,
    bool                          closed = false) {
    std::vector<glm::vec3> tubeVertices;
    size_t                 n = points.size();
    if (n < 2) {
        return tubeVertices;
    }

    constexpr int                             sides = 4;
    std::vector<std::array<glm::vec3, sides>> ringVertices;

    // choose a stable initial reference up vector
    glm::vec3 referenceUp(0, 1, 0);
    if (glm::length(glm::cross(referenceUp, glm::normalize(points[1] - points[0]))) < 0.1f) {
        referenceUp = glm::vec3(1, 0, 0); // fallback if colinear
    }

    glm::vec3 prevTangent;
    glm::vec3 normal, binormal;

    for (size_t i = 0; i < n; ++i) {
        glm::vec3 tangent;
        if (i == 0) {
            tangent = closed
                          ? glm::normalize(points[1] - points[n - 1])
                          : glm::normalize(points[1] - points[0]);
        } else if (i == n - 1) {
            tangent = closed
                          ? glm::normalize(points[0] - points[n - 2])
                          : glm::normalize(points[n - 1] - points[n - 2]);
        } else {
            tangent = glm::normalize(points[i + 1] - points[i - 1]);
        }

        if (i == 0) {
            normal   = glm::normalize(glm::cross(tangent, referenceUp));
            binormal = glm::normalize(glm::cross(tangent, normal));
        } else {
            glm::vec3 rotationAxis = glm::cross(prevTangent, tangent);
            float     angle        = glm::asin(glm::length(rotationAxis));

            if (angle > 1e-4f) {
                rotationAxis = glm::normalize(rotationAxis);
                glm::mat4 R  = glm::rotate(glm::mat4(1.0f), angle, rotationAxis);
                normal       = glm::normalize(glm::vec3(R * glm::vec4(normal, 0.0)));
                binormal     = glm::normalize(glm::cross(tangent, normal));
            } else {
                // parallel: just keep previous frame
                binormal = glm::normalize(glm::cross(tangent, normal));
            }
        }

        prevTangent = tangent;

        // build cross-section ring
        std::array<glm::vec3, sides> ring;
        for (int j = 0; j < sides; ++j) {
            float     angle = glm::radians(90.0f * j);
            glm::vec3 dir   = glm::cos(angle) * normal + glm::sin(angle) * binormal;
            ring[j]         = points[i] + dir * radius;
        }

        ringVertices.push_back(ring);
    }

    // ensure seamless ring if closed
    if (closed) {
        ringVertices.push_back(ringVertices[0]);
    }

    size_t ringCount = ringVertices.size();
    for (size_t i = 0; i < ringCount - 1; ++i) {
        for (int j = 0; j < sides; ++j) {
            int j0 = j;
            int j1 = (j + 1) % sides;

            glm::vec3 a = ringVertices[i][j0];
            glm::vec3 b = ringVertices[i][j1];
            glm::vec3 c = ringVertices[i + 1][j0];
            glm::vec3 d = ringVertices[i + 1][j1];

            // triangle 1
            tubeVertices.push_back(a);
            tubeVertices.push_back(c);
            tubeVertices.push_back(b);

            // triangle 2
            tubeVertices.push_back(b);
            tubeVertices.push_back(c);
            tubeVertices.push_back(d);
        }
    }

    return tubeVertices;
}

void setup() {
    hint(ENABLE_DEPTH_TEST);
    create_line_strip_rect();
}

void draw() {
    background(0.85f);

    fill(0);
    noStroke();
    debug_text("FPS: " + nf(frameRate, 2), 20, 20);

    pushMatrix();
    translate(width / 2.0f, height / 2.0f);

    fill(0.5f, 0.85f, 1.0f, 0.5f);
    box(400, 400, 10);

    rotateX(frame_counter * 0.01f);
    rotateY(frame_counter * 0.027f);
    rotateZ(frame_counter * 0.043f);

    if (isKeyPressed && key == ' ') {
        frame_counter++;
    }

    line_width = map(mouseX, 0, width, 1, 50);

    // const std::vector<glm::vec3> vertices = generateRibbonTriangles(line_points,
    //                                                                 g->model_matrix,
    //                                                                 g->view_matrix,
    //                                                                 line_width, true);
    const std::vector<glm::vec3> vertices = _generateTubeMesh(line_points, line_width, true);
    const std::vector<glm::vec4> colors   = {
        glm::vec4(1, 0, 0, 1),
        glm::vec4(0, 1, 0, 1),
        glm::vec4(0, 0, 1, 1)};
    fill(0);
    beginShape(TRIANGLES);
    int i = 0;
    for (const auto v: vertices) {
        // const glm::vec4 c = colors[(i / 3) % 3];
        // fill(c.r, c.g, c.b);
        vertex(v.x, v.y, v.z);
        i++;
    }
    endShape();

    // glm::vec3              p0                = glm::vec3{10, 10, 0};
    // glm::vec3              p1                = glm::vec3{mouseX, mouseY, 0};
    // std::vector<glm::vec3> extruded_vertices = extrudeSegmentToQuad(p0, p1, line_width);
    const std::vector<glm::vec3> extruded_vertices = extrudeLineStripToRibbon(line_points, line_width, g->model_matrix, g->view_matrix, g->projection_matrix);

    fill(0);
    rotateX(HALF_PI);
    beginShape(TRIANGLES);
    i = 0;
    for (const auto v: extruded_vertices) {
        const glm::vec4 c = colors[(i / 3) % 3];
        // fill(c.r, c.g, c.b);
        i++;
        vertex(v.x, v.y, v.z);
    }
    endShape();

    // std::vector<Vertex> vertices;
    // triangulate_line_strip(line_points, vertices);
    // beginShape(TRIANGLES);
    // for (const auto v: vertices) {
    //     fill(v.color.r, v.color.g, v.color.b);
    //     vertex(v.position.x, v.position.y, v.position.z);
    // }
    // endShape();

    /* reset the shader */
    shader();

    popMatrix();
}

void keyPressed() {
    if (key == '1') {
        create_line_strip_random();
    }
    if (key == '2') {
        create_line_strip_rect();
    }
    if (key == 'r') {
        frame_counter = 0;
    }
}