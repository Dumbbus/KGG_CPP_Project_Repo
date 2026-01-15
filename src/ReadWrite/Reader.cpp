#include "../../include/ReadWrite/Reader.h"
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm> // для std::replace
#include "Render/Polygon.hpp"
#include <ReadWrite/Object.hpp>

using namespace std;

// Вспомогательная функция для обработки индексов OBJ (они начинаются с 1)
int fix_index(int idx, size_t current_size) {
    if (idx > 0) return idx - 1;
    if (idx < 0) return static_cast<int>(current_size) + idx;
    return -1;
}

Object Reader::Read(const std::string& filename) {
    Object object3d;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << filename << endl;
        return object3d;
    }

    string line;
    while (getline(file, line)) {
        // Убираем лишние пробелы в начале строки
        line.erase(0, line.find_first_not_of(" \t\r\n"));
        if (line.empty() || line[0] == '#') continue;

        istringstream iss(line);
        string type;
        iss >> type;

        if (type == "v") {
            double x, y, z;
            iss >> x >> y >> z;
            object3d.mesh.m_vertexs.push_back({x, y, z});
        }
        else if (type == "vt") {
            double u, v;
            iss >> u >> v;
            object3d.mesh.m_uvs.push_back({u, v});
        }
        else if (type == "f") {
            vector<int> vertex_indices;
            vector<int> uv_indices;
            vector<int> normal_indices;

            string token;
            while (iss >> token) {
                // В OBJ токены грани могут быть: v, v/vt, v//vn, v/vt/vn
                int vi = 0, vti = 0, vni = 0;

                // Считаем количество слешей, чтобы понять формат
                size_t first_slash = token.find('/');
                size_t last_slash = token.rfind('/');

                if (first_slash == string::npos) {
                    // Формат: f v1 v2 v3
                    vi = stoi(token);
                } else {
                    // Формат: v/...
                    vi = stoi(token.substr(0, first_slash));

                    if (first_slash == last_slash) {
                        // Формат: f v/vt
                        vti = stoi(token.substr(first_slash + 1));
                    } else if (last_slash == first_slash + 1) {
                        // Формат: f v//vn
                        vni = stoi(token.substr(last_slash + 1));
                    } else {
                        // Формат: f v/vt/vn
                        vti = stoi(token.substr(first_slash + 1, last_slash - first_slash - 1));
                        vni = stoi(token.substr(last_slash + 1));
                    }
                }

                vertex_indices.push_back(fix_index(vi, object3d.mesh.m_vertexs.size()));
                uv_indices.push_back(vti != 0 ? fix_index(vti, object3d.mesh.m_uvs.size()) : -1);
                normal_indices.push_back(vni != 0 ? fix_index(vni, object3d.mesh.m_normals.size()) : -1);
            }

            // Триангуляция
            for (size_t i = 1; i + 1 < vertex_indices.size(); ++i) {
                vector<int> v_idx = {vertex_indices[0], vertex_indices[i], vertex_indices[i + 1]};
                vector<int> n_idx = {normal_indices[0], normal_indices[i], normal_indices[i + 1]};
                vector<int> uv_idx = {uv_indices[0], uv_indices[i], uv_indices[i + 1]};

                object3d.mesh.m_polygons.emplace_back(v_idx, n_idx, uv_idx);
            }
        }
        else if (type == "o" || type == "g" || type == "usemtl" || type == "s" || type == "mtllib") {
            // Игнорируем метаданные: название объекта, группы, материалы и сглаживание
            continue;
        }
    }

    if (object3d.mesh.m_normals.empty()) {
        object3d.mesh.recompute_normals();

        for (auto& poly : object3d.mesh.m_polygons) {
            std::vector<int> v_indices = poly.get_vertexs();
            poly.set_normals(v_indices);
        }
    }

    object3d.mesh.set_dull_uv();

    return object3d;
}
