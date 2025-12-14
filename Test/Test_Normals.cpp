#include "Normal.hpp"
#include "Vector3.hpp"
#include <gtest/gtest.h>

using namespace gmath;

// ===== 1. Constructor tests =====

TEST(NormalTests, ConstructorInitializesZeroVectors) {
    Normal<float> n(3, 2);

    const auto& vn = n.get_vertex_normals();
    const auto& fn = n.get_face_normals();

    ASSERT_EQ(vn.size(), 3);
    ASSERT_EQ(fn.size(), 2);

    for (const auto& v : vn) {
        EXPECT_EQ(v, Vector3f::Null());
    }
    for (const auto& v : fn) {
        EXPECT_EQ(v, Vector3f::Null());
    }
}

// ===== 2. Face normal computation =====

TEST(NormalTests, ComputesFaceNormalsCorrectly) {
    // Один треугольник в плоскости XY
    std::vector<Vector3f> vertices = {
        {0,0,0},
        {1,0,0},
        {0,1,0}
    };

    std::vector<std::vector<int>> polys = {
        {0,1,2}
    };

    Normal<float> n(3, 1);
    n.compute_face_normals(polys, vertices);

    auto fn = n.get_face_normals();
    Vector3f expected = Vector3f(0,0,1); // нормаль вверх

    EXPECT_NEAR(fn[0].x, expected.x, 1e-5);
    EXPECT_NEAR(fn[0].y, expected.y, 1e-5);
    EXPECT_NEAR(fn[0].z, expected.z, 1e-5);
}

TEST(NormalTests, FaceNormalForDegeneratePolygonIsZero) {
    std::vector<Vector3f> vertices = {
        {0,0,0},
        {1,0,0}
    };
    std::vector<std::vector<int>> polys = { {0,1} };

    Normal<float> n(2, 1);
    n.compute_face_normals(polys, vertices);

    EXPECT_EQ(n.get_face_normals()[0], Vector3f::Null());
}

// ===== 3. Vertex normals tests =====

TEST(NormalTests, ComputesVertexNormalsCorrectly) {
    // Простой треугольник
    std::vector<Vector3f> vertices = {
        {0,0,0},
        {1,0,0},
        {0,1,0}
    };
    std::vector<std::vector<int>> polys = {
        {0,1,2}
    };

    Normal<float> n(3, 1);

    n.compute_face_normals(polys, vertices);
    n.compute_vertex_normals(polys, vertices);

    auto vn = n.get_vertex_normals();
    Vector3f expected(0,0,1);

    for (int i = 0; i < 3; i++) {
        EXPECT_NEAR(vn[i].x, expected.x, 1e-5);
        EXPECT_NEAR(vn[i].y, expected.y, 1e-5);
        EXPECT_NEAR(vn[i].z, expected.z, 1e-5);
    }
}

TEST(NormalTests, VertexNormalsAccumulateMultipleFaces) {
    // Квадрат из двух треугольников
    std::vector<Vector3f> vertices = {
        {0,0,0},
        {1,0,0},
        {1,1,0},
        {0,1,0}
    };
    std::vector<std::vector<int>> polys = {
        {0,1,2},
        {0,2,3}
    };

    Normal<float> n(4, 2);

    n.compute_face_normals(polys, vertices);
    n.compute_vertex_normals(polys, vertices);

    auto vn = n.get_vertex_normals();

    // Все нормали должны быть (0,0,1)
    Vector3f expected(0,0,1);

    for (int i = 0; i < 4; i++) {
        EXPECT_NEAR(vn[i].x, expected.x, 1e-5);
        EXPECT_NEAR(vn[i].y, expected.y, 1e-5);
        EXPECT_NEAR(vn[i].z, expected.z, 1e-5);
    }
}