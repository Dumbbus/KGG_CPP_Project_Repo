//
// Created by lunarimoonlin on 12/14/25.
//

#ifndef KGG_CPP_PROJECT_REPO_CAMERA_H
#define KGG_CPP_PROJECT_REPO_CAMERA_H
#include <Math/Vector3.hpp>

#include "Math/Matrix4.hpp"


class Camera {
    public:
    // static gmath::Vector3d look_direction_vector(gmath::Vector3d target, gmath::Vector3d eye);
        Camera(gmath::Vector3d eye, gmath::Vector3d target, gmath::Vector3d up);
        ~Camera() = default;

        gmath::Matrix4d get_view_matrix();

        gmath::Vector3d get_eye() const { return m_eye; }
        gmath::Vector3d get_target() const { return m_target; }
        gmath::Vector3d get_up() const { return m_up; }

        void set_position(gmath::Vector3d pos) { m_eye = pos; }
        void set_target(gmath::Vector3d target) { m_target = target; }
    private:
        gmath::Vector3d m_eye;
        gmath::Vector3d m_target;
        gmath::Vector3d m_up;
};


#endif //KGG_CPP_PROJECT_REPO_CAMERA_H