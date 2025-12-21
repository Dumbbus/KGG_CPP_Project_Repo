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

    /**
     * Отрисовка треугольников с помощью условия на нахождение внутри треугольника
     * В который вписан соответствующие координаты
     *
     * @param framebuffer
     * @param a
     * @param b
     * @param c
     * @param color
     */
    void Rasterizer::draw_triangle(
        Framebuffer &framebuffer,
        const gmath::Vector2<float> a,
        const gmath::Vector2<float> b,
        const gmath::Vector2<float> c,
        const Color &color
        ) {
        // 1. Bounding box
        // Получим "квадрат", в которую полностью вписан треугольник
        const int min_x = static_cast<int>(
            std::floor(std::min({a.x, b.x, c.x}))
            );
        const int max_x = static_cast<int>(
            std::floor(std::max({a.x, b.x, c.x}))
            );
        const int min_y = static_cast<int>(
            std::floor(std::min({a.y, b.y, c.y}))
            );
        const int max_y = static_cast<int>(
            std::floor(std::max({a.y, b.y, c.y}))
            );

        // 2. Предварительная ориентация
        const float area = edge(a, b, c);
        if (area == 0.0f) {
            return;
        }

        // 3. Отрисовка треуголька
        for (int y = min_y; y <= max_y; ++y) {
            for (int x = min_x; x <= max_x; ++x) {
                gmath::Vector2<float> pixel(
                    x + 0.5f,
                    y + 0.5f
                );

                float w0 = edge(b, c, pixel);
                float w1 = edge(c, a, pixel);
                float w2 = edge(a, b, pixel);

                if ((w0 >= 0 && w1 >= 0 && w2 >= 0) || (w0 <= 0 && w1 <= 0 && w2 <= 0)) {
                    framebuffer.set_pixel(x, y, color);
                }
            }
        }
    }

    void Rasterizer::draw_colored_triangle(
        Framebuffer& framebuffer,
        const gmath::Vector2<float> a,
        const gmath::Vector2<float> b,
        const gmath::Vector2<float> c,
        const Color& color_a,
        const Color& color_b,
        const Color& color_c
    ) {
        const int min_x = static_cast<int>(
            std::floor(std::min({a.x, b.x, c.x}))
            );
        const int max_x = static_cast<int>(
            std::floor(std::max({a.x, b.x, c.x}))
            );
        const int min_y = static_cast<int>(
            std::floor(std::min({a.y, b.y, c.y}))
            );
        const int max_y = static_cast<int>(
            std::floor(std::max({a.y, b.y, c.y}))
            );

        const float area = edge(a, b, c);
        if (area == 0.0f) {
            return;
        }

        for (int y = min_y; y <= max_y; ++y) {
            for (int x = min_x; x <= max_x; ++x) {
                gmath::Vector2<float> pixel(x + 0.5f, y + 0.5f);

                float w0 = edge(b, c, pixel);
                float w1 = edge(c, a, pixel);
                float w2 = edge(a, b, pixel);

                if ((w0 >= 0 && w1 >= 0 && w2 >= 0) || (w0 <= 0 && w1 <= 0 && w2 <= 0)) {
                    //framebuffer.set_pixel(x, y, color);
                    float alpha = w0 / area;
                    float beta = w1 / area;
                    float gamma = w2 / area;

                    Color result = interpolate_color(
                        alpha, beta, gamma,
                        color_a, color_b, color_c
                        );
                    framebuffer.set_pixel(x, y, result);
                }
            }
        }
    }
}
