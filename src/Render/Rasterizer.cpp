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

    // TODO: одинаковые фрагменты кода
    // сделать более универсальным по возможности
    // хоть это и будут треугольники
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

    // TODO: избавиться от всех передающихся значениях, сделать меньшюю зависимость
    // Пусть будет обёрткой для draw_scene (пусть примет
    // список индексов, экранные координаты и фреймбуффер)
    void Rasterizer::draw_shape(
        Framebuffer &fb,
        Object &obj,
        Render &renderer,
        Camera &camera,
        Projection &projection,
        const Viewport &viewport
    ) {
        auto screen_coords = renderer.process_mesh(obj.mesh, obj.transform, camera, projection, viewport);

        draw_scene(obj.mesh, screen_coords, fb);
    }

    void Rasterizer::draw_shape(
        Framebuffer &fb,
        const std::vector<gmath::Vector3d>& screen_coords,
        const std::vector<std::vector<int>>& faces
    ) {
        draw_scene(faces, screen_coords, fb);
    }

    void Rasterizer::draw_scene(
        const std::vector<std::vector<int>>& faces,
        const std::vector<gmath::Vector3d>& screen_coords,
        Framebuffer& fb
    ) {
        for (std::vector<int> face : faces) {
            int index_0 = face[0];
            int index_1 = face[1];
            int index_2 = face[2];

            gmath::Vector3f v0 = {(float)screen_coords[index_0].x, (float)screen_coords[index_0].y, (float)screen_coords[index_0].z};
            gmath::Vector3f v1 = {(float)screen_coords[index_1].x, (float)screen_coords[index_1].y, (float)screen_coords[index_1].z};
            gmath::Vector3f v2 = {(float)screen_coords[index_2].x, (float)screen_coords[index_2].y, (float)screen_coords[index_2].z};

            draw_colored_triangle(fb, v0, v1, v2, Color::white(), Color::white(), Color::white());
        }
    }

    // TODO: меньше зависимости => избавиться от Mesh
    // Сделать метод приватным, над ним пусть будет обёртка draw_shape
    void Rasterizer::draw_scene(const Mesh& mesh, const std::vector<gmath::Vector3d>& screen_coords, Framebuffer& fb) {
        // Проходим по индексам меша (по 3 за раз)
        for (size_t i = 0; i < mesh.m_indices.size(); i += 3) {
            int i0 = mesh.m_indices[i];
            int i1 = mesh.m_indices[i+1];
            int i2 = mesh.m_indices[i+2];

            gmath::Vector3f v0 = {(float)screen_coords[i0].x, (float)screen_coords[i0].y, (float)screen_coords[i0].z};
            gmath::Vector3f v1 = {(float)screen_coords[i1].x, (float)screen_coords[i1].y, (float)screen_coords[i1].z};
            gmath::Vector3f v2 = {(float)screen_coords[i2].x, (float)screen_coords[i2].y, (float)screen_coords[i2].z};

            draw_colored_triangle(fb, v0, v1, v2, Color::white(), Color::white(), Color::white());
        }
    }
}