//
// Created by lunarimoonlin on 12/14/25.
//

#ifndef KGG_CPP_PROJECT_REPO_MESH_H
#define KGG_CPP_PROJECT_REPO_MESH_H
#include "Math/Vector3.hpp"
#include <vector>
#include "Math/Vector2.hpp"
#include "Render/Texture.hpp"
#include "Render/Polygon.hpp"

struct Vertex {
    gmath::Vector3<double> position;
    gmath::Vector3<double> normal;
    gmath::Vector2<double> uv;
};

class Mesh {
    public:
        std::vector<gmath::Vector3d> m_vertexs;
        std::vector<gmath::Vector3d> m_normals;
        std::vector<gmath::Vector3d> m_face_normals; // Не заполнять ридером, высчитывается отдельно
        std::vector<gmath::Vector2d> m_uvs;
        std::vector<Polygon> m_polygons;
        std::shared_ptr<Texture> m_texture;

        Mesh() = default;
        ~Mesh() = default;
        Mesh(
            std::vector<gmath::Vector3d>& vertices,
            std::vector<gmath::Vector3d>& normals,
            std::vector<gmath::Vector2d>& uvs,
            std::vector<Polygon>& polygons,
            std::shared_ptr<Texture> texture = nullptr
            ) : m_vertexs(vertices), m_normals(normals), m_uvs(uvs), m_polygons(polygons), m_texture(texture) {};
        Mesh(
            std::vector<gmath::Vector3d>& vertices,
            std::vector<gmath::Vector3d>& normals,
            std::vector<Polygon>& polygons,
            std::shared_ptr<Texture> texture = nullptr
            ) : m_vertexs(vertices), m_normals(normals), m_polygons(polygons), m_texture(texture) {
            set_dull_uv();
        };

        void recompute_normals();
        void set_dull_uv();
};


#endif //KGG_CPP_PROJECT_REPO_MESH_H