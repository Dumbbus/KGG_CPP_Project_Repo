//
// Created by shulz on 18.12.2025.
//
#pragma once

#include "Window/Framebuffer.h"
#include <algorithm>
#include <cstdint>

namespace render {
    Framebuffer::Framebuffer(uint32_t width, uint32_t height)
        : m_width(width),
        m_height(height),
        m_colorBuffer(width * height * 4),
        m_depthBuffer(width * height, 1.0f)
    {}

    void Framebuffer::clear(const Color &color) {
        for (size_t i = 0; i< m_width * m_height; i++) {
            m_colorBuffer[i * 4] = color.r;
            m_colorBuffer[i * 4 + 1] = color.g;
            m_colorBuffer[i * 4 + 2] = color.b;
            m_colorBuffer[i * 4 + 3] = color.a;
            m_depthBuffer[i] = 1.0f;
        }
    }

    void Framebuffer::clear_depth(const float depth) {
        std::fill(m_depthBuffer.begin(), m_depthBuffer.end(), depth);
    }

    // Пока что depth[0, 1], чем число меньше, тем ближе к "камере"
    void Framebuffer::set_pixel(int x, int y, const Color &color, float depth) {
        if (x < 0 || x >= static_cast<int>(m_width) || y < 0 || y >= static_cast<int>(m_height)) {
            return;
        }

        const size_t index = y * m_width + x;

        if (depth >= m_depthBuffer[index]) {
            return;
        }

        m_depthBuffer[index] = depth;

        size_t index_color_size = index * 4;
        m_colorBuffer[index_color_size + 0] = color.r;
        m_colorBuffer[index_color_size + 1] = color.g;
        m_colorBuffer[index_color_size + 2] = color.b;
        m_colorBuffer[index_color_size + 3] = color.a;
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
