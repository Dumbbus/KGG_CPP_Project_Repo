//
// Created by shulz on 16.01.2026.
//

#include <gtest/gtest.h>
#include <Scene/Camera.h>
#include <Math/Matrix4.hpp>
#include <cmath>

// Вспомогательная функция для сравнения чисел с плавающей точкой
#define EXPECT_NEAR_VEC3(v1, v2, eps) \
    EXPECT_NEAR(v1.x, v2.x, eps); \
    EXPECT_NEAR(v1.y, v2.y, eps); \
    EXPECT_NEAR(v1.z, v2.z, eps);

class CameraTest : public ::testing::Test {
protected:
    gmath::Vector3d eye{0.0, 0.0, 5.0};
    gmath::Vector3d target{0.0, 0.0, 0.0};
    gmath::Vector3d up{0.0, 1.0, 0.0};
};

// Тест инициализации
TEST_F(CameraTest, Initialization) {
    Camera cam(eye, target, up);

    EXPECT_NEAR_VEC3(cam.get_eye(), eye, 1e-5);
    EXPECT_NEAR_VEC3(cam.get_target(), target, 1e-5);
    EXPECT_NEAR(cam.get_distance(), 5.0, 1e-5);
}

// Тест матрицы LookAt
TEST_F(CameraTest, LookAtMatrix) {
    Camera cam(eye, target, up);
    gmath::Matrix4d view = cam.look_at();

    // В позиции (0,0,5) смотря в (0,0,0), объект в центре должен
    // иметь координаты (0,0,-5) в пространстве камеры
    gmath::Vector4d point_in_world(0.0, 0.0, 0.0, 1.0);
    gmath::Vector4d point_in_view = view * point_in_world;

    EXPECT_NEAR(point_in_view.x, 0.0, 1e-5);
    EXPECT_NEAR(point_in_view.y, 0.0, 1e-5);
    EXPECT_NEAR(point_in_view.z, -5.0, 1e-5);
}

// Тест панорамирования (Pan)
TEST_F(CameraTest, CameraPanning) {
    Camera cam(eye, target, up);

    cam.pan(100.0f, 0.0f);

    // eye и target должны измениться одинаково
    EXPECT_NEAR(cam.get_distance(), 5.0, 1e-5);
    EXPECT_LT(cam.get_eye().x, eye.x); // При dx > 0 камера уходит влево/сдвигает мир вправо
}

// Тест вращения (Rotation)
TEST_F(CameraTest, CameraRotation) {
    Camera cam(eye, target, up);
    float initial_dist = cam.get_distance();

    // Поворот по горизонтали
    cam.rotate_camera(314.15f, 0.0f); // dx примерно PI/0.005

    // Дистанция до цели не должна меняться при вращении
    EXPECT_NEAR(cam.get_distance(), initial_dist, 1e-5);

    cam.rotate_camera(0.0f, 1000.0f); // Сильно вверх
    EXPECT_LE(cam.get_pitch(), 1.55f);
}