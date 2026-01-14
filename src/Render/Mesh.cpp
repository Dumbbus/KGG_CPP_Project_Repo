//
// Created by lunarimoonlin on 12/14/25.
//

#include <Render/Mesh.hpp>

#include "Light/Normal.hpp"
#include "Render/Polygon.hpp"

void Mesh::recompute_normals() {
    if (m_vertexs.empty() || m_polygons.empty())
        return;

    m_normals.assign(m_vertexs.size(), gmath::Vector3d{0.0, 0.0, 0.0});

    for (const Polygon& poly : m_polygons) {
        const auto& index = poly.get_vertexs();
        if (index.size() < 3) continue;

        const auto& v0 = m_vertexs[index[0]];
        const auto& v1 = m_vertexs[index[1]];
        const auto& v2 = m_vertexs [index[2]];

        gmath::Vector3d face_normal = (v1 - v0).cross(v2 - v0).normalized();

        for (int i : index) {
            m_normals[i] += face_normal;
        }
    }

    for (auto& n : m_normals) {
        n.normalize();
    }
}
