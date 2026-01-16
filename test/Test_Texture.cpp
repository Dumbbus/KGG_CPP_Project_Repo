//
// Created by shulz on 16.01.2026.
//

#include <gtest/gtest.h>
#include "Render/Texture.hpp"

class TextureTest : public ::testing::Test {
protected:
    Texture tex;

    // (0,0) - Черный, (1,0) - Красный
    // (0,1) - Зеленый, (1,1) - Синий
    void Setup2x2Texture() {
        tex.width = 2;
        tex.height = 2;
        tex.channels = 3;
        tex.pixels = {
            0,   0,   0,   // Black
            255, 0,   0,   // Red
            0,   255, 0,   // Green
            0,   0,   255  // Blue
        };
    }
};

// 1. Тест пустой текстуры
TEST_F(TextureTest, EmptyTextureSampling) {
    EXPECT_TRUE(tex.empty());
    render::Color c = tex.sample(0.5f, 0.5f);
    EXPECT_EQ(c.r, 255);
    EXPECT_EQ(c.g, 255);
    EXPECT_EQ(c.b, 255);
}

// 2. Тест координат (UV Sampling)
TEST_F(TextureTest, UVSamplingCorners) {
    Setup2x2Texture();

    // Левый нижний угол (UV: 0, 0) -> Массив: x=0, y=1 (Зеленый)
    render::Color bl = tex.sample(0.0f, 0.0f);
    EXPECT_EQ(bl.g, 255);
    EXPECT_EQ(bl.r, 0);

    // Правый верхний угол (UV: 1, 1) -> Массив: x=1, y=0 (Красный)
    render::Color tr = tex.sample(1.0f, 1.0f);
    EXPECT_EQ(tr.r, 255);
    EXPECT_EQ(tr.b, 0);
}

// 3. Тест Clamp (Ограничение координат)
TEST_F(TextureTest, ClampingTest) {
    Setup2x2Texture();

    // Координаты за пределами [0, 1] должны сэмплить крайние пиксели
    render::Color c1 = tex.sample(1.5f, 1.5f); // Должно стать (1.0, 1.0)
    render::Color c2 = tex.sample(1.0f, 1.0f);

    EXPECT_EQ(c1.r, c2.r);
    EXPECT_EQ(c1.g, c2.g);
    EXPECT_EQ(c1.b, c2.b);
}

// 4. Тест альфа-канала (3 vs 4 канала)
TEST_F(TextureTest, AlphaChannelHandling) {
    tex.width = 1;
    tex.height = 1;
    tex.channels = 4;
    tex.pixels = {10, 20, 30, 128}; // Альфа = 128

    render::Color c = tex.sample(0, 0);
    EXPECT_EQ(c.a, 128);

    tex.channels = 3; // Переключаем на RGB
    c = tex.sample(0, 0);
    EXPECT_EQ(c.a, 255); // Должно быть 255 (непрозрачный)
}