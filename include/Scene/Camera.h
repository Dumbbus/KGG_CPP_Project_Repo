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

        gmath::Matrix4d look_at();
        void rotate_camera(float dx, float dy);
        void pan(float dx, float dy);

        gmath::Vector3d get_eye() const { return m_eye; }
        gmath::Vector3d get_target() const { return m_target; }
        gmath::Vector3d get_up() const { return m_up; }
        float get_yaw() const { return m_yaw; }
        float get_pitch() const { return m_pitch; }
        float get_distance() const { return m_distance; }

        void set_position(gmath::Vector3d pos) { m_eye = pos; }
        void set_target(gmath::Vector3d target) { m_target = target; }
        void set_up(gmath::Vector3d up) { m_up = up; }
        void set_yaw(float yaw) { m_yaw = yaw; }
        void set_pitch(float pitch) { m_pitch = pitch; }
        void set_distance(float distance) { m_distance = distance; }
    private:
        gmath::Vector3d m_eye;
        gmath::Vector3d m_target;
        gmath::Vector3d m_up;

        // Для поворота камеры
        float m_yaw; // горизонтальный
        float m_pitch; // вертикальный
        float m_distance;
};


#endif //KGG_CPP_PROJECT_REPO_CAMERA_H