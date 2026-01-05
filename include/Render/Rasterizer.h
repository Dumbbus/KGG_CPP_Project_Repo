//
// Created by shulz on 18.12.2025.
//

#ifndef KGG_CPP_PROJECT_REPO_RASTERIZER_H
#define KGG_CPP_PROJECT_REPO_RASTERIZER_H
#include "Mesh.hpp"
#include "Render.h"
#include "Math/Vector2.hpp"
#include "Math/Vector3.hpp"
#include "../ReadWrite/Object.hpp"
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

        // Отличие в типе вершины. Здесь вершина уже с 3-мя координатами
        // Где применяется наконец-то z-buffer
        static void draw_colored_triangle(
            Framebuffer& framebuffer,
            const gmath::Vector3<float> a,
            const gmath::Vector3<float> b,
            const gmath::Vector3<float> c,
            const Color& color_a,
            const Color& color_b,
            const Color& color_c
        );

        static void draw_shape(
            Framebuffer &fb,
            Object &obj,
            Render &renderer,
            Camera &camera,
            Projection &projection,
            const Viewport &viewport
        );

        static void draw_scene(const Mesh& mesh, const std::vector<gmath::Vector3d>& screen_coords, Framebuffer& fb);
    };
}

#endif //KGG_CPP_PROJECT_REPO_RASTERIZER_H