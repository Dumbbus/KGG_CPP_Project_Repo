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

struct Viewport {
    double height;
    double width;
};

class Render {
    public:
    static std::vector<gmath::Vector3d> process_mesh(
                const Mesh& mesh,
                const Transform& transform,
                Camera& camera,
                Projection& projection,
                const Viewport& viewport
        );

    std::vector<gmath::Vector3d> process_mesh(
        const std::vector<gmath::Vector3d> &vertices,
        const gmath::Matrix4d &transform_martix,
        const gmath::Matrix4d &projection_martix,
        const gmath::Matrix4d &view_martix,
        double width,
        double height
    );
};


#endif //KGG_CPP_PROJECT_REPO_RENDER_H