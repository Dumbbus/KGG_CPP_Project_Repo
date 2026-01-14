//
// Created by shulz on 18.12.2025.
//

#include "Render/Rasterizer.h"

#include <algorithm>
#include <complex>
#include <iostream>

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

        int d_x = std::abs(x_1 - x_0);
        int d_y = std::abs(y_1 - y_0);
        int error = 0;
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

    // Для интерполяции нормалей (более адекватные тени)
    static gmath::Vector3f interpolate_normal(
        float alpha,
        float beta,
        float gamma,
        const gmath::Vector3f& normal_1,
        const gmath::Vector3f& normal_2,
        const gmath::Vector3f& normal_3
    ) {
        gmath::Vector3f result = normal_1 * alpha + normal_2 * beta + normal_3 * gamma;

        return result.normalized();
    }

    static gmath::Vector2f interpolate_uv(
        float alpha,
        float beta,
        float gamma,
        const gmath::Vector2f& uv_1,
        const gmath::Vector2f& uv_2,
        const gmath::Vector2f& uv_3
    ) {
        return uv_1 * alpha + uv_2 * beta + uv_3 * gamma;
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

    void Rasterizer::draw_soft_shadow(
        Framebuffer &fb,
        const std::vector<ProcessedVertex> &triangles,
        const Texture* texture,
        const bool use_face_normals,
        const gmath::Vector3f& light_direction,
        const float ambient,
        const Color &base_color
        ) {
        for (size_t i = 0; i + 2 < triangles.size(); i += 3) {

            const auto& pv0 = triangles[i + 0];
            const auto& pv1 = triangles[i + 1];
            const auto& pv2 = triangles[i + 2];

            if (!pv0.valid || !pv1.valid || !pv2.valid)
                continue;

            gmath::Vector3f normal_0, normal_1, normal_2;

            if (use_face_normals) {
                gmath::Vector3f face_normal = (
                    gmath::Vector3f((float)pv0.normal.x, (float)pv0.normal.y, (float)pv0.normal.z) +
                    gmath::Vector3f((float)pv1.normal.x, (float)pv1.normal.y, (float)pv1.normal.z) +
                    gmath::Vector3f((float)pv2.normal.x, (float)pv2.normal.y, (float)pv2.normal.z)
                ).normalized();

                std::cout << "Face normal: " << face_normal << std::endl;

                normal_0 = normal_1 = normal_2 = face_normal;
            } else {
                normal_0 = {(float)pv0.normal.x, (float)pv0.normal.y, (float)pv0.normal.z};
                normal_1 = {(float)pv1.normal.x, (float)pv1.normal.y, (float)pv1.normal.z};
                normal_2 = {(float)pv2.normal.x, (float)pv2.normal.y, (float)pv2.normal.z};
            }

            gmath::Vector3f pos0f(pv0.position.x, pv0.position.y, pv0.position.z);
            gmath::Vector3f pos1f(pv1.position.x, pv1.position.y, pv1.position.z);
            gmath::Vector3f pos2f(pv2.position.x, pv2.position.y, pv2.position.z);

            gmath::Vector2f uv0f(pv0.uv.x, pv0.uv.y);
            gmath::Vector2f uv1f(pv1.uv.x, pv1.uv.y);
            gmath::Vector2f uv2f(pv2.uv.x, pv2.uv.y);

            draw_phong_triangle(
                fb,
                pos0f,
                pos1f,
                pos2f,
                normal_0,
                normal_1,
                normal_2,
                uv0f,
                uv1f,
                uv2f,
                static_cast<float>(pv0.inv_w),
                static_cast<float>(pv1.inv_w),
                static_cast<float>(pv2.inv_w),
                texture,
                light_direction,
                ambient,
                base_color
            );
        }
    }

    void Rasterizer::draw_wireframe(
        Framebuffer& fb,
        const std::vector<ProcessedVertex> &triangles,
        const Color &color
        ) {
        for (size_t i = 0; i + 2 < triangles.size(); i += 3) {

            const auto& pv0 = triangles[i + 0];
            const auto& pv1 = triangles[i + 1];
            const auto& pv2 = triangles[i + 2];

            if (!pv0.valid || !pv1.valid || !pv2.valid)
                continue;

            gmath::Vector3f v0 = {
                (float)pv0.position.x,
                (float)pv0.position.y,
                (float)pv0.position.z
            };
            gmath::Vector3f v1 = {
                (float)pv1.position.x,
                (float)pv1.position.y,
                (float)pv1.position.z
            };
            gmath::Vector3f v2 = {
                (float)pv2.position.x,
                (float)pv2.position.y,
                (float)pv2.position.z
            };

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

    void Rasterizer::draw_phong_triangle(
        Framebuffer& fb,
        const gmath::Vector3<float> a,
        const gmath::Vector3<float> b,
        const gmath::Vector3<float> c,
        const gmath::Vector3<float> normal_a,
        const gmath::Vector3<float> normal_b,
        const gmath::Vector3<float> normal_c,
        const gmath::Vector2<float> uv0,
        const gmath::Vector2<float> uv1,
        const gmath::Vector2<float> uv2,
        const float pv0_inv_w,
        const float pv1_inv_w,
        const float pv2_inv_w,
        const Texture* texture,
        const gmath::Vector3<float> light_direction,
        const float ambient,
        const Color &color
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
        max_x = std::min(max_x, static_cast<int>(fb.get_width()) - 1);
        max_y = std::min(max_y, static_cast<int>(fb.get_height()) - 1);

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

                    float inv_w = alpha * pv0_inv_w + beta * pv1_inv_w + gamma * pv2_inv_w;

                    gmath::Vector2f uv = interpolate_uv(alpha, beta, gamma, uv0, uv1, uv2) / inv_w;

                    Color texture_color = (texture && !texture->empty()) ? texture->sample(uv.x, uv.y) : color;

                    gmath::Vector3f pixel_normal = interpolate_normal(alpha, beta, gamma, normal_a, normal_b, normal_c);

                    float diffuse = std::max(0.0f, pixel_normal.dot(light_direction));
                    float intensity = std::min(1.0f, ambient + diffuse);

                    float z = (alpha * a.z + beta * b.z + gamma * c.z);

                    Color pixel_color(
                        (std::uint8_t) (intensity * texture_color.r),
                        (std::uint8_t) (intensity * texture_color.g),
                        (std::uint8_t) (intensity * texture_color.b),
                        texture_color.a
                    );

                    fb.set_pixel(x, y, pixel_color, z);
                }
            }
        }
    }
}
