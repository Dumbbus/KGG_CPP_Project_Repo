//
// Created by shulz on 18.12.2025.
//

#ifndef KGG_CPP_PROJECT_REPO_COLOR_HPP
#define KGG_CPP_PROJECT_REPO_COLOR_HPP

namespace render {
    struct Color {
        std::uint8_t r, g, b, a;

        constexpr Color(
            std::uint8_t r = 0,
            std::uint8_t g = 0,
            std::uint8_t b = 0,
            std::uint8_t a = 255
        ) : r(r), g(g), b(b), a(a) {}

        static constexpr Color black() { return Color(0, 0, 0, 255); }
        static constexpr Color white() { return Color(255, 255, 255, 255); }
        static constexpr Color red() { return Color(255, 0, 0, 255); }
        static constexpr Color green() { return {0, 255, 0, 255}; }
        static constexpr Color blue() { return {0, 0, 255, 255}; }
        static constexpr Color yellow() { return {255, 255, 0, 255}; }
    };
}


#endif //KGG_CPP_PROJECT_REPO_COLOR_HPP