//
// Created by lunarimoonlin on 12/14/25.
//

#ifndef KGG_CPP_PROJECT_REPO_MESH_H
#define KGG_CPP_PROJECT_REPO_MESH_H
#include "Math/Vector3.hpp"
#include <vector>

class Mesh {
    public:
        std::vector<gmath::Vector3<float>> vertices;
        std::vector<gmath::Vector3<float>> normals;
        std::vector<std::vector<int>> faces;


    private:
};


#endif //KGG_CPP_PROJECT_REPO_MESH_H