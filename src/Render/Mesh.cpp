//
// Created by lunarimoonlin on 12/14/25.
//

#include <Render/Mesh.hpp>

#include "Light/Normal.hpp"
#include "Render/Polygon.hpp"

void Mesh::recompute_normals() {
    if (m_vertexs.empty() || m_polygons.empty())
        return;

    gmath::Normal<double> normal_calculator(m_vertexs.size(), m_polygons.size());

    std::vector<std::vector<int>> polygons;
    polygons.reserve(m_polygons.size());

    for (size_t i = 0; i < m_polygons.size(); ++i) {
        polygons.push_back(m_polygons[i].get_vertexs());
    }

    normal_calculator.compute_face_normals(polygons, m_vertexs);
    normal_calculator.compute_vertex_normals(polygons);

    m_normals.assign(m_vertexs.size(), gmath::Vector3d{0.0, 0.0, 0.0});

    m_face_normals = normal_calculator.get_face_normals();
    m_normals = normal_calculator.get_vertex_normals();
}
