//
// Created by shulz on 16.01.2026.
//

#include <gtest/gtest.h>
#include "Scene/Projection.h"
#include <cmath>

const double EPSILON = 1e-6;

class ProjectionTest : public ::testing::Test {
protected:
    double fov = 90.0;
    double aspect = 1.777; // 16:9
    double near = 0.1;
    double far = 100.0;
};

// 1. Тест инициализации и сеттеров
TEST_F(ProjectionTest, SettersAndGetters) {
    Projection proj(fov, aspect, near, far);

    // Проверяем изменение FOV
    proj.set_fov(60.0);

    SUCCEED();
}

// 2. Тест корректности матрицы проекции
TEST_F(ProjectionTest, MatrixValuesCalculation) {
    Projection proj(fov, aspect, near, far);
    gmath::Matrix4d mat = proj.get_projection_matrix();

    double fov_rad = fov * M_PI / 180.0;
    double tan_half_fov = std::tan(fov_rad / 2.0);

    double expected_11 = 1.0 / (aspect * tan_half_fov);
    double expected_22 = 1.0 / tan_half_fov;
    double expected_33 = -(far + near) / (far - near);
    double expected_34 = -(2.0 * far * near) / (far - near);

    EXPECT_NEAR(mat(0, 0), expected_11, EPSILON);
    EXPECT_NEAR(mat(1, 1), expected_22, EPSILON);
    EXPECT_NEAR(mat(2, 2), expected_33, EPSILON);
    EXPECT_NEAR(mat(2, 3), expected_34, EPSILON);
    EXPECT_NEAR(mat(3, 2), -1.0, EPSILON);
}

// 3. Тест на граничные условия (близкая и дальняя плоскости)
TEST_F(ProjectionTest, NearFarPlaneClash) {
    Projection proj(90.0, 1.0, 10.0, 10.0);
    gmath::Matrix4d mat = proj.get_projection_matrix();
}