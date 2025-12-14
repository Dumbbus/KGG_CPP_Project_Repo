#pragma once

#include <vector>
#include "Vector3.hpp"

namespace gmath {

    template<Chislo T>
    class Normal {
        private:
            std::vector<Vector3<T>> vertex_normals;
            std::vector<Vector3<T>> face_normals;
        public:
            Normal(size_t vertex_count, size_t face_count)
                : vertex_normals(vertex_count, Vector3<T>::Null()),
                face_normals(face_count, Vector3<T>::Null())
            {}

            const std::vector<Vector3<T>>& get_vertex_normals() const {
                return vertex_normals;
            }

            const std::vector<Vector3<T>>& get_face_normals() const {
                return face_normals;
            }

            void compute_face_normals(
                const std::vector<std::vector<int>>& polygons,
                const std::vector<Vector3<T>>& vertices
            ) {
                //face_normals.clear();

                for (size_t i = 0; i < polygons.size(); i++) {
                    const auto& polygon = polygons[i];

                    if (polygon.size() < 3) {
                        face_normals[i] = Vector3<T>::Null();
                        continue;
                    }

                    const Vector3<T> edge_A = vertices[polygon[0]];
                    const Vector3<T> edge_B = vertices[polygon[1]];
                    const Vector3<T> edge_C = vertices[polygon[2]];

                    Vector3<T> edge_one = edge_B - edge_A;
                    Vector3<T> edge_two = edge_C - edge_A;

                    face_normals[i] = edge_one.cross(edge_two).normalized();
                }
            }

            void compute_vertex_normals(
            const std::vector<std::vector<int>>& polygons,
            const std::vector<Vector3<T>>& vertices
            ) {
                //vertex_normals.clear();

                for (auto& vertex : vertex_normals) {
                    vertex = Vector3<T>::Null();
                }

                for (size_t i = 0; i < polygons.size(); i++) {
                    const auto& polygon = polygons[i];
                    const Vector3<T>& local_face_normal = face_normals[i];

                    for (int vertex_index : polygon) {
                        vertex_normals[vertex_index] += local_face_normal;
                    }
                }

                for (auto& vertex : vertex_normals) {
                    vertex = vertex.normalized();
                }
            }
    };
}