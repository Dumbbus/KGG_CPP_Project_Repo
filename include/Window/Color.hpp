#ifndef KGG_CPP_PROJECT_REPO_COLOR_HPP
#define KGG_CPP_PROJECT_REPO_COLOR_HPP

#include <algorithm>
#include <cstdint>

namespace render {
    struct Color {
        std::uint8_t r, g, b, a;

        constexpr Color(
            std::uint8_t r = 0,
            std::uint8_t g = 0,
            std::uint8_t b = 0,
            std::uint8_t a = 255
        ) : r(r), g(g), b(b), a(a) {}

        explicit Color(double r_f, double g_f, double b_f, double a_f = 255.0) {
            r = static_cast<std::uint8_t>(std::clamp(r_f, 0.0, 255.0));
            g = static_cast<std::uint8_t>(std::clamp(g_f, 0.0, 255.0));
            b = static_cast<std::uint8_t>(std::clamp(b_f, 0.0, 255.0));
            a = static_cast<std::uint8_t>(std::clamp(a_f, 0.0, 255.0));
        }

        static constexpr Color black()  { return Color(static_cast<std::uint8_t>(0), 0, 0, 255); }
        static constexpr Color white()  { return Color(static_cast<std::uint8_t>(255), 255, 255, 255); }
        static constexpr Color red()    { return Color(static_cast<std::uint8_t>(255), 0, 0, 255); }
        static constexpr Color green()  { return Color(static_cast<std::uint8_t>(0), 255, 0, 255); }
        static constexpr Color blue()   { return Color(static_cast<std::uint8_t>(0), 0, 255, 255); }
        static constexpr Color yellow() { return Color(static_cast<std::uint8_t>(255), 255, 0, 255); }
    };
}

#endif //KGG_CPP_PROJECT_REPO_COLOR_HPP