//
// Created by shulz on 18.12.2025.
//

#ifndef KGG_CPP_PROJECT_REPO_RASTERIZER_H
#define KGG_CPP_PROJECT_REPO_RASTERIZER_H
#include "Mesh.hpp"
#include "Render.h"
#include "Math/Vector2.hpp"
#include "Math/Vector3.hpp"
#include "Window/Framebuffer.h"

namespace render {
    class Rasterizer {
    public:
        void draw_scene(
            Framebuffer &fb,
            const std::vector<ProcessedVertex> &triangles,
            std::vector<gmath::Vector3d>& face_normals,
            const Texture* texture,
            const bool use_face_normals,
            const gmath::Vector3f& light_direction,
            const float ambient,
            const Color &color
        );

        void draw_wireframe(
            Framebuffer& fb,
            const std::vector<ProcessedVertex>& screen_coords,
            const Color& color
            );

    private:
        void draw_colored_triangle(
            Framebuffer& framebuffer,
            const gmath::Vector3<float> a,
            const gmath::Vector3<float> b,
            const gmath::Vector3<float> c,
            const Color& color_a,
            const Color& color_b,
            const Color& color_c
        );

        void draw_phong_triangle(
            Framebuffer& fb,
            const gmath::Vector3<float> a,
            const gmath::Vector3<float> b,
            const gmath::Vector3<float> c,
            const gmath::Vector3<float> normal_a,
            const gmath::Vector3<float> normal_b,
            const gmath::Vector3<float> normal_c,
            const gmath::Vector2<float> uv_1,
            const gmath::Vector2<float> uv_2,
            const gmath::Vector2<float> uv_3,
            const float pv0_inv_w,
            const float pv1_inv_w,
            const float pv2_inv_w,
            const Texture* texture,
            const gmath::Vector3<float> light_direction,
            const float ambient,
            const Color &color
        );

        void draw_only_lined_triangle(
            Framebuffer& fb,
            const gmath::Vector3f &a,
            const gmath::Vector3f &b,
            const gmath::Vector3f &c,
            const Color &line_color
        );
    };
}

#endif //KGG_CPP_PROJECT_REPO_RASTERIZER_H