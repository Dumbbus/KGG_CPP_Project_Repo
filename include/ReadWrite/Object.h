//
// Created by lunarimoonlin on 12/30/25.
//
#include <Math/Vector3.hpp>
#include <Math/Matrix3.hpp>
#include <Light/Normal.hpp>

#ifndef KGG_CPP_PROJECT_REPO_OBJECT_H
#define KGG_CPP_PROJECT_REPO_OBJECT_H


using namespace std;
using namespace gmath;

class Object {
    public:
    vector<Vector3<float>> vertices;
    vector<Vector3<float>> faces;
    vector<Normal<double>> normal;
    //vector<render::Color> color;
    vector<Matrix3<double>> rotation;
    vector<Matrix3<double>> translation;
    vector<Matrix3<double>> scale;
};


#endif //KGG_CPP_PROJECT_REPO_OBJECT_H