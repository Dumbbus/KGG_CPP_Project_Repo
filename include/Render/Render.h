//
// Created by lunarimoonlin on 12/14/25.
//

#ifndef KGG_CPP_PROJECT_REPO_RENDER_H
#define KGG_CPP_PROJECT_REPO_RENDER_H

#include "Mesh.hpp"
#include "Scene/Transform.h"
#include "Scene/Camera.h"
#include "Scene/Projection.h"
#include <vector>

struct ProcessedVertex {
    gmath::Vector3<double> position;
    gmath::Vector3<double> normal;
    gmath::Vector2<double> uv;
    double inv_w; // 1 / w
    bool valid;
};

class Render {
public:
    static std::vector<ProcessedVertex> process_mesh(
        const Mesh& mesh,
        const gmath::Matrix4d& model,
        const gmath::Matrix4d& view,
        const gmath::Matrix4d& projection,
        double width,
        double height
    );

    static std::vector<gmath::Vector3d> process_face_normals(
        const std::vector<gmath::Vector3d> &face_normals,
        const gmath::Matrix4d& model,
        const gmath::Matrix4d& view
        );
};
#endif //KGG_CPP_PROJECT_REPO_RENDER_H