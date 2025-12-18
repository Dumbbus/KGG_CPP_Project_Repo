//
// Created by shulz on 18.12.2025.
//
#pragma once

#ifndef KGG_CPP_PROJECT_REPO_FRAMEBUFFER_H
#define KGG_CPP_PROJECT_REPO_FRAMEBUFFER_H

#include <cstdint>
#include <vector>
#include <Window/Color.hpp>

namespace render {
    class Framebuffer {
        public:
            Framebuffer(uint32_t  width, uint32_t  height);

            void clear(const Color& color);
            void set_pixel(int  x, int y, const Color& color);

            [[nodiscard]] const uint8_t* get_data() const;
            [[nodiscard]] uint32_t  get_width() const;
            [[nodiscard]] uint32_t  get_height() const;

        private:
            uint32_t m_width, m_height;
            std::vector<std::uint8_t> m_colorBuffer; // RGBA
    };
}

#endif //KGG_CPP_PROJECT_REPO_FRAMEBUFFER_H