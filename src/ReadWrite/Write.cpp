//
// Created by lunarimoonlin on 1/16/26.
//
#include "../../include/ReadWrite/Write.h"
#include <fstream>
#include <iostream>

void Write::write(const Object& obj) {
    std::ofstream outputFile(obj.name);
    bool are_there_normals = false;
    bool are_there_uvs = false;
    if (!outputFile.is_open()) {
        std::cerr << "Error: Could not open the file for writing." << std::endl;// Return an error code
    }
    outputFile << "writer by moonlin" << std::endl;
    for (gmath::Vector3d vert : obj.mesh.m_vertexs) {
        outputFile << "v" << " " << std::to_string(vert.x) << " " << std::to_string(vert.y) << " " << std::to_string(vert.z) << std::endl;
    }
    for (gmath::Vector2d text : obj.mesh.m_uvs) {
        outputFile << "vt " << " " << std::to_string(text.x) << " " << std::to_string(text.y) << std::endl;
    }
    for (gmath::Vector3d normal : obj.mesh.m_face_normals) {
        outputFile << "vn" << " "<< std::to_string(normal.x) << " " << std::to_string(normal.y) << " " << std::to_string(normal.z) << std::endl;
    }
    if (obj.mesh.m_polygons.at(0).get_normals().size() > 0) {
        are_there_normals = true;
    }
    if (obj.mesh.m_polygons.at(0).get_uvs().size() > 0) {
        are_there_uvs = true;
    }
    if (!are_there_normals & !are_there_uvs) {
        for (Polygon poly : obj.mesh.m_polygons) {
            outputFile << "f" << " " << std::to_string(poly.get_vertexs().at(0) + 1) << " " <<
                    std::to_string(poly.get_vertexs().at(1) + 1) << " " << std::to_string(poly.get_vertexs().at(2) + 1)
                    << std::endl;
        }
    }
    else if (!are_there_normals & are_there_uvs) {
        for (Polygon poly : obj.mesh.m_polygons) {
            outputFile << "f" << " " << std::to_string(poly.get_vertexs().at(0) + 1) << "/" <<
                    std::to_string(poly.get_uvs().at(0) + 1) << " " << std::to_string(poly.get_vertexs().at(1) + 1) << "/" <<
                    std::to_string(poly.get_uvs().at(1) + 1) << " " << std::to_string(poly.get_vertexs().at(2) + 1) << "/" <<
                    std::to_string(poly.get_uvs().at(2) + 1) << std::endl;
        }
    }
    else if (are_there_normals & !are_there_uvs) {
        for (Polygon poly : obj.mesh.m_polygons) {
            outputFile << "f" << " " << std::to_string(poly.get_vertexs().at(0) + 1) << "//" <<
                    std::to_string(poly.get_normals().at(0) + 1) << " " << std::to_string(poly.get_vertexs().at(1) + 1) << "//"
                    << std::to_string(poly.get_normals().at(1) + 1) << "" << std::to_string(poly.get_vertexs().at(2) + 1) <<
                    "//" << std::to_string(poly.get_normals().at(2) + 1) << std::endl;
        }
    }
    else {
        for (Polygon poly : obj.mesh.m_polygons) {
            outputFile << "f" << " " << std::to_string(poly.get_vertexs().at(0) + 1) << "/" <<
                    std::to_string(poly.get_uvs().at(0) + 1) << "/" << std::to_string(poly.get_normals().at(0) + 1) << " " <<
                    std::to_string(poly.get_vertexs().at(1) + 1) << "/" << std::to_string(poly.get_uvs().at(1) + 1) << "/" <<
                    std::to_string(poly.get_normals().at(1) + 1) << " " << std::to_string(poly.get_vertexs().at(2) + 1) << "/"
                    << std::to_string(poly.get_uvs().at(2) + 1) << "/" << std::to_string(poly.get_normals().at(2) + 1) << " " <<
                    std::endl;
        }
    }
}

