//
// Created by akemi on 17.01.2026.
//

#ifndef KGG_CPP_PROJECT_REPO_LIGHT_POINT_H
#define KGG_CPP_PROJECT_REPO_LIGHT_POINT_H

#include "Math/Vector3.hpp"
#include "Math/Vector4.hpp"
#include "Math/Matrix4.hpp"
#include "Window/Color.hpp"
#include <vector>

struct Light {
    gmath::Vector3f position;
    render::Color color;
    float intensity;
};

class Light_Point {
private:
    std::vector<Light> lights;
public:
    Light_Point() = default;
    Light_Point(std::vector<Light> lights) : lights(lights) {}
    ~Light_Point() = default;

    std::vector<Light> get_lights() {
        return lights;
    }

    void add_light(Light light) {
        lights.push_back(light);
    };

    std::vector<Light> transfer_light_to_view(const gmath::Matrix4d& view, const gmath::Matrix4d& projection, double width, double height) {
        std::vector<Light> lights_new;
        for (const auto& light : lights) {
            gmath::Vector4d light_pos = {(double)light.position.x, (double)light.position.y, (double)light.position.z, 1.0};

            gmath::Vector4d light_in_view = view * light_pos;
            gmath::Vector3f light_float = {(float)light_in_view.x, (float)light_in_view.y, (float)light_in_view.z};

            lights_new.push_back({light_float, light.color, light.intensity});
        }
        return lights_new;
    }
};

#endif //KGG_CPP_PROJECT_REPO_LIGHT_POINT_H