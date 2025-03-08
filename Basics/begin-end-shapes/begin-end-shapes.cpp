#include "Umgebung.h"
#include "PGraphics.h"

using namespace umgebung;


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

constexpr int BEVEL            = 0;
constexpr int MITER            = 1;
constexpr int ROUND            = 2;
constexpr int NONE             = 3;
constexpr int BEVEL_TESSELATOR = 4;

int stroke_join_mode = NONE;

void add_quad_as_triangles(std::vector<glm::vec2>& triangles,
                           const glm::vec2&        p1,
                           const glm::vec2&        p2,
                           const glm::vec2&        p3,
                           const glm::vec2&        p4) {
    triangles.emplace_back(p1);
    triangles.emplace_back(p2);
    triangles.emplace_back(p4);
    triangles.emplace_back(p4);
    triangles.emplace_back(p2);
    triangles.emplace_back(p3);
}

bool intersect_lines(const glm::vec2& p1, const glm::vec2& d1,
                     const glm::vec2& p2, const glm::vec2& d2,
                     glm::vec2& intersection) {
    const float det = d1.x * d2.y - d1.y * d2.x;

    if (fabs(det) < 1e-6f) {
        return false; // Parallel or coincident lines
    }

    const float t = ((p2.x - p1.x) * d2.y - (p2.y - p1.y) * d2.x) / det;

    intersection = glm::vec2(p1 + t * d1);
    return true;
}

float angle_between_vectors(const glm::vec2& d1, const glm::vec2& d2) {
    const float determinant = d1.x * d2.y - d1.y * d2.x;
    const float angle       = std::atan2(determinant, glm::dot(d1, d2));
    return angle;
}

struct Segment {
    glm::vec2 position;
    glm::vec2 normal;
    glm::vec2 direction;
    glm::vec2 next_position;
};

void create_stroke_join_bevel(std::vector<glm::vec2>& triangles,
                              const bool              close_shape,
                              const float             half_width,
                              std::vector<Segment>&   segments) {
    glm::vec2 p_prev_left{};
    glm::vec2 p_prev_right{};
    const int num_segments = segments.size() - (close_shape ? 0 : 1);
    for (int i = 0; i < num_segments; ++i) {
        Segment&        s1           = segments[i];
        const glm::vec2 p1_line_norm = s1.normal * half_width;
        const glm::vec2 p1_left      = s1.position + p1_line_norm;
        const glm::vec2 p1_right     = s1.position - p1_line_norm;
        const glm::vec2 p2_left      = s1.next_position + p1_line_norm;
        const glm::vec2 p2_right     = s1.next_position - p1_line_norm;
        add_quad_as_triangles(triangles,
                              p1_left,
                              p2_left,
                              p2_right,
                              p1_right);
        if (i != 0) {
            Segment&    s2    = segments[i - 1];
            const float angle = glm::degrees(angle_between_vectors(s1.direction, s2.direction));
            if (angle > 0) {
                triangles.emplace_back(s1.position);
                triangles.emplace_back(p_prev_left);
                triangles.emplace_back(p1_left);
            } else {
                triangles.emplace_back(s1.position);
                triangles.emplace_back(p_prev_right);
                triangles.emplace_back(p1_right);
            }
        }
        p_prev_left  = p2_left;
        p_prev_right = p2_right;
    }
    if (close_shape) {
        Segment&        s1           = segments[0];
        Segment&        s2           = segments[segments.size() - 1];
        const float     angle        = glm::degrees(angle_between_vectors(s1.direction, s2.direction));
        const glm::vec2 p1_line_norm = s1.normal * half_width;
        const glm::vec2 p1_left      = s1.position + p1_line_norm;
        const glm::vec2 p1_right     = s1.position - p1_line_norm;
        if (angle > 0) {
            triangles.emplace_back(s1.position);
            triangles.emplace_back(p_prev_left);
            triangles.emplace_back(p1_left);
        } else {
            triangles.emplace_back(s1.position);
            triangles.emplace_back(p_prev_right);
            triangles.emplace_back(p1_right);
        }
    }
}

void create_stroke_join_none(std::vector<glm::vec2>& triangles,
                             const bool              close_shape,
                             const float             half_width,
                             std::vector<Segment>&   segments) {
    const int num_segments = segments.size() - (close_shape ? 0 : 1);
    for (int i = 0; i < num_segments; ++i) {
        Segment&        s1           = segments[i];
        const glm::vec2 p1_line_norm = s1.normal * half_width;
        const glm::vec2 p1_left      = s1.position + p1_line_norm;
        const glm::vec2 p1_right     = s1.position - p1_line_norm;
        const glm::vec2 p2_left      = s1.next_position + p1_line_norm;
        const glm::vec2 p2_right     = s1.next_position - p1_line_norm;
        add_quad_as_triangles(triangles,
                              p1_left,
                              p2_left,
                              p2_right,
                              p1_right);
    }
}

void create_stroke_join_round(std::vector<glm::vec2>&     triangles,
                              const bool                  close_shape,
                              const float                 half_width,
                              const std::vector<Segment>& segments) {
    noStroke();
    fill(0);

    const int num_segments = segments.size() - (close_shape ? 0 : 1);
    for (int i = 0; i < num_segments; ++i) {
        const Segment&  s            = segments[i];
        const glm::vec2 p1_line_norm = s.normal * half_width;
        const glm::vec2 p1_left      = s.position + p1_line_norm;
        const glm::vec2 p1_right     = s.position - p1_line_norm;
        const glm::vec2 p2_left      = s.next_position + p1_line_norm;
        const glm::vec2 p2_right     = s.next_position - p1_line_norm;
        add_quad_as_triangles(triangles,
                              p1_left,
                              p2_left,
                              p2_right,
                              p1_right);
        circle(s.position.x, s.position.y, half_width * 2);
    }
    if (!close_shape) {
        const Segment& s = segments[segments.size() - 1];
        circle(s.position.x, s.position.y, half_width * 2);
    }
}

void create_stroke_join_miter_tessellate(std::vector<glm::vec2>&     triangles,
                                         const bool                  close_shape,
                                         const float                 half_width,
                                         const std::vector<Segment>& segments) {
    std::vector<glm::vec2> outline_left;
    std::vector<glm::vec2> outline_right;

    const int num_segments = segments.size() + (close_shape ? 1 : -1);
    for (int i = 0; i < num_segments; ++i) {
        const Segment& s1 = segments[i % segments.size()];
        const Segment& s2 = segments[(i + 1) % segments.size()];

        glm::vec2 intersection_left, intersection_right;

        const bool result_left = intersect_lines(
            s1.position + s1.normal * half_width, s1.direction,
            s2.position + s2.normal * half_width, s2.direction,
            intersection_left);

        const bool result_right = intersect_lines(
            s1.position - s1.normal * half_width, s1.direction,
            s2.position - s2.normal * half_width, s2.direction,
            intersection_right);

        if (!result_left) {
            intersection_left = s2.position + s1.normal * half_width;
        }
        if (!result_right) {
            intersection_right = s2.position - s1.normal * half_width;
        }

        const float     angle     = glm::degrees(angle_between_vectors(s1.direction, s2.direction));
        constexpr float max_angle = 160.0f;
        if (fabs(angle) > max_angle) {
            intersection_left  = s1.next_position + s1.normal * half_width;
            intersection_right = s1.next_position - s1.normal * half_width;
        }

        outline_left.push_back(intersection_left);
        outline_right.push_back(intersection_right);

        if (i == 0 && !close_shape) {
            outline_left.insert(outline_left.begin(), s1.position + s1.normal * half_width);
            outline_right.insert(outline_right.begin(), s1.position - s1.normal * half_width);
        }
    }

    std::vector<glm::vec2> polygon_outline;
    polygon_outline.insert(polygon_outline.end(), outline_left.begin(), outline_left.end());
    polygon_outline.insert(polygon_outline.end(), outline_right.rbegin(), outline_right.rend());

    TESStesselator* tess = tessNewTess(nullptr);
    tessAddContour(tess, 2, polygon_outline.data(), sizeof(glm::vec2), polygon_outline.size());

    if (tessTesselate(tess, TESS_WINDING_NONZERO, TESS_POLYGONS, 3, 2, nullptr)) {
        const float*     verts  = tessGetVertices(tess);
        const TESSindex* elems  = tessGetElements(tess);
        const int        nelems = tessGetElementCount(tess);

        for (int i = 0; i < nelems; ++i) {
            const TESSindex* tri = &elems[i * 3];
            glm::vec2        v1  = glm::make_vec2(&verts[tri[0] * 2]);
            glm::vec2        v2  = glm::make_vec2(&verts[tri[1] * 2]);
            glm::vec2        v3  = glm::make_vec2(&verts[tri[2] * 2]);

            triangles.push_back(v1);
            triangles.push_back(v2);
            triangles.push_back(v3);
        }
    }

    tessDeleteTess(tess);
}

void create_stroke_join_miter(std::vector<glm::vec2>& triangles,
                              const bool              close_shape,
                              const float             half_width,
                              std::vector<Segment>&   segments) {
    glm::vec2 p_prev_left{};
    glm::vec2 p_prev_right{};

    const int num_segments = segments.size() + (close_shape ? 1 : -1);
    for (int i = 0; i < num_segments; ++i) {
        const int      j  = i % segments.size();
        const int      jj = (i + 1) % segments.size();
        const Segment& s1 = segments[j];
        const Segment& s2 = segments[jj];

        const glm::vec2 p1_line_norm = s1.normal * half_width;
        const glm::vec2 p1_left      = s1.position + p1_line_norm;
        const glm::vec2 p1_right     = s1.position - p1_line_norm;

        const glm::vec2 p2_line_norm = s2.normal * half_width;
        const glm::vec2 p2_left      = s2.position + p2_line_norm;
        const glm::vec2 p2_right     = s2.position - p2_line_norm;

        glm::vec2  intersection_left;
        const bool result_left = intersect_lines(p1_left, s1.direction,
                                                 p2_left, s2.direction,
                                                 intersection_left);
        glm::vec2  intersection_right;
        const bool result_right = intersect_lines(p1_right, s1.direction,
                                                  p2_right, s2.direction,
                                                  intersection_right);

        if (!result_left) {
            intersection_left = s2.position + p1_line_norm;
        }

        if (!result_right) {
            intersection_right = s2.position - p1_line_norm;
        }

        bool            flip_intersection = false;
        const float     angle             = glm::degrees(angle_between_vectors(s1.direction, s2.direction));
        constexpr float max_angle         = 160.0f;
        if (fabs(angle) > max_angle) {
            intersection_left  = s1.next_position + p1_line_norm;
            intersection_right = s1.next_position - p1_line_norm;
            flip_intersection  = true;
        }

        if (i != 0) {
            add_quad_as_triangles(triangles,
                                  p_prev_left,
                                  intersection_left,
                                  intersection_right,
                                  p_prev_right);
        } else {
            if (!close_shape) {
                add_quad_as_triangles(triangles,
                                      p1_left,
                                      intersection_left,
                                      intersection_right,
                                      p1_right);
            }
        }

        if (flip_intersection) {
            p_prev_left  = intersection_right;
            p_prev_right = intersection_left;
        } else {
            p_prev_left  = intersection_left;
            p_prev_right = intersection_right;
        }
    }
}

void create_stroke_join_none_tessellate(std::vector<glm::vec2>& triangles,
                                        const bool              close_shape,
                                        const float             half_width,
                                        std::vector<Segment>&   segments) {
    std::vector<glm::vec2> outline_points;

    const int num_segments = segments.size() - (close_shape ? 0 : 1);
    for (int i = 0; i < num_segments; ++i) {
        Segment&        s1           = segments[i];
        const glm::vec2 p1_line_norm = s1.normal * half_width;
        const glm::vec2 p1_left      = s1.position + p1_line_norm;
        const glm::vec2 p2_left      = s1.next_position + p1_line_norm;

        // add left side points
        outline_points.push_back(p1_left);
        outline_points.push_back(p2_left);
    }

    // Then traverse segments backwards to get right-side points correctly ordered:
    for (int i = num_segments - 1; i >= 0; --i) {
        Segment&        s1           = segments[i];
        const glm::vec2 p1_line_norm = s1.normal * half_width;
        const glm::vec2 p2_right     = s1.next_position - p1_line_norm;
        const glm::vec2 p1_right     = s1.position - p1_line_norm;

        // add right side points
        outline_points.push_back(p2_right);
        outline_points.push_back(p1_right);
    }

    // Now send these points to libtess2 (as shown above)
    TESStesselator* tess = tessNewTess(nullptr);
    tessAddContour(tess, 2, outline_points.data(), sizeof(glm::vec2), outline_points.size());

    if (tessTesselate(tess, TESS_WINDING_NONZERO, TESS_POLYGONS, 3, 2, nullptr)) {
        const float*     verts  = tessGetVertices(tess);
        const TESSindex* elems  = tessGetElements(tess);
        const int        nelems = tessGetElementCount(tess);

        for (int i = 0; i < nelems; ++i) {
            const TESSindex* tri = &elems[i * 3];
            glm::vec2        v1  = glm::make_vec2(&verts[tri[0] * 2]);
            glm::vec2        v2  = glm::make_vec2(&verts[tri[1] * 2]);
            glm::vec2        v3  = glm::make_vec2(&verts[tri[2] * 2]);

            triangles.push_back(v1);
            triangles.push_back(v2);
            triangles.push_back(v3);
        }
    }

    tessDeleteTess(tess);
}

std::vector<glm::vec2> line_strip(const std::vector<glm::vec3>& points,
                                  const bool                    close_shape,
                                  const float                   stroke_weight) {
    std::vector<glm::vec2> triangles;
    const float            half_width = stroke_weight * 0.5f;

    // TODO test this case
    // if (points.size() < 2) {
    //     return triangles;
    // }

    std::vector<Segment> segments(points.size());
    for (int i = 0; i < points.size(); ++i) {
        Segment s;
        s.position = glm::vec2(points[i].x, points[i].y);
        if (i == points.size() - 1) { // last point needs special care
            if (close_shape) {        // copy first point for closed shapes
                s.next_position = glm::vec2(points[0].x, points[0].y);
            } else { // project point last for open shapes
                s.next_position = points[i] + (points[i] - points[i - 1]);
            }
        } else { // for all other segments use next point
            s.next_position = glm::vec2(points[i + 1].x, points[i + 1].y);
        }
        s.direction = s.next_position - s.position;
        s.normal    = glm::normalize(s.direction);
        s.normal    = glm::vec2(-s.normal.y, s.normal.x);
        segments[i] = s;
    }

    switch (stroke_join_mode) {
        case ROUND:
            create_stroke_join_round(triangles, close_shape, half_width, segments);
            break;
        case MITER:
            create_stroke_join_miter(triangles, close_shape, half_width, segments);
            break;
        case BEVEL:
            create_stroke_join_bevel(triangles, close_shape, half_width, segments);
            break;
        case BEVEL_TESSELATOR:
            // create_stroke_join_none_tessellate(triangles, close_shape, half_width, segments);
            create_stroke_join_miter_tessellate(triangles, close_shape, half_width, segments);
            break;
        case NONE:
        default:
            create_stroke_join_none(triangles, close_shape, half_width, segments);
            break;
    }
    return triangles;
}

float stroke_weight = 30;

void settings() {
    size(1024, 768);
    display            = 0;
    antialiasing       = 8;
    render_to_buffer   = false;
    retina_support     = true;
    subsystem_graphics = umgebung_subsystem_graphics_create_openglv33();
}

void setup() {
    hint(HINT_ENABLE_SMOOTH_LINES);
}

void draw() {
    background(1.0f);

    strokeWeight(stroke_weight);
    stroke(0.0f);
    fill(0.5f, 0.85f, 1.0f);
    beginShape(POLYGON);
    vertex(120, 80);
    vertex(230, 80);
    vertex(mouseX, mouseY);
    vertex(340, 190);
    vertex(340, 300);
    vertex(120, 300);
    endShape(is_mouse_pressed);

    std::vector<glm::vec3> points;
    points.emplace_back(120, 80, 0);
    points.emplace_back(230, 80, 0);
    points.emplace_back(mouseX, mouseY, 0);
    points.emplace_back(340, 190, 0);
    // points.emplace_back(340, 300, 0);
    points.emplace_back(120, 300, 0);

    const std::vector<glm::vec2> triangles = line_strip(points, is_mouse_pressed, stroke_weight);

    const std::vector<glm::vec4> colors = {
        glm::vec4{1, 0, 0, 0.5},
        glm::vec4{0, 1, 0, 0.5},
        glm::vec4{0, 0, 1, 0.5},
    };

    int i = 0;
    noStroke();
    fill(0.0f, 0.5f);
    beginShape(TRIANGLES);
    for (const auto t: triangles) {
        const int       ii = (i / 3) % colors.size();
        const glm::vec4 c  = colors[ii];
        // fill(c.r, c.g, c.b, c.a);
        vertex(t.x, t.y);
        i++;
    }
    endShape();
}

void keyPressed() {
    if (key == '-') {
        stroke_weight--;
        if (stroke_weight < 0) { stroke_weight = 0; }
    }
    if (key == '+') {
        stroke_weight++;
    }
    if (key == '1') {
        stroke_join_mode = NONE;
    }
    if (key == '2') {
        stroke_join_mode = BEVEL;
    }
    if (key == '3') {
        stroke_join_mode = MITER;
    }
    if (key == '4') {
        stroke_join_mode = ROUND;
    }
    if (key == '5') {
        stroke_join_mode = BEVEL_TESSELATOR;
    }
}