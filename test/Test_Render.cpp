//
// Created by shulz on 16.01.2026.
//

#include <gtest/gtest.h>
#include "Render/Render.h"

// Используем небольшую дельту для double
const double R_EPS = 1e-5;

class RenderTest : public ::testing::Test {
protected:
    // Подготовка простой меш-структуры (один треугольник)
    Mesh create_single_triangle_mesh() {
        Mesh mesh;
        mesh.m_vertexs = {{0, 0, 0}, {1, 0, 0}, {0, 1, 0}};
        mesh.m_normals = {{0, 0, 1}, {0, 0, 1}, {0, 0, 1}};
        mesh.m_uvs     = {{0, 0},    {1, 0},    {0, 1}};

        // Создаем один полигон (треугольник)
        Polygon poly;
        poly.set_vertexs({0, 1, 2});
        poly.set_normals({0, 1, 2});
        poly.set_uvs({0, 1, 2});
        mesh.m_polygons.push_back(poly);

        return mesh;
    }
};

// 1. Тест базовой проекции (Точка в центре экрана)
TEST_F(RenderTest, ProcessMeshCenterPoint) {
    Mesh mesh = create_single_triangle_mesh();

    // Единичные матрицы (камера смотрит в 0,0,0, проекции нет)
    gmath::Matrix4d model = gmath::Matrix4d::edinich();
    gmath::Matrix4d view = gmath::Matrix4d::edinich();
    gmath::Matrix4d proj = gmath::Matrix4d::edinich();

    double width = 800;
    double height = 600;

    auto result = Render::process_mesh(mesh, model, view, proj, width, height);

    ASSERT_EQ(result.size(), 3);

    // Первая вершина (0,0,0) при единичных матрицах в NDC должна быть (0,0,0)
    // В экранных координатах: x = (0 + 1) * 800 * 0.5 = 400
    // y = (1 - 0) * 600 * 0.5 = 300
    EXPECT_NEAR(result[0].position.x, 400.0, R_EPS);
    EXPECT_NEAR(result[0].position.y, 300.0, R_EPS);
    EXPECT_TRUE(result[0].valid);
}

// 2. Тест отсечения (Clipping) объектов за камерой
TEST_F(RenderTest, ProcessMeshBehindCamera) {
    Mesh mesh = create_single_triangle_mesh();

    // Сдвигаем объект далеко за камеру (Z = +10, если камера смотрит в -Z)
    // Или просто используем матрицу трансляции
    gmath::Matrix4d model = gmath::Matrix4d::translation({0, 0, 10});
    gmath::Matrix4d view = gmath::Matrix4d::edinich();
    gmath::Matrix4d proj = gmath::Matrix4d::edinich(); // w будет равно 1, но проверим логику w < 0.0001

    // Чтобы получить w < 0, нам нужна реальная матрица проекции,
    // где w зависит от -Z. Но мы можем симулировать это через MVP.
    gmath::Matrix4d mvp_bad = gmath::Matrix4d::edinich();
    mvp_bad(3,3) = -1.0; // Искусственно портим w

    auto result = Render::process_mesh(mesh, model, view, mvp_bad, 800, 600);

    for (const auto& v : result) {
        EXPECT_FALSE(v.valid); // Вершины должны быть помечены как невалидные
    }
}

// 3. Тест трансформации нормалей
TEST_F(RenderTest, ProcessFaceNormals) {
    std::vector<gmath::Vector3d> normals = {{0, 0, 1}};

    // Поворачиваем модель на 90 градусов по Y
    // Нормаль (0,0,1) должна стать (1,0,0)
    gmath::Matrix4d model = gmath::Matrix4d::rotation_y(M_PI / 2.0);
    gmath::Matrix4d view = gmath::Matrix4d::edinich();

    auto result = Render::process_face_normals(normals, model, view);

    ASSERT_EQ(result.size(), 1);
    EXPECT_NEAR(result[0].x, 1.0, R_EPS);
    EXPECT_NEAR(result[0].y, 0.0, R_EPS);
    EXPECT_NEAR(result[0].z, 0.0, R_EPS);
}

// 4. Тест коррекции текстурных координат
TEST_F(RenderTest, PerspectiveUVCorrection) {
    Mesh mesh = create_single_triangle_mesh();
    gmath::Matrix4d model = gmath::Matrix4d::edinich();
    gmath::Matrix4d view = gmath::Matrix4d::edinich();

    // Создаем матрицу, которая даст w = 2.0 для всех вершин
    gmath::Matrix4d proj = gmath::Matrix4d::edinich();
    proj(3,3) = 2.0;

    auto result = Render::process_mesh(mesh, model, view, proj, 800, 600);

    // inv_w должно быть 1 / 2.0 = 0.5
    EXPECT_NEAR(result[0].inv_w, 0.5, R_EPS);

    // UV вершины [1] было {1, 0}. Должно стать {1*0.5, 0*0.5} = {0.5, 0}
    EXPECT_NEAR(result[1].uv.x, 0.5, R_EPS);
}