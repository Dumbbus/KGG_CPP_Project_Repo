#include <gtest/gtest.h>
#include "Window/Framebuffer.h"

namespace render {

class FramebufferTest : public ::testing::Test {
protected:
    uint32_t width = 100;
    uint32_t height = 100;
    Color red = {255, 0, 0, 255};
    Color blue = {0, 0, 255, 255};
};

// 1. Тест инициализации и размеров
TEST_F(FramebufferTest, Initialization) {
    Framebuffer fb(width, height);
    EXPECT_EQ(fb.get_width(), width);
    EXPECT_EQ(fb.get_height(), height);
    ASSERT_NE(fb.get_data(), nullptr);
}

// 2. Тест очистки (Clear)
TEST_F(FramebufferTest, ClearCheck) {
    Framebuffer fb(width, height);
    fb.clear(red);
    
    const uint8_t* data = fb.get_data();
    EXPECT_EQ(data[0], 255); // R
    EXPECT_EQ(data[1], 0);   // G
    EXPECT_EQ(data[2], 0);   // B
    EXPECT_EQ(data[3], 255); // A
    
    // Проверяем последний пиксель, чтобы убедиться, что цикл прошел до конца
    size_t last_idx = (width * height - 1) * 4;
    EXPECT_EQ(data[last_idx], 255);
}

// 3. Тест логики Z-буфера (Depth Test)
TEST_F(FramebufferTest, DepthTestLogic) {
    Framebuffer fb(1, 1); // Маленький буфер для теста одного пикселя
    
    // 1. Ставим синий пиксель далеко
    fb.set_pixel(0, 0, blue, 0.8f);
    
    // 2. Пытаемся поставить красный пиксель дальше
    // Он не должен отобразиться
    fb.set_pixel(0, 0, red, 0.9f);
    
    const uint8_t* data = fb.get_data();
    EXPECT_EQ(data[2], 255); // Должен остаться синий
    EXPECT_EQ(data[0], 0);   // Не красный
    
    // 3. Ставим красный пиксель БЛИЖЕ (depth = 0.2)
    // Он должен перекрыть синий
    fb.set_pixel(0, 0, red, 0.2f);
    EXPECT_EQ(data[0], 255); // Теперь красный
    EXPECT_EQ(data[2], 0);
}

// 4. Тест выхода за границы (Bounds Checking)
TEST_F(FramebufferTest, OutOfBounds) {
    Framebuffer fb(width, height);

    fb.set_pixel(-1, 0, red, 0.5f);
    fb.set_pixel(width, height, red, 0.5f);
    fb.set_pixel(width + 100, 0, red, 0.5f);
    
    SUCCEED();
}

} // namespace render