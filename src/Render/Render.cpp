#include "Render/Render.h"

#include <iostream>

std::vector<ProcessedVertex> Render::process_mesh(
    const Mesh& mesh,
    const gmath::Matrix4d& model,
    const gmath::Matrix4d& view,
    const gmath::Matrix4d& projection,
    double width,
    double height
) {
    std::vector<ProcessedVertex> result;

    const gmath::Matrix4d MVP = projection * view * model;
    const gmath::Matrix4d model_view = view * model;

    for (const Polygon& poly : mesh.m_polygons) {
        const auto& vertex_index = poly.get_vertexs();
        const auto& normal_index = poly.get_normals();
        const auto& uv_index = poly.get_uvs();

        const size_t count = vertex_index.size();
        if (count < 3) continue;

        for (size_t i = 0; i < count; ++i) {
            const auto& vertex = mesh.m_vertexs[vertex_index[i]];
            const auto& normal = mesh.m_normals[normal_index[i]];
            const auto& uv = mesh.m_uvs[uv_index[i]];

            const gmath::Vector4d clip = MVP * gmath::Vector4d(vertex.x, vertex.y, vertex.z, 1.0);

            const gmath::Vector4d n4 = (model_view * gmath::Vector4d(normal.x, normal.y, normal.z, 0.0)).normalized();

            if (clip.w < 0.0001) {
                result.push_back({{}, {}, {}, 0.0, false});
                continue;
            }

            const double inv_w = 1.0 / clip.w;

            const double ndc_x = clip.x * inv_w;
            const double ndc_y = clip.y * inv_w;
            const double ndc_z = clip.z * inv_w;

            const double screen_x = (ndc_x + 1.0) * width  * 0.5;
            const double screen_y = (1.0 - ndc_y) * height * 0.5;

            result.push_back({
                {screen_x, screen_y, ndc_z},
                {n4.x, n4.y, n4.z},
                uv * inv_w,
                inv_w,
                true
            });
        }
    }

    return result;
}

std::vector<gmath::Vector3d> Render::process_face_normals(
    const std::vector<gmath::Vector3d> &face_normals,
    const gmath::Matrix4d &model,
    const gmath::Matrix4d &view
    ) {
    std::vector<gmath::Vector3d> result;

    const gmath::Matrix4d model_view = view * model;

    for (const gmath::Vector3d face_normal : face_normals) {
        const gmath::Vector4d n4 = (
            model_view * gmath::Vector4d(
            face_normal.x,
            face_normal.y,
            face_normal.z,
            0.0
            )
        ).normalized();

        result.push_back({n4.x, n4.y, n4.z});
    }

    return result;
}
