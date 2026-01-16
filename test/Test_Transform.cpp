//
// Created by shulz on 16.01.2026.
//

#include <gtest/gtest.h>
#include "Scene/Transform.h"
#include <cmath>

const double EPS = 1e-6;

class TransformTest : public ::testing::Test {
protected:
    Transform t;
};

// 1. Тест начального состояния
TEST_F(TransformTest, DefaultInitialization) {
    gmath::Matrix4d m = t.get_model_matrix();
    // По умолчанию должна быть единичная матрица
    EXPECT_NEAR(m(0,0), 1.0, EPS);
    EXPECT_NEAR(m(1,1), 1.0, EPS);
    EXPECT_NEAR(m(2,2), 1.0, EPS);
    EXPECT_NEAR(m(3,3), 1.0, EPS);
}

// 2. Тест переноса
TEST_F(TransformTest, TranslationTest) {
    t.set_position({10.0, -5.0, 2.0});
    gmath::Matrix4d m = t.get_model_matrix();

    EXPECT_NEAR(m(0,3), 10.0, EPS);
    EXPECT_NEAR(m(1,3), -5.0, EPS);
    EXPECT_NEAR(m(2,3), 2.0, EPS);
}

// 3. Тест "Dirty Flag" и кеширования
TEST_F(TransformTest, CacheDirtyFlagLogic) {
    t.set_position({1, 1, 1});
    gmath::Matrix4d m1 = t.get_model_matrix(); // Вызывает update_matrix

    // Повторный вызов не должен менять матрицу
    gmath::Matrix4d m2 = t.get_model_matrix();
    EXPECT_EQ(m1, m2);

    t.translate({1, 0, 0}); // Должно установить m_dirty = true
    gmath::Matrix4d m3 = t.get_model_matrix();
    EXPECT_NE(m1, m3);
}

// 4. Тест комбинированных трансформаций (Порядок SRT)
TEST_F(TransformTest, CombinedTransformOrder) {
    t.set_scale({2.0, 2.0, 2.0});
    t.set_position({5.0, 0.0, 0.0});

    gmath::Matrix4d m = t.get_model_matrix();

    EXPECT_NEAR(m(0,0), 2.0, EPS); // Scale X
    EXPECT_NEAR(m(0,3), 5.0, EPS); // Translate X
}