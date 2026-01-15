//
// Created by shulz on 14.01.2026.
//

#include "Render/Texture.hpp"

#include <SFML/Graphics/Image.hpp>

render::Color Texture::sample(float u, float v) const {
    if (pixels.empty()) {
        return render::Color::white();
    }

    v = 1.0f - v;

    u = std::clamp(u, 0.f, 1.f);
    v = std::clamp(v, 0.f, 1.f);

    int x = static_cast<int>(u * (width - 1));
    int y = static_cast<int>(v * (height - 1));

    int index = (y * width + x) * channels;

    std::uint8_t r = pixels[index];
    std::uint8_t g = pixels[index + 1];
    std::uint8_t b = pixels[index + 2];
    std::uint8_t a = (channels == 4) ? pixels[index + 3] : 255;

    return {r, g, b, a};
}