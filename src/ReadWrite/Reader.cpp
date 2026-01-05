//
// Created by lunarimoonlin on 12/30/25.
//
#include "../../include/ReadWrite/Reader.h"
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

    Object Reader::Read(const std::string filename) {
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
                    object3d.vertices.emplace_back(x, y, z);
                    break;
                case 'f':
                    int v1, v2, v3;
                    iss >> v1 >> v2 >> v3;
                    object3d.faces.emplace_back(v1 - 1, v2 - 1, v3 - 1);
                    break;
            }

        }
        return object3d;
    }