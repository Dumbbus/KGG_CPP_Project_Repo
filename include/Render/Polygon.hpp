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
    Polygon(std::vector<int> vertices, std::vector<int> normals, std::vector<int> uvs)
        : m_vertices(vertices), m_normals(normals), m_uvs(uvs) {}
    ~Polygon() = default;

    std::vector<int> get_vertexs() {
        return m_vertexs;
    }
    std::vector<int> get_normals() {
        return m_normals;
    }
    std::vector<int> get_uvs() {
        return m_uvs;
    }

private:
    std::vector<int> m_vertexs;
    std::vector<int> m_normals;
    std::vector<int> m_uvs;
};

#endif //KGG_CPP_PROJECT_REPO_POLYGON_HPP