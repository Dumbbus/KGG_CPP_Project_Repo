#include "Render/Render.h"

#include <iostream>

std::vector<gmath::Vector3d> Render::process_mesh(
    const Mesh &mesh, // Vertex vertex? mesh size?
    const Transform &transform, // Matrix4d
    Camera &camera, // Matrix4d
    Projection &projection, // Matrix4d
    const Viewport &viewport // Width, Height
    ) {
    std::vector<gmath::Vector3d> screen_vertices;
    screen_vertices.reserve(mesh.vertex_count());

    gmath::Matrix4d M = transform.get_model_matrix();
    gmath::Matrix4d V = camera.get_view_matrix();
    gmath::Matrix4d P = projection.get_projection_matrix();

    gmath::Matrix4d MVP = P * V * M;

    for (const auto& vertex : mesh.m_vertices) {
        gmath::Vector4d temp_vector(
            vertex.position.x,
            vertex.position.y,
            vertex.position.z,
            1.0
            );

        gmath::Vector4d clip_space_v = MVP * temp_vector;

        if (clip_space_v.w >= 0.0001) {
            double ndc_x = clip_space_v.x / clip_space_v.w;
            double ndc_y = clip_space_v.y / clip_space_v.w;
            double ndc_z = clip_space_v.z / clip_space_v.w;

            double screen_x = (ndc_x + 1.0) * (viewport.width / 2.0);
            double screen_y = (1.0 - ndc_y) * (viewport.height / 2.0);

            // Внутри цикла Render::process_mesh
            if (screen_vertices.size() == 0) {
                std::cout << "Vertex 0 Screen: " << screen_x << ", " << screen_y << " Z: " << ndc_z << std::endl;
            }

            screen_vertices.push_back({screen_x, screen_y, ndc_z});
        }
    }

    return screen_vertices;
}

std::vector<gmath::Vector3d> Render::process_mesh(
    const std::vector<gmath::Vector3d> &vertices,
    const gmath::Matrix4d &transform_martix,
    const gmath::Matrix4d &projection_martix,
    const gmath::Matrix4d &view_martix,
    const double width,
    const double height
) {
    std::vector<gmath::Vector3d> screen_vertices;
    screen_vertices.reserve(vertices.size());

    gmath::Matrix4d MVP = projection_martix * view_martix * transform_martix;

    for (const auto& vertex : vertices) {
        gmath::Vector4d temp_vector(
            vertex.x,
            vertex.y,
            vertex.z,
            1.0
        );

        gmath::Vector4d clip_space_v = MVP * temp_vector;

        if (clip_space_v.w >= 0.0001) {
            double ndc_x = clip_space_v.x / clip_space_v.w;
            double ndc_y = clip_space_v.y / clip_space_v.w;
            double ndc_z = clip_space_v.z / clip_space_v.w;

            double screen_x = (ndc_x + 1.0) * (width / 2.0);
            double screen_y = (1.0 - ndc_y) * (height / 2.0);

            // Внутри цикла Render::process_mesh
            if (screen_vertices.empty()) {
                std::cout << "Vertex 0 Screen: " << screen_x << ", " << screen_y << " Z: " << ndc_z << std::endl;
            }

            screen_vertices.push_back({screen_x, screen_y, ndc_z});
        }
    }

    return screen_vertices;
}

