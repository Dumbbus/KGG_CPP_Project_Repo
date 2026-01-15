//
// Created by lunarimoonlin on 12/30/25.
//
#include "../../include/ReadWrite/Reader.h"
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <ReadWrite/Object.hpp>
using namespace std;

std::vector<std::string> splitWithEmpty(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    // Use getline to capture empty tokens
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    // Handle trailing delimiter case if needed (getline won't add last empty)
    if (!s.empty() && s.back() == delimiter) {
        tokens.push_back("");
    }
    return tokens;
}

Object Reader::Read(const std::string filename) {
    bool are_normals_present = true;
    bool is_default_uv_needed = true;
    char delim = '/';
    Object object3d;
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        //cout << line << endl;
        std::stringstream stringstream(line);
        std::string word;
        stringstream >> word;
        if (word == "v") {
            double x, y, z;
            stringstream >> x >> y >> z;
            gmath::Vector3<double> vertex = {x-1, y-1, z-1};
            object3d.mesh.m_vertexs.emplace_back(vertex);
        }
        else if (word == "f") {
            int face_count = 0;
            int normal_count = 0;
            int texture_count = 0;
            vector<int> face;
            vector<int> normal;
            vector<int> textIndicies;
            std::string s;

            while (stringstream >> s) {
                face_count++;
                normal_count++;
                texture_count++;
                cout << s << endl;
                std::vector<std::string> result = splitWithEmpty(s, delim);
                face.emplace_back(std::stoi(result[0])-1);
                switch (result.size()) {
                    case 1:
                        are_normals_present = false;
                    case 2:
                        are_normals_present = false;
                        is_default_uv_needed = false;
                        textIndicies.emplace_back(std::stoi(result[1])-1);
                        break;
                    case 3:
                        if (result[1] != "") {
                            textIndicies.emplace_back(std::stoi(result[1])-1);
                            normal.emplace_back(std::stoi(result[2])-1);
                            is_default_uv_needed = false;
                        } else {
                            is_default_uv_needed = true;
                            normal.emplace_back(std::stoi(result[2])-1);
                        }
                }
            }
            try {
                if (face.size() < 3) {
                    throw invalid_argument("Face " + to_string(face_count) + " has less tan 3 vertecies");
                }
                if (are_normals_present && normal.size() < 3) {
                    throw invalid_argument("Normal " + to_string(normal_count) + " has less tan 3 vertecies");
                }
                if (!is_default_uv_needed && textIndicies.size() < 3) {
                    throw invalid_argument("TextureFace " + to_string(texture_count) + " has less tan 3 vertecies");
                }
            }
            catch (invalid_argument e) {
                std::cerr <<"Error: " << e.what() << std::endl;
            }
            if (face.size() == 3) {
                Polygon polygon;
                polygon.set_vertexs(face);
                polygon.set_normals(normal);
                polygon.set_uvs(textIndicies);
                object3d.mesh.m_polygons.emplace_back(polygon);
            }
            else if (face.size() > 3) {
                for (size_t i = 1; i < face.size() - 1; i++) {
                    Polygon polygon;
                    polygon.set_vertexs({face[0],face[i],face[i + 1]});
                    polygon.set_normals({normal[0],normal[i],normal[i + 1]});
                    polygon.set_uvs({textIndicies[0],textIndicies[i],textIndicies[i + 1]});
                    object3d.mesh.m_polygons.emplace_back(polygon);
                }
            }
        }
        else if (word == "vn") {
            double x, y, z;
            stringstream >> x >> y >> z;
            gmath::Vector3<double> vertex = {x, y, z};
            object3d.mesh.m_normals.emplace_back(vertex);
        }
        else if (word == "vt") {
            double x, y;
            stringstream >> x >> y;
            gmath::Vector2<double> vertex = {x, y};
            object3d.mesh.m_uvs.emplace_back(vertex);
        }
    }
    if (is_default_uv_needed) {
        object3d.mesh.set_dull_uv();
    }
    object3d.mesh.recompute_normals();

    return object3d;
}