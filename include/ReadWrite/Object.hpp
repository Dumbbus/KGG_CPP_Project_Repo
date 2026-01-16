#ifndef KGG_CPP_PROJECT_REPO_OBJECT_HPP
#define KGG_CPP_PROJECT_REPO_OBJECT_HPP

#include "Render/Mesh.hpp"
#include "Scene/Transform.h"
#include "Window/Framebuffer.h"

using namespace render;
    class Object {
    public:
        std::string name;
        Mesh mesh;
        Transform transform;
        Object() = default;
        Object(const Mesh& m) : mesh(m) {}
        Object(const Mesh& m, const Transform& t) : mesh(m), transform(t) {}};

#endif