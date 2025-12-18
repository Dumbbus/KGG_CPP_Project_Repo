//
// Created by shulz on 18.12.2025.
//

#ifndef KGG_CPP_PROJECT_REPO_RASTERIZER_H
#define KGG_CPP_PROJECT_REPO_RASTERIZER_H
#include "Math/Vector2.hpp"
#include "SFML/Graphics/Color.hpp"
#include "Window/Framebuffer.h"

namespace render {
    class Rasterizer {
    public:
        static void draw_triangle(
            Framebuffer& framebuffer,
            const gmath::Vector2<float> a,
            const gmath::Vector2<float> b,
            const gmath::Vector2<float> c,
            const Color& color
        );

        static void draw_colored_triangle(
        Framebuffer& framebuffer,
        const gmath::Vector2<float> a,
        const gmath::Vector2<float> b,
        const gmath::Vector2<float> c,
        const Color& color_a,
        const Color& color_b,
        const Color& color_c
        );
    };
}

#endif //KGG_CPP_PROJECT_REPO_RASTERIZER_H