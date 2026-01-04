//
// Created by akemi on 03.01.2026.
//
#include "Scene/Transform.h"

Transform::Transform()
    : m_position(0, 0, 0),
    m_rotation(0, 0, 0),
    m_scale(1, 1, 1),
    m_dirty(true) {}

void Transform::translate(const gmath::Vector3d& delta) {
    m_position += delta;
    m_dirty = true;
}

void Transform::rotate(const gmath::Vector3d delta_euler) {
    m_rotation += delta_euler;
    m_dirty = true;
}

void Transform::update_martix() const {
    if (!m_dirty) return;

    m_model_cache = gmath::Matrix4d::translation(m_position) *
                    gmath::Matrix4d::rotation_x(m_rotation.x) *
                    gmath::Matrix4d::rotation_y(m_rotation.y) *
                    gmath::Matrix4d::rotation_z(m_rotation.z) *
                    gmath::Matrix4d::scale(m_scale);

    m_dirty = false;
}

gmath::Matrix4d Transform::get_model_matrix() const {
    update_martix();
    return m_model_cache;
}