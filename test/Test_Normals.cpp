#include <gtest/gtest.h>

#include <Light/Normal.hpp>
#include <Math/Vector3.hpp>

using namespace gmath;

// ========================================================
// 1. Constructor tests
// ========================================================

TEST(NormalTests, ConstructorInitializesZeroVectors) {
    Normal<float> n(3, 2);

    const auto& vn = n.get_vertex_normals();
    const auto& fn = n.get_face_normals();

    ASSERT_EQ(vn.size(), 3);
    ASSERT_EQ(fn.size(), 2);

    for (const auto& v : vn) {
        EXPECT_EQ(v, Vector3f::Null());
    }

    for (const auto& f : fn) {
        EXPECT_EQ(f, Vector3f::Null());
    }
}

// ========================================================
// 2. Face normal computation
// ========================================================

TEST(NormalTests, ComputesFaceNormalsCorrectly) {
    std::vector<Vector3f> vertices = {
        {0.f, 0.f, 0.f},
        {1.f, 0.f, 0.f},
        {0.f, 1.f, 0.f}
    };

    std::vector<std::vector<int>> polys = {
        {0, 1, 2}
    };

    Normal<float> n(vertices.size(), polys.size());
    n.compute_face_normals(polys, vertices);

    const auto& fn = n.get_face_normals();

    ASSERT_EQ(fn.size(), 1);

    Vector3f expected(0.f, 0.f, 1.f);

    EXPECT_NEAR(fn[0].x, expected.x, 1e-5f);
    EXPECT_NEAR(fn[0].y, expected.y, 1e-5f);
    EXPECT_NEAR(fn[0].z, expected.z, 1e-5f);
}

TEST(NormalTests, FaceNormalForDegeneratePolygonIsZero) {
    std::vector<Vector3f> vertices = {
        {0.f, 0.f, 0.f},
        {1.f, 0.f, 0.f}
    };

    std::vector<std::vector<int>> polys = {
        {0, 1}
    };

    Normal<float> n(vertices.size(), polys.size());
    n.compute_face_normals(polys, vertices);

    EXPECT_EQ(n.get_face_normals()[0], Vector3f::Null());
}

// ========================================================
// 3. Vertex normals computation
// ========================================================

TEST(NormalTests, ComputesVertexNormalsCorrectly) {
    std::vector<Vector3f> vertices = {
        {0.f, 0.f, 0.f},
        {1.f, 0.f, 0.f},
        {0.f, 1.f, 0.f}
    };

    std::vector<std::vector<int>> polys = {
        {0, 1, 2}
    };

    Normal<float> n(vertices.size(), polys.size());

    n.compute_face_normals(polys, vertices);
    n.compute_vertex_normals(polys, vertices);

    const auto& vn = n.get_vertex_normals();
    Vector3f expected(0.f, 0.f, 1.f);

    ASSERT_EQ(vn.size(), 3);

    for (const auto& v : vn) {
        EXPECT_NEAR(v.x, expected.x, 1e-5f);
        EXPECT_NEAR(v.y, expected.y, 1e-5f);
        EXPECT_NEAR(v.z, expected.z, 1e-5f);
    }
}

TEST(NormalTests, VertexNormalsAccumulateMultipleFaces) {
    std::vector<Vector3f> vertices = {
        {0.f, 0.f, 0.f},
        {1.f, 0.f, 0.f},
        {1.f, 1.f, 0.f},
        {0.f, 1.f, 0.f}
    };

    std::vector<std::vector<int>> polys = {
        {0, 1, 2},
        {0, 2, 3}
    };

    Normal<float> n(vertices.size(), polys.size());

    n.compute_face_normals(polys, vertices);
    n.compute_vertex_normals(polys, vertices);

    const auto& vn = n.get_vertex_normals();
    Vector3f expected(0.f, 0.f, 1.f);

    ASSERT_EQ(vn.size(), 4);

    for (const auto& v : vn) {
        EXPECT_NEAR(v.x, expected.x, 1e-5f);
        EXPECT_NEAR(v.y, expected.y, 1e-5f);
        EXPECT_NEAR(v.z, expected.z, 1e-5f);
    }
}
