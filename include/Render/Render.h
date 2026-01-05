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
};


#endif //KGG_CPP_PROJECT_REPO_RENDER_H