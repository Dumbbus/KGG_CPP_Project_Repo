//
// Created by lunarimoonlin on 12/30/25.
//
#include "../../include/ReadWrite/Reader.h"
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
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
                    int v1, v2, v3;
                    iss >> v1 >> v2 >> v3;
                    //object3d.mesh.m_indices.push_back({v1-1, v2-1, v3-1}); если заменишь на вектор, то это
                    //раскоментировать и доделать чтобы передавался вектор Vector3 с этими значениями
                    object3d.mesh.m_indices.push_back(v1-1);
                    object3d.mesh.m_indices.push_back(v2-1);
                    object3d.mesh.m_indices.push_back(v3-1);
                    break;
            }

        }
        return object3d;
    }