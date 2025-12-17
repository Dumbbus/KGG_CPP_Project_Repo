//
// Created by lunarimoonlin on 12/14/25.
//

#include "../Headers/Camera.h"
#include "Vector3.hpp"

gmath::Vector3d Camera::look_direction_vector(gmath::Vector3d target, gmath::Vector3d eye) {
    gmath::Vector3d z = target-eye;
    return z;
}
