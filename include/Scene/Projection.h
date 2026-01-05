//
// Created by akemi on 05.01.2026.
//

#ifndef KGG_CPP_PROJECT_REPO_PROJECTION_H
#define KGG_CPP_PROJECT_REPO_PROJECTION_H
#include "Math/Matrix4.hpp"

class Projection {
    public:
        Projection(double fov, double aspect_ratio, double near_plane, double far_plane)
            : m_fov(fov), m_aspect_ratio(aspect_ratio),
            m_near_plane(near_plane), m_far_plane(far_plane) {}
        ~Projection() = default;

        gmath::Matrix4d get_projection_matrix() const;

        void set_fov(double fov) { m_fov = fov; }
        void set_aspect_ratio(double ratio) { m_aspect_ratio = ratio; }
        void set_near_plane(double near_plane) { m_near_plane = near_plane; }
        void set_far_plane(double far_plane) { m_far_plane = far_plane; }
    private:
        double m_fov; // Примем его за градусы
        double m_aspect_ratio;
        double m_near_plane;
        double m_far_plane;
};

#endif //KGG_CPP_PROJECT_REPO_PROJECTION_H