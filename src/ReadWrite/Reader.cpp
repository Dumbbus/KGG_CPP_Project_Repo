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
    int face_count = 0;
    char delim = '/';
    Vertex vertex;
    Object object3d;
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        cout << line << endl;
        std::stringstream stringstream(line);
        std::string word;
        stringstream >> word;
        if (word == "v") {
            float x, y, z;
            stringstream >> x >> y >> z;
            vertex = {{x, y, z}, {0, 0, 1}  };
            object3d.mesh.m_vertices.push_back(vertex);
        }
        else if (word == "f") {
            face_count++;
            vector<int> face;
            vector<int> normal;
            vector<int> textIndicies;
            std::string s;

            while (stringstream >> s) {
                cout << s << endl;
                std::vector<std::string> result = splitWithEmpty(s, delim);
                for (int i = 0; i < result.size(); i++) {
                    cout << result[i] << endl;
                }
                face.push_back(std::stoi(result[0]));
                textIndicies.push_back(std::stoi(result[1]));
                normal.push_back(std::stoi(result[2]));
            }
            try {
                if (face.size() < 3) {
                    throw invalid_argument("Face " + to_string(face_count) + " has less tan 3 vertecies");
                }
            }
            catch (invalid_argument e) {
                std::cerr <<"Error: " << e.what() << std::endl;
            }
            if (face.size() == 3) {
                object3d.mesh.m_faces.push_back(face);
                object3d.mesh.text_indiciess.push_back(textIndicies);
                object3d.mesh.vert_normals.push_back(normal);
            }
            else if (face.size() > 3) {
                for (size_t i = 1; i < face.size() - 1; i++) {
                    object3d.mesh.m_faces.push_back({
                        face[0],
                        face[i],
                        face[i + 1]
                    });
                }
            }
        }
        else if (word == "vn") {

        }
        else if (word == "vt") {

        }
    }

    object3d.mesh.recompute_normals();

    return object3d;
}