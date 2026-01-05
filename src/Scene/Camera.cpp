//
// Created by lunarimoonlin on 12/14/25.
//

#include <Scene/Camera.h>
#include <Math/Vector3.hpp>

#include "Math/Vector4.hpp"

Camera::Camera(gmath::Vector3d eye, gmath::Vector3d target, gmath::Vector3d up)
    : m_eye(eye), m_target(target), m_up(up) {}

gmath::Matrix4d Camera::get_view_matrix() {
    // В правосторонней системе (OpenGL) камера смотрит в -Z
    gmath::Vector3d z_axis = (m_eye - m_target).normalized();
    gmath::Vector3d x_axis = m_up.cross(z_axis).normalized();
    gmath::Vector3d y_axis = z_axis.cross(x_axis);

    gmath::Matrix4d view = gmath::Matrix4d::edinich();

    // Верхняя левая часть 3x3 — это транспонированная матрица базиса камеры
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
