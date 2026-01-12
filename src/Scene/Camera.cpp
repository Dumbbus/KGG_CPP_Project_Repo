//
// Created by lunarimoonlin on 12/14/25.
//

#include <algorithm>
#include <Scene/Camera.h>
#include <Math/Vector3.hpp>

#include "Math/Vector4.hpp"

Camera::Camera(gmath::Vector3d eye, gmath::Vector3d target, gmath::Vector3d up)
    : m_eye(eye), m_target(target), m_up(up) {
    gmath::Vector3d direction = (eye - m_target).normalized();
    m_distance = (eye - m_target).length();
    m_pitch = std::asin(direction.y);
    m_yaw = std::atan2(direction.z, direction.x);
}

void Camera::rotate_camera(float dx, float dy) {
    float rotation_speed = 0.005f;

    m_yaw += dx * rotation_speed;
    m_pitch += dy * rotation_speed;

    m_pitch = std::clamp(m_pitch, -1.55f, 1.55f);

    float cos_pitch = std::cos(m_pitch);
    gmath::Vector3d direction;
    direction.x = cos_pitch * std::cos(m_yaw);
    direction.y = std::sin(m_pitch);
    direction.z = cos_pitch * std::sin(m_yaw);

    m_eye = m_target + direction * m_distance;
}

void Camera::pan(float dx, float dy) {
    float pan_speed = 0.01f * m_distance;
    gmath::Vector3d z_axis = (m_eye - m_target).normalized();
    gmath::Vector3d x_axis = m_up.cross(z_axis).normalized();
    gmath::Vector3d y_axis = z_axis.cross(x_axis).normalized();

    gmath::Vector3d offset = -x_axis * dx * pan_speed + y_axis * dy * pan_speed;

    m_eye += offset;
    m_target += offset;
}


gmath::Matrix4d Camera::look_at() {
    // В правосторонней системе (OpenGL) камера смотрит в -Z
    gmath::Vector3d z_axis = (m_eye - m_target).normalized();
    gmath::Vector3d x_axis = m_up.cross(z_axis).normalized();
    gmath::Vector3d y_axis = z_axis.cross(x_axis);

    gmath::Matrix4d view = gmath::Matrix4d::edinich();

    // Строка 0
    view(0, 0) = x_axis.x;
    view(0, 1) = x_axis.y;
    view(0, 2) = x_axis.z;
    // Строка 1
    view(1, 0) = y_axis.x;
    view(1, 1) = y_axis.y;
    view(1, 2) = y_axis.z;
    // Строка 2
    view(2, 0) = z_axis.x;
    view(2, 1) = z_axis.y;
    view(2, 2) = z_axis.z;

    view(0, 3) = -x_axis.dot(m_eye);
    view(1, 3) = -y_axis.dot(m_eye);
    view(2, 3) = -z_axis.dot(m_eye);

    return view;
}
