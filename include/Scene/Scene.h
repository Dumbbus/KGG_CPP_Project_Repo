//
// Created by lunarimoonlin on 1/5/26.
//

#ifndef KGG_CPP_PROJECT_REPO_SCENE_H
#define KGG_CPP_PROJECT_REPO_SCENE_H
#include "ReadWrite/Object.h"
#include "ReadWrite/Reader.h"


class Scene {
    public:
    std::vector<Object> objects3d;
    void addObject3d(Object object3d);
};


#endif //KGG_CPP_PROJECT_REPO_SCENE_H