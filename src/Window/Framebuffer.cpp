//
// Created by shulz on 18.12.2025.
//
#pragma once

#include "Window/Framebuffer.h"
#include <algorithm>

namespace render {
    Framebuffer::Framebuffer(uint32_t width, uint32_t height)
        : m_width(width), m_height(height), m_colorBuffer(width * height * 4)
    {}

    void Framebuffer::clear(const Color &color) {
        for (uint32_t y = 0; y < m_height; ++y) {
            for (uint32_t x = 0; x < m_width; ++x) {
                set_pixel(x, y, color);
            }
        }
    }

    void Framebuffer::set_pixel(int x, int y, const Color &color) {
        if (x < 0 || x >= static_cast<int>(m_width) || y < 0 || y >= static_cast<int>(m_height)) {
            return;
        }

        const size_t index = (y * m_width + x) * 4;
        m_colorBuffer[index + 0] = color.r;
        m_colorBuffer[index + 1] = color.g;
        m_colorBuffer[index + 2] = color.b;
        m_colorBuffer[index + 3] = color.a;
    }

    // Получаем указатель на массив данных
    const uint8_t* Framebuffer::get_data() const {
        return m_colorBuffer.data();
    }

    uint32_t Framebuffer::get_width() const {
        return m_width;
    }

    uint32_t Framebuffer::get_height() const {
        return m_height;
    }
}
