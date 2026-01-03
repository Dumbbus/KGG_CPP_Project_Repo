//
// Created by akemi on 03.01.2026.
//

#ifndef KGG_CPP_PROJECT_REPO_TRANSFORM_H
#define KGG_CPP_PROJECT_REPO_TRANSFORM_H
#include "Math/Vector3.hpp"

gmath::Vector3<float> position(gmath::Vector4<float> vertex);
gmath::Vector3<float> rotation(gmath::Vector4<float> vertex);
gmath::Vector3<float> scale(gmath::Vector4<float> vertex);

#endif //KGG_CPP_PROJECT_REPO_TRANSFORM_H