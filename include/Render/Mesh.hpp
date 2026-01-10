//
// Created by lunarimoonlin on 12/14/25.
//

#ifndef KGG_CPP_PROJECT_REPO_MESH_H
#define KGG_CPP_PROJECT_REPO_MESH_H
#include "Math/Vector3.hpp"
#include <vector>

struct Vertex {
    gmath::Vector3<double> position;
    gmath::Vector3<double> normal;
};

// TODO: добавить поле атрибута для цвета? UV-коорды (на потом)
// TODO: вопрос триангуляции в случае, когда полигоны != треугольники
class Mesh {
    public:
        std::vector<Vertex> m_vertices;
        // std::vector<gmath::Vector3<double>> m_normals;
        // std::vector<int> m_indices;
        std::vector<std::vector<int>> m_faces;

        Mesh() = default;
        Mesh(
            const std::vector<gmath::Vector3<double>>& vertices,
            const std::vector<gmath::Vector3<double>>& normals,
            //const std::vector<int>& indices,
            const std::vector<std::vector<int>>& faces
            ) : m_faces(faces) {
            for (size_t i = 0; i < vertices.size(); i++) {
                gmath::Vector3<double> normal = (i < normals.size())
                    ? normals[i] : gmath::Vector3<double>{0, 0, 0};
                m_vertices.push_back({vertices[i], normal});
            }
        }
        ~Mesh() = default;

        std::vector<gmath::Vector3<double>> get_vertices() const {
            std::vector<gmath::Vector3<double>> vertices;
            vertices.reserve(m_vertices.size());
            for (const auto &v: m_vertices) {
                vertices.push_back(v.position);
            }
            return vertices;
        }

        std::vector<gmath::Vector3<double>> get_normals() const {
            std::vector<gmath::Vector3<double>> normals;
            normals.reserve(m_vertices.size());
            for (const auto &v: m_vertices) {
                normals.push_back(v.normal);
            }
            return normals;
        }

        void set_vertices(const std::vector<gmath::Vector3<double> > &vertices) {
            if (vertices.size() != m_vertices.size()) {
                m_vertices.resize(vertices.size());
            }
            for (size_t i = 0; i < vertices.size(); i++) {
                m_vertices[i].position = vertices[i];
            }
        }

        void set_normals(const std::vector<gmath::Vector3<double> > &normals) {
            for (size_t i = 0; i < normals.size() && i < m_vertices.size(); i++) {
                m_vertices[i].normal = normals[i];
            }
        }

        int vertex_count() const { return m_vertices.size(); }
        //int normals_count() const { m_vertices.size(); }
        int faces_count() const { return m_faces.size(); }

        void recompute_normals();
};


#endif //KGG_CPP_PROJECT_REPO_MESH_H