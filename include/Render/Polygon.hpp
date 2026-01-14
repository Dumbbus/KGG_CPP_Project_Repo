//
// Created by shulz on 14.01.2026.
//

#ifndef KGG_CPP_PROJECT_REPO_POLYGON_HPP
#define KGG_CPP_PROJECT_REPO_POLYGON_HPP
#include <vector>

#include "Math/Vector3.hpp"

// Класс индексов нужных элементов
class Polygon {
public:
    Polygon() = default;
    Polygon(std::vector<int>& vertices, std::vector<int>& normals, std::vector<int>& uvs)
        : m_vertices_index(vertices), m_normals_index(normals), m_uvs_index(uvs) {}
    ~Polygon() = default;

    const std::vector<int> get_vertexs() const {
        return m_vertices_index;
    }
    const std::vector<int> get_normals() const {
        return m_normals_index;
    }
    const std::vector<int> get_uvs() const {
        return m_uvs_index;
    }

    void set_vertexs(std::vector<int>& vertices) {
        m_vertices_index = vertices;
    }
    void set_normals(std::vector<int>& normals) {
        m_normals_index = normals;
    }
    void set_uvs(std::vector<int>& uvs) {
        m_uvs_index = uvs;
    }

private:
    std::vector<int> m_vertices_index;
    std::vector<int> m_normals_index;
    std::vector<int> m_uvs_index;
};

#endif //KGG_CPP_PROJECT_REPO_POLYGON_HPP