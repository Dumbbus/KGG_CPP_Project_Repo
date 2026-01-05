#ifndef KGG_CPP_PROJECT_REPO_OBJECT_HPP
#define KGG_CPP_PROJECT_REPO_OBJECT_HPP

#include "Render/Mesh.hpp"
#include "Scene/Transform.h"

namespace render {
    class Object {
    public:
        Mesh mesh;
        Transform transform;

        Object(const Mesh& m) : mesh(m) {}
        Object(const Mesh& m, const Transform& t) : mesh(m), transform(t) {}
    };
}

#endif