//
// Created by shulz on 18.12.2025.
//

#include "Render/Rasterizer.h"

#include <algorithm>

namespace render {
    static float edge(
        const gmath::Vector2<float>& a,
        const gmath::Vector2<float>& b,
        const gmath::Vector2<float>& c
        ) {
        return (c.x - a.x) * (b.y - a.y) - (c.y - a.y) * (b.x - a.x);
    }

    // По алгоритму Брезенхема
    static void draw_3d_line(
        Framebuffer& fb,
        const gmath::Vector3<float>& a,
        const gmath::Vector3<float>& b,
        const Color& color
    ) {
        int x_0 = static_cast<int>(a.x);
        int y_0 = static_cast<int>(a.y);
        float z_0 = a.z;

        int x_1 = static_cast<int>(b.x);
        int y_1 = static_cast<int>(b.y);
        float z_1 = b.z;

        bool steep = std::abs(y_1 - y_0) > std::abs(x_1 - x_0);
        if (steep) {
            std::swap(x_0, y_0);
            std::swap(x_1, y_1);
        }
        if (x_0 > x_1) {
            std::swap(x_0, x_1);
            std::swap(y_0, y_1);
            std::swap(z_0, z_1);
        }

        int d_x = x_1 - x_0;
        int d_y = std::abs(y_1 - y_0);
        int error = d_x / 2;
        int y_step = (y_0 < y_1) ? 1 : -1;
        int y = y_0;

        float z_step = (d_x != 0) ? (z_1 - z_0) / static_cast<float>(d_x) : 0.0f;
        float z = z_0;

        for (int x = x_0; x <= x_1; ++x) {
            if (steep) {
                fb.set_pixel(y, x, color, z);
            } else {
                fb.set_pixel(x, y, color, z);
            }

            error -= d_y;
            if (error < 0) {
                y += y_step;
                error += d_x;
            }

            z += z_step;
        }
    }

    static Color interpolate_color(
        float alpha,
        float beta,
        float gamma,
        const Color& a,
        const Color& b,
        const Color& c
    ) {
        // Lambda-функция, ограничиваем в нужной области чисел и приводим из float к
        // uint8_t, т.к. Color такой тип и хранит
        auto clamp = [](float v) {
            return static_cast<std::uint8_t>(
                std::clamp(v, 0.0f, 255.0f)
            );
        };

        float r = alpha * a.r + beta * b.r + gamma * c.r;

        float g = alpha * a.g + beta * b.g + gamma * c.g;

        float b_col = alpha * a.b + beta * b.b + gamma * c.b;

        float a_col = alpha * a.a + beta * b.a + gamma * c.a;

        return Color(
            clamp(r),
            clamp(g),
            clamp(b_col),
            clamp(a_col)
        );
    }

    void Rasterizer::draw_colored_triangle(
        Framebuffer& framebuffer,
        const gmath::Vector3<float> a,
        const gmath::Vector3<float> b,
        const gmath::Vector3<float> c,
        const Color& color_a,
        const Color& color_b,
        const Color& color_c
    ) {
        int min_x = static_cast<int>(
            std::floor(std::min({a.x, b.x, c.x}))
            );
        int max_x = static_cast<int>(
            std::floor(std::max({a.x, b.x, c.x}))
            );
        int min_y = static_cast<int>(
            std::floor(std::min({a.y, b.y, c.y}))
            );
        int max_y = static_cast<int>(
            std::floor(std::max({a.y, b.y, c.y}))
            );

        min_x = std::max(min_x, 0);
        min_y = std::max(min_y, 0);
        max_x = std::min(max_x, static_cast<int>(framebuffer.get_width()) - 1);
        max_y = std::min(max_y, static_cast<int>(framebuffer.get_height()) - 1);

        // Кэшируем 2D проекции вершин заранее, чтобы не создавать векторы в цикле
        const gmath::Vector2<float> v0(a.x, a.y);
        const gmath::Vector2<float> v1(b.x, b.y);
        const gmath::Vector2<float> v2(c.x, c.y);

        const float area = edge(v0, v1, v2);
        if (std::abs(area) < 0.00001f) return;

        for (int y = min_y; y <= max_y; ++y) {
            for (int x = min_x; x <= max_x; ++x) {
                gmath::Vector2<float> pixel(x + 0.5f, y + 0.5f);

                float w0 = edge(v1, v2, pixel);
                float w1 = edge(v2, v0, pixel);
                float w2 = edge(v0, v1, pixel);

                if ((w0 >= 0 && w1 >= 0 && w2 >= 0) || (w0 <= 0 && w1 <= 0 && w2 <= 0)) {
                    //framebuffer.set_pixel(x, y, color);
                    float alpha = w0 / area;
                    float beta = w1 / area;
                    float gamma = w2 / area;

                    Color result = interpolate_color(
                        alpha, beta, gamma,
                        color_a, color_b, color_c
                        );
                    float z = alpha * a.z + beta * b.z + gamma * c.z;

                    framebuffer.set_pixel(x, y, result, z);
                }
            }
        }
    }

    void Rasterizer::draw_shape(
        Framebuffer &fb,
        const std::vector<gmath::Vector3d>& screen_coords,
        const std::vector<std::vector<int>>& faces,
        const Color& color = Color::white() // По стандарту будет белым
    ) {
        draw_scene(faces, screen_coords, fb, color);
    }

    void Rasterizer::draw_scene(
        const std::vector<std::vector<int>>& faces,
        const std::vector<gmath::Vector3d>& screen_coords,
        Framebuffer& fb,
        const Color& color
    ) {
        size_t face_index = 1;
        for (std::vector<int> face : faces) {
            // TEMPORARY
            Color face_color(face_index * 45, face_index * 77, face_index * 123);

            int index_0 = face[0];
            int index_1 = face[1];
            int index_2 = face[2];

            gmath::Vector3f v0 = {(float)screen_coords[index_0].x, (float)screen_coords[index_0].y, (float)screen_coords[index_0].z};
            gmath::Vector3f v1 = {(float)screen_coords[index_1].x, (float)screen_coords[index_1].y, (float)screen_coords[index_1].z};
            gmath::Vector3f v2 = {(float)screen_coords[index_2].x, (float)screen_coords[index_2].y, (float)screen_coords[index_2].z};

            draw_colored_triangle(fb, v0, v1, v2, face_color, face_color, face_color);
            face_index++;
        }
    }

    void Rasterizer::draw_shape_soft_shadow(
        Framebuffer &fb,
        const std::vector<ProcessedVertex> &processed_vertices,
        const std::vector<std::vector<int> > &faces,
        const Color &base_color
        ) {
        draw_scene_soft_shadow(faces, processed_vertices, fb, base_color);
    }

    void Rasterizer::draw_scene_soft_shadow(
        const std::vector<std::vector<int>> &faces,
        const std::vector<ProcessedVertex> &processed_vertices,
        Framebuffer &fb,
        const Color &color
    ) {
        gmath::Vector3f light_direction(0.0f, 1.0f, 1.0f);
        light_direction.normalize();

        for (const std::vector<int> &face : faces) {
            const int index_0 = face[0];
            const int index_1 = face[1];
            const int index_2 = face[2];

            const auto& pv0 = processed_vertices[index_0];
            const auto& pv1 = processed_vertices[index_1];
            const auto& pv2 = processed_vertices[index_2];

            const gmath::Vector3f v0 ={(float)pv0.position.x, (float)pv0.position.y, (float)pv0.position.z};
            const gmath::Vector3f v1 ={(float)pv1.position.x, (float)pv1.position.y, (float)pv1.position.z};
            const gmath::Vector3f v2 ={(float)pv2.position.x, (float)pv2.position.y, (float)pv2.position.z};

            gmath::Vector3f normal_0 = {(float)pv0.normal.x, (float)pv0.normal.y, (float)pv0.normal.z};
            gmath::Vector3f normal_1 = {(float)pv1.normal.x, (float)pv1.normal.y, (float)pv1.normal.z};
            gmath::Vector3f normal_2 = {(float)pv2.normal.x, (float)pv2.normal.y, (float)pv2.normal.z};

            normal_0.normalize();
            normal_1.normalize();
            normal_2.normalize();

            const float ambient = 0.10f;

            const float index_max_0 = std::max(ambient, normal_0.dot(light_direction));
            const float index_max_1 = std::max(ambient, normal_1.dot(light_direction));
            const float index_max_2 = std::max(ambient, normal_2.dot(light_direction));

            const Color color_0((uint8_t)(index_max_0 * color.r), (uint8_t)(index_max_0 * color.g), (uint8_t)(index_max_0 * color.b));
            const Color color_1((uint8_t)(index_max_1 * color.r), (uint8_t)(index_max_1 * color.g), (uint8_t)(index_max_1 * color.b));
            const Color color_2((uint8_t)(index_max_2 * color.r), (uint8_t)(index_max_2 * color.g), (uint8_t)(index_max_2 * color.b));

            draw_colored_triangle(fb, v0, v1, v2, color_0, color_1, color_2);
        }
    }

    void Rasterizer::draw_wireframe(
        Framebuffer& fb,
        const std::vector<gmath::Vector3d> &screen_coords,
        const std::vector<std::vector<int>> &faces,
        const Color &color
        ) {
        for (const std::vector<int> &face : faces) {
            const int index_0 = face[0];
            const int index_1 = face[1];
            const int index_2 = face[2];

            gmath::Vector3f v0 = {(float)screen_coords[index_0].x, (float)screen_coords[index_0].y, (float)screen_coords[index_0].z};
            gmath::Vector3f v1 = {(float)screen_coords[index_1].x, (float)screen_coords[index_1].y, (float)screen_coords[index_1].z};
            gmath::Vector3f v2 = {(float)screen_coords[index_2].x, (float)screen_coords[index_2].y, (float)screen_coords[index_2].z};

            draw_only_lined_triangle(fb, v0, v1, v2, color);
        }
    }

    void Rasterizer::draw_only_lined_triangle(
        Framebuffer &fb,
        const gmath::Vector3f &a,
        const gmath::Vector3f &b,
        const gmath::Vector3f &c,
        const Color &line_color
        ) {
        draw_3d_line(fb, a, b, line_color);
        draw_3d_line(fb, b, c, line_color);
        draw_3d_line(fb, c, a, line_color);
    }
}