#include "Render/Render.h"

#include <iostream>

// Transform -> get_model_matrix
// Projection -> get_projection_matrix
// Camera -> get_view_matrix
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

            screen_vertices.push_back({screen_x, screen_y, ndc_z});
        }
    }

    return screen_vertices;
}

std::vector<ProcessedVertex> Render::process_mesh_with_normals(
    const std::vector<gmath::Vector3d> &vertices,
    const std::vector<gmath::Vector3d> &normals,
    const gmath::Matrix4d &transform_martix,
    const gmath::Matrix4d &projection_martix,
    const gmath::Matrix4d &view_martix,
    const double width,
    const double height
) {
    size_t vertex_size = vertices.size();
    std::vector<ProcessedVertex> result;
    result.reserve(vertex_size);

    gmath::Matrix4d MVP = projection_martix * view_martix * transform_martix;

    const gmath::Matrix4d model_view = view_martix * transform_martix;

    for (size_t i = 0; i < vertex_size; i++) {
        const gmath::Vector4d clip_space_v = MVP * gmath::Vector4d(vertices[i].x, vertices[i].y, vertices[i].z, 1.0);

        const gmath::Vector4d n4 = (model_view * gmath::Vector4d(normals[i].x, normals[i].y, normals[i].z, 0.0)).normalized();

        const gmath::Vector3d normal_view = {n4.x, n4.y, n4.z};

        if (clip_space_v.w >= 0.0001) {
            const double ndc_x = clip_space_v.x / clip_space_v.w;
            const double ndc_y = clip_space_v.y / clip_space_v.w;
            const double ndc_z = clip_space_v.z / clip_space_v.w;

            const double screen_x = (ndc_x + 1.0) * (width / 2.0);
            const double screen_y = (1.0 - ndc_y) * (height / 2.0);

            result.push_back({{screen_x, screen_y, ndc_z}, normal_view});
        }
    }

    return result;
}