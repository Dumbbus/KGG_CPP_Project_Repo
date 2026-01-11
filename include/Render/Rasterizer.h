//
// Created by shulz on 18.12.2025.
//

#ifndef KGG_CPP_PROJECT_REPO_RASTERIZER_H
#define KGG_CPP_PROJECT_REPO_RASTERIZER_H
#include "imgui.h"
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
        void draw_shape(
            Framebuffer &fb,
            const std::vector<gmath::Vector3d>& screen_coords,
            const std::vector<std::vector<int>>& faces,
            const Color& color
        );

        void draw_shape_soft_shadow(
            Framebuffer &fb,
            const std::vector<ProcessedVertex> &processed_vertices,
            const std::vector<std::vector<int> > &faces,
            const std::vector<gmath::Vector3d> face_normals,
            const bool use_face_normals,
            const gmath::Vector3f& light_direction,
            const float ambient,
            const Color &base_color
        );

        void draw_wireframe(
            Framebuffer& fb,
            const std::vector<gmath::Vector3d>& screen_coords,
            const std::vector<std::vector<int>>& faces,
            const Color& color
            );

    private:
        void draw_scene(
            const std::vector<std::vector<int>>& faces,
            const std::vector<gmath::Vector3d>& screen_coords,
            Framebuffer& fb,
            const Color& color
        );

        void draw_scene_soft_shadow(
            const std::vector<std::vector<int>> &faces,
            const std::vector<ProcessedVertex> &processed_vertices,
            const gmath::Vector3f& light_direction,
            const std::vector<gmath::Vector3d> &face_normals,
            const bool use_face_normals,
            const float ambient,
            Framebuffer &fb,
            const Color &color
        );

        void draw_colored_triangle(
            Framebuffer& framebuffer,
            const gmath::Vector3<float> a,
            const gmath::Vector3<float> b,
            const gmath::Vector3<float> c,
            const Color& color_a,
            const Color& color_b,
            const Color& color_c
        );

        void draw_only_lined_triangle(
            Framebuffer& fb,
            const gmath::Vector3f &a,
            const gmath::Vector3f &b,
            const gmath::Vector3f &c,
            const Color &line_color
        );

        void draw_phong_triangle(
            Framebuffer& fb,
            const gmath::Vector3<float> a,
            const gmath::Vector3<float> b,
            const gmath::Vector3<float> c,
            const gmath::Vector3<float> normal_a,
            const gmath::Vector3<float> normal_b,
            const gmath::Vector3<float> normal_c,
            const gmath::Vector3<float> light_direction,
            const float ambient,
            const Color &color
        );
    };
}

#endif //KGG_CPP_PROJECT_REPO_RASTERIZER_H