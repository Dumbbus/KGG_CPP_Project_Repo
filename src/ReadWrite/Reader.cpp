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

Object Reader::Read(const std::string filename) {
    Vertex vertex;
    Object object3d;
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        cout << line << endl;
        istringstream iss(line);
        char type;
        iss >> type;
        switch(type) {
            case 'v':
                float x, y, z;
                iss >> x >> y >> z;
                vertex = {{x, y, z}, {0, 0, 1}  };
                object3d.mesh.m_vertices.push_back(vertex);
                break;
            case 'f':
                std::vector<int> vertices;
                int index;

                while (iss >> index) {
                    vertices.push_back(index - 1);
                }

                if (vertices.size() == 3) {
                    object3d.mesh.m_faces.push_back({vertices[0], vertices[1], vertices[2]});
                }
                else if (vertices.size() > 3) {
                    for (size_t i = 1; i < vertices.size() - 1; i++) {
                        object3d.mesh.m_faces.push_back({
                            vertices[0],
                            vertices[i],
                            vertices[i + 1]
                        });
                    }
                }
                break;
        }

    }

    object3d.mesh.recompute_normals();

    return object3d;
}