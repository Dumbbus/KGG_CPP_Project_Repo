//
// Created by lunarimoonlin on 12/14/25.
//

#ifndef KGG_CPP_PROJECT_REPO_CAMERA_H
#define KGG_CPP_PROJECT_REPO_CAMERA_H
#include "Vector3.hpp"


class Camera {
    public: gmath::Vector3d look_direction_vector(gmath::Vector3d target, gmath::Vector3d eye);
};


#endif //KGG_CPP_PROJECT_REPO_CAMERA_H