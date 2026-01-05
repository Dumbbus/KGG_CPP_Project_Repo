//
// Created by lunarimoonlin on 1/5/26.
//

#ifndef KGG_CPP_PROJECT_REPO_SCENE_H
#define KGG_CPP_PROJECT_REPO_SCENE_H
#include "Camera.h"
#include "Projection.h"
#include "ReadWrite/Object.hpp"
#include "ReadWrite/Reader.h"


class Scene {
    public:
    Camera camera;
    Projection projection;
    std::vector<Object> objects3d;
    Scene() = default;
    Scene(Camera camera, Projection projection) : camera(camera), projection(projection){};
    void addObject3d(Object object3d);
};


#endif //KGG_CPP_PROJECT_REPO_SCENE_H