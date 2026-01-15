//
// Created by shulz on 14.01.2026.
//

#ifndef KGG_CPP_PROJECT_REPO_TEXTURE_HPP
#define KGG_CPP_PROJECT_REPO_TEXTURE_HPP
#include <vector>

#include "Window/Color.hpp"

struct Texture {
    int width = 0;
    int height = 0;
    int channels = 0; // RGB, RGBA (3, 4)

    std::vector<std::uint8_t> pixels;

    bool empty() const {
        return pixels.empty();
    }

    render::Color sample(float u, float v) const;
};

#endif //KGG_CPP_PROJECT_REPO_TEXTURE_HPP