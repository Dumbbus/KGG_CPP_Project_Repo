//
// Created by akemi on 03.01.2026.
//

#ifndef KGG_CPP_PROJECT_REPO_TRANSFORM_H
#define KGG_CPP_PROJECT_REPO_TRANSFORM_H
#include "Math/Matrix4.hpp"
#include "Math/Vector3.hpp"

class Transform {
    public:
        Transform();
        //Transform(gmath::Matrix4d model);
        ~Transform() = default;

        void set_position(const gmath::Vector3d& pos) { m_position = pos; m_dirty = true; }
        void set_rotation(const gmath::Vector3d& euler) { m_rotation = euler; m_dirty = true; }
        void set_scale(const gmath::Vector3d& s) { m_scale = s; m_dirty = true; }

        void translate(const gmath::Vector3d& delta);
        void rotate(const gmath::Vector3d &delta_euler);

        gmath::Matrix4d get_model_matrix() const;

    private:
        gmath::Vector3d m_position;
        gmath::Vector3d m_rotation;
        gmath::Vector3d m_scale;

        mutable gmath::Matrix4d m_model_cache;
        mutable bool m_dirty; // Для того, нужно ли обновить матрицу

        void update_matrix() const;
};

#endif //KGG_CPP_PROJECT_REPO_TRANSFORM_H