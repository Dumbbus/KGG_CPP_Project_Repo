//
// Created by shulz on 16.01.2026.
//

#include <gtest/gtest.h>
#include "Render/Rasterizer.h"

namespace render {

class RasterizerTest : public ::testing::Test {
protected:
    Framebuffer fb{10, 10};
    Rasterizer rasterizer;
    Color white = {255, 255, 255, 255};
    Color black = {0, 0, 0, 255};
    gmath::Vector3f light_dir = {0, 0, 1}; // Свет светит "в экран"
};

// 1. Тест Wireframe (Рисование линий)
TEST_F(RasterizerTest, WireframeBasicLine) {
    fb.clear(black);

    // Создаем одну линию через структуру ProcessedVertex
    std::vector<ProcessedVertex> vertices(3);
    vertices[0] = {{0, 0, 0.5}, {0, 0, 1}, {0, 0}, 1.0, true};
    vertices[1] = {{9, 0, 0.5}, {0, 0, 1}, {1, 0}, 1.0, true};
    vertices[2] = {{0, 9, 0.5}, {0, 0, 1}, {0, 1}, 1.0, true};

    rasterizer.draw_wireframe(fb, vertices, white);

    const uint8_t* data = fb.get_data();
    // Проверяем, что начало и конец линии закрашены
    EXPECT_EQ(data[0], 255); // Точка (0,0)
    // Проверяем точку (5,0) - середина горизонтальной линии
    EXPECT_EQ(data[(0 * 10 + 5) * 4], 255);
}

// 2. Тест заполнения треугольника и освещения
TEST_F(RasterizerTest, TriangleFillAndAmbient) {
    fb.clear(black);

    // Треугольник на весь экран (10x10)
    std::vector<ProcessedVertex> vertices = {
        {{0, 0, 0.5}, {0, 0, 1}, {0, 0}, 1.0, true},
        {{9, 0, 0.5}, {0, 0, 1}, {1, 0}, 1.0, true},
        {{0, 9, 0.5}, {0, 0, 1}, {0, 1}, 1.0, true}
    };
    std::vector<gmath::Vector3d> face_normals = {{0, 0, 1}};

    // Рисуем с ambient = 0.5 и без прямого света (свет сбоку)
    gmath::Vector3f side_light = {1, 0, 0};
    rasterizer.draw_scene(fb, vertices, face_normals, nullptr, true, side_light, 0.5f, white);

    const uint8_t* data = fb.get_data();
    // Пиксель внутри треугольника (1,1). Ожидаем яркость ~127 (0.5 от 255)
    int idx = (1 * 10 + 1) * 4;
    EXPECT_NEAR(data[idx], 127, 2);
}

// 3. Тест отсечения невалидных вершин
TEST_F(RasterizerTest, SkipInvalidVertices) {
    fb.clear(black);

    std::vector<ProcessedVertex> vertices = {
        {{5, 5, 0.5}, {0, 0, 1}, {0, 0}, 1.0, false},
        {{9, 0, 0.5}, {0, 0, 1}, {1, 0}, 1.0, true},
        {{0, 9, 0.5}, {0, 0, 1}, {0, 1}, 1.0, true}
    };
    std::vector<gmath::Vector3d> face_normals = {{0, 0, 1}};

    rasterizer.draw_scene(fb, vertices, face_normals, nullptr, true, light_dir, 1.0f, white);

    const uint8_t* data = fb.get_data();
    // Буфер должен остаться черным, так как одна вершина была невалидна
    EXPECT_EQ(data[(5 * 10 + 5) * 4], 0);
}

// 4. Тест интерполяции Z-буфера внутри растеризатора
TEST_F(RasterizerTest, RasterizerDepthInterpolation) {
    fb.clear(black);
    fb.clear_depth(1.0f);

    // Треугольник под наклоном: лево(Z=0.1) -> право(Z=0.9)
    std::vector<ProcessedVertex> vertices = {
        {{0, 0, 0.1}, {0, 0, 1}, {0, 0}, 1.0, true},
        {{9, 0, 0.9}, {0, 0, 1}, {1, 0}, 1.0, true},
        {{0, 9, 0.5}, {0, 0, 1}, {0, 1}, 1.0, true}
    };
    std::vector<gmath::Vector3d> face_normals = {{0, 0, 1}};

    rasterizer.draw_scene(fb, vertices, face_normals, nullptr, true, light_dir, 1.0f, white);

    // Мы не можем напрямую достать Z из FB (нет геттера), но можем проверить через перезапись
    // Рисуем точку в (1,0) с Z=0.5. Она должна перекрыть наш треугольник, если там Z > 0.5
    // В (1,0) Z треугольника примерно 0.1 + (0.9-0.1)*0.1 = 0.18.
    // Значит точка с Z=0.5 НЕ должна нарисоваться.
    Color red = {255, 0, 0, 255};
    fb.set_pixel(1, 0, red, 0.5f);

    const uint8_t* data = fb.get_data();
    EXPECT_EQ(data[(0 * 10 + 1) * 4 + 0], 255); // Остался белый
    EXPECT_EQ(data[(0 * 10 + 1) * 4 + 1], 255);
}

} // namespace render