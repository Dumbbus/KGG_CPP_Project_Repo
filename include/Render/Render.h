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

struct ProcessedVertex {
    gmath::Vector3d position;
    gmath::Vector3d normal;
};

class Render {
    public:
    static std::vector<gmath::Vector3d> process_mesh(
        const std::vector<gmath::Vector3d> &vertices,
        const gmath::Matrix4d &transform_martix,
        const gmath::Matrix4d &projection_martix,
        const gmath::Matrix4d &view_martix,
        double width,
        double height
    );

    static std::vector<ProcessedVertex> process_mesh_with_normals(
    const std::vector<gmath::Vector3d> &vertices,
    const std::vector<gmath::Vector3d> &normals,
    const gmath::Matrix4d &transform_martix,
    const gmath::Matrix4d &projection_martix,
    const gmath::Matrix4d &view_martix,
    const double width,
    const double height
    );

    static std::vector<gmath::Vector3d> process_face_normals(
        const std::vector<gmath::Vector3d>& face_normals,
        const gmath::Matrix4d &transform_martix,
        const gmath::Matrix4d &projection_martix,
        const gmath::Matrix4d &view_martix
    );
};


#endif //KGG_CPP_PROJECT_REPO_RENDER_H