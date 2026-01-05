//
// Created by akemi on 05.01.2026.
//

#include "Scene/Projection.h"

gmath::Matrix4d Projection::get_projection_matrix() const {
    gmath::Matrix4d projection_matrix = gmath::Matrix4d::perspective(m_fov, m_aspect_ratio, m_near_plane, m_far_plane);

    return projection_matrix;
}
