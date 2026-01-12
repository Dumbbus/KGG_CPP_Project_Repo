//
// Created by lunarimoonlin on 12/14/25.
//

#include <Render/Mesh.hpp>

#include "Light/Normal.hpp"

void Mesh::recompute_normals() {
    if (m_vertices.empty() || m_faces.empty()) return;

    gmath::Normal<double> normal_calculator(vertex_count(), faces_count());

    normal_calculator.compute_face_normals(m_faces, get_vertices());
    normal_calculator.compute_vertex_normals(m_faces, get_vertices());

    m_faces_normals = normal_calculator.get_face_normals();

    set_normals(normal_calculator.get_vertex_normals());
}
