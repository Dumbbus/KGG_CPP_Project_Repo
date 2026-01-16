//by deepseek


#include "../../include/Math/Math.hpp"
#include <iostream>
#include <cmath>
#include <limits>

namespace gmath_test {

    // Вспомогательная функция для сравнения с заданной точностью
    template<typename T>
    bool approx_equal(T a, T b, T epsilon = std::numeric_limits<T>::epsilon() * 100) {
        return std::abs(a - b) <= epsilon;
    }

    // Тест для Vector2
    int test_vector2() {
        std::cout << "Testing Vector2...\n";
        
        try {
            // Создание и базовые операции
            gmath::Vector2f v1(1.0f, 2.0f);
            gmath::Vector2f v2(3.0f, 4.0f);
            
            // Тест сложения
            auto v3 = v1 + v2;
            if (!v3.equals(gmath::Vector2f(4.0f, 6.0f))) return 0;
            
            // Тест вычитания
            auto v4 = v2 - v1;
            if (!v4.equals(gmath::Vector2f(2.0f, 2.0f))) return 0;
            
            // Тест скалярного умножения
            auto v5 = v1 * 2.0f;
            if (!v5.equals(gmath::Vector2f(2.0f, 4.0f))) return 0;
            
            // Тест скалярного деления
            auto v6 = v2 / 2.0f;
            if (!v6.equals(gmath::Vector2f(1.5f, 2.0f))) return 0;
            
            // Тест скалярного произведения
            float dot = v1.dot(v2);
            if (!approx_equal(dot, 1.0f*3.0f + 2.0f*4.0f)) return 0;
            
            // Тест длины
            float len_sq = v1.length_squared();
            if (!approx_equal(len_sq, 1.0f*1.0f + 2.0f*2.0f)) return 0;
            
            float len = v1.length();
            if (!approx_equal(len, std::sqrt(1.0f*1.0f + 2.0f*2.0f))) return 0;
            
            // Тест нормализации
            gmath::Vector2f v7(3.0f, 4.0f);
            auto v7_norm = v7.normalized();
            float expected_len = 5.0f; // sqrt(3^2 + 4^2)
            if (!v7_norm.equals(gmath::Vector2f(3.0f/expected_len, 4.0f/expected_len))) return 0;
            
            // Тест унарного минуса
            auto v8 = -v1;
            if (!v8.equals(gmath::Vector2f(-1.0f, -2.0f))) return 0;
            
            std::cout << "  Vector2 tests passed!\n";
            return 1;
        }
        catch (const std::exception& e) {
            std::cerr << "  Vector2 test failed: " << e.what() << "\n";
            return 0;
        }
    }

    // Тест для Vector3
    int test_vector3() {
        std::cout << "Testing Vector3...\n";
        
        try {
            // Создание и базовые операции
            gmath::Vector3f v1(1.0f, 2.0f, 3.0f);
            gmath::Vector3f v2(4.0f, 5.0f, 6.0f);
            
            // Тест сложения
            auto v3 = v1 + v2;
            if (!v3.equals(gmath::Vector3f(5.0f, 7.0f, 9.0f))) return 0;
            
            // Тест вычитания
            auto v4 = v2 - v1;
            if (!v4.equals(gmath::Vector3f(3.0f, 3.0f, 3.0f))) return 0;
            
            // Тест скалярного произведения
            float dot = v1.dot(v2);
            if (!approx_equal(dot, 1.0f*4.0f + 2.0f*5.0f + 3.0f*6.0f)) return 0;
            
            // Тест векторного произведения
            // v1 × v2 = (y1*z2 - z1*y2, z1*x2 - x1*z2, x1*y2 - y1*x2)
            // = (2*6 - 3*5, 3*4 - 1*6, 1*5 - 2*4)
            // = (12-15, 12-6, 5-8) = (-3, 6, -3)
            auto cross = v1.cross(v2);
            if (!cross.equals(gmath::Vector3f(-3.0f, 6.0f, -3.0f))) return 0;
            
            // Проверка ортогональности результата векторного произведения
            if (!approx_equal((float)cross.dot(v1), 0.0f)) return 0;
            if (!approx_equal((float)cross.dot(v2), 0.0f)) return 0;
            
            // Тест длины
            float len_sq = v1.length_squared();
            if (!approx_equal(len_sq, 1.0f*1.0f + 2.0f*2.0f + 3.0f*3.0f)) return 0;
            
            // Тест нормализации
            gmath::Vector3f v5(2.0f, 0.0f, 0.0f);
            auto v5_norm = v5.normalized();
            if (!v5_norm.equals(gmath::Vector3f(1.0f, 0.0f, 0.0f))) return 0;
            
            std::cout << "  Vector3 tests passed!\n";
            return 1;
        }
        catch (const std::exception& e) {
            std::cerr << "  Vector3 test failed: " << e.what() << "\n";
            return 0;
        }
    }

    // Тест для Vector4
    int test_vector4() {
        std::cout << "Testing Vector4...\n";
        
        try {
            // Создание и базовые операции
            gmath::Vector4f v1(1.0f, 2.0f, 3.0f, 4.0f);
            gmath::Vector4f v2(5.0f, 6.0f, 7.0f, 8.0f);
            
            // Тест сложения
            auto v3 = v1 + v2;
            if (!v3.equals(gmath::Vector4f(6.0f, 8.0f, 10.0f, 12.0f))) return 0;
            
            // Тест скалярного произведения
            float dot = v1.dot(v2);
            float expected_dot = 1.0f*5.0f + 2.0f*6.0f + 3.0f*7.0f + 4.0f*8.0f;
            if (!approx_equal(dot, expected_dot)) return 0;
            
            // Тест длины
            float len_sq = v1.length_squared();
            float expected_len_sq = 1.0f*1.0f + 2.0f*2.0f + 3.0f*3.0f + 4.0f*4.0f;
            if (!approx_equal(len_sq, expected_len_sq)) return 0;
            
            // Тест нормализации
            gmath::Vector4f v4(0.0f, 0.0f, 0.0f, 5.0f);
            auto v4_norm = v4.normalized();
            if (!v4_norm.equals(gmath::Vector4f(0.0f, 0.0f, 0.0f, 1.0f))) return 0;
            
            std::cout << "  Vector4 tests passed!\n";
            return 1;
        }
        catch (const std::exception& e) {
            std::cerr << "  Vector4 test failed: " << e.what() << "\n";
            return 0;
        }
    }

    // Тест для умножения матрицы 3x3
    int test_matrix3_multiplication() {
        std::cout << "Testing Matrix3 multiplication...\n";
        
        try {
            // Создаем две тестовые матрицы
            // Матрица A:
            // [1, 2, 3]
            // [4, 5, 6]
            // [7, 8, 9]
            float A_values[3][3] = {
                {1.0f, 2.0f, 3.0f},
                {4.0f, 5.0f, 6.0f},
                {7.0f, 8.0f, 9.0f}
            };
            
            // Матрица B:
            // [9, 8, 7]
            // [6, 5, 4]
            // [3, 2, 1]
            float B_values[3][3] = {
                {9.0f, 8.0f, 7.0f},
                {6.0f, 5.0f, 4.0f},
                {3.0f, 2.0f, 1.0f}
            };
            
            gmath::Matrix3f A(A_values);
            gmath::Matrix3f B(B_values);
            
            // Умножаем вручную:
            // C = A × B
            // C[0][0] = 1*9 + 2*6 + 3*3 = 9 + 12 + 9 = 30
            // C[0][1] = 1*8 + 2*5 + 3*2 = 8 + 10 + 6 = 24
            // C[0][2] = 1*7 + 2*4 + 3*1 = 7 + 8 + 3 = 18
            // C[1][0] = 4*9 + 5*6 + 6*3 = 36 + 30 + 18 = 84
            // C[1][1] = 4*8 + 5*5 + 6*2 = 32 + 25 + 12 = 69
            // C[1][2] = 4*7 + 5*4 + 6*1 = 28 + 20 + 6 = 54
            // C[2][0] = 7*9 + 8*6 + 9*3 = 63 + 48 + 27 = 138
            // C[2][1] = 7*8 + 8*5 + 9*2 = 56 + 40 + 18 = 114
            // C[2][2] = 7*7 + 8*4 + 9*1 = 49 + 32 + 9 = 90
            
            float expected_C[3][3] = {
                {30.0f, 24.0f, 18.0f},
                {84.0f, 69.0f, 54.0f},
                {138.0f, 114.0f, 90.0f}
            };
            
            gmath::Matrix3f C = A * B;
            
            // Проверяем каждый элемент
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (!approx_equal((float)C(i, j), (float)expected_C[i][j])) {
                        std::cerr << "  Matrix3 multiplication failed at [" << i << "][" << j << "]: "
                                  << "expected " << expected_C[i][j] << ", got " << C(i, j) << "\n";
                        return 0;
                    }
                }
            }
            
            // Тест умножения матрицы на вектор
            gmath::Vector3f v(1.0f, 2.0f, 3.0f);
            auto result_vec = A * v;
            
            // Проверяем вручную:
            // [1, 2, 3] * [1] = 1*1 + 2*2 + 3*3 = 1 + 4 + 9 = 14
            // [4, 5, 6] * [2] = 4*1 + 5*2 + 6*3 = 4 + 10 + 18 = 32
            // [7, 8, 9] * [3] = 7*1 + 8*2 + 9*3 = 7 + 16 + 27 = 50
            gmath::Vector3f expected_vec(14.0f, 32.0f, 50.0f);
            
            if (!result_vec.equals(expected_vec)) {
                std::cerr << "  Matrix3 * Vector3 failed\n";
                return 0;
            }
            
            // Тест умножения на скаляр
            auto A_times_2 = A * 2.0f;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (!approx_equal(A_times_2(i, j), A_values[i][j] * 2.0f)) {
                        return 0;
                    }
                }
            }
            
            // Тест единичной матрицы
            auto I = gmath::Matrix3f::edinich();
            auto A_times_I = A * I;
            if (!A.equals(A_times_I)) {
                std::cerr << "  Matrix3 identity multiplication failed\n";
                return 0;
            }
            
            // Тест транспонирования
            auto A_transposed = A.transposed();
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (!approx_equal(A_transposed(i, j), A(j, i))) {
                        return 0;
                    }
                }
            }
            
            std::cout << "  Matrix3 multiplication tests passed!\n";
            return 1;
        }
        catch (const std::exception& e) {
            std::cerr << "  Matrix3 test failed: " << e.what() << "\n";
            return 0;
        }
    }

    // Тест для умножения матрицы 4x4
    int test_matrix4_multiplication() {
        std::cout << "Testing Matrix4 multiplication...\n";
        
        try {
            // Создаем две тестовые матрицы 4x4
            float A_values[4][4] = {
                {1.0f, 2.0f, 3.0f, 4.0f},
                {5.0f, 6.0f, 7.0f, 8.0f},
                {9.0f, 10.0f, 11.0f, 12.0f},
                {13.0f, 14.0f, 15.0f, 16.0f}
            };
            
            float B_values[4][4] = {
                {16.0f, 15.0f, 14.0f, 13.0f},
                {12.0f, 11.0f, 10.0f, 9.0f},
                {8.0f, 7.0f, 6.0f, 5.0f},
                {4.0f, 3.0f, 2.0f, 1.0f}
            };
            
            gmath::Matrix4f A(A_values);
            gmath::Matrix4f B(B_values);
            
            // Умножаем и проверяем несколько элементов вручную
            auto C = A * B;
            
            // Проверяем C[0][0]:
            // 1*16 + 2*12 + 3*8 + 4*4 = 16 + 24 + 24 + 16 = 80
            if (!approx_equal(C(0, 0), 80.0f)) return 0;
            
            // Проверяем C[1][2]:
            // 5*14 + 6*10 + 7*6 + 8*2 = 70 + 60 + 42 + 16 = 188
            if (!approx_equal(C(1, 2), 188.0f)) return 0;
            
            // Проверяем C[3][3]:
            // 13*13 + 14*9 + 15*5 + 16*1 = 169 + 126 + 75 + 16 = 386
            if (!approx_equal(C(3, 3), 386.0f)) return 0;
            
            // Тест умножения матрицы на вектор 4D
            gmath::Vector4f v(1.0f, 2.0f, 3.0f, 4.0f);
            auto result_vec = A * v;
            
            // Проверяем вручную:
            // x = 1*1 + 2*2 + 3*3 + 4*4 = 1 + 4 + 9 + 16 = 30
            // y = 5*1 + 6*2 + 7*3 + 8*4 = 5 + 12 + 21 + 32 = 70
            // z = 9*1 + 10*2 + 11*3 + 12*4 = 9 + 20 + 33 + 48 = 110
            // w = 13*1 + 14*2 + 15*3 + 16*4 = 13 + 28 + 45 + 64 = 150
            gmath::Vector4f expected_vec(30.0f, 70.0f, 110.0f, 150.0f);
            
            if (!result_vec.equals(expected_vec)) {
                std::cerr << "  Matrix4 * Vector4 failed\n";
                return 0;
            }
            
            // Тест преобразований
            // Тест трансляции
            gmath::Vector3f translation(2.0f, 3.0f, 4.0f);
            auto T = gmath::Matrix4f::translation(translation);
            
            // Проверяем, что трансляция работает правильно
            gmath::Vector4f point(1.0f, 1.0f, 1.0f, 1.0f);
            auto translated = T * point;
            if (!translated.equals(gmath::Vector4f(3.0f, 4.0f, 5.0f, 1.0f))) {
                std::cerr << "  Translation failed\n";
                return 0;
            }
            
            // Тест масштабирования
            gmath::Vector3f scale_vec(2.0f, 3.0f, 4.0f);
            auto S = gmath::Matrix4f::scale(scale_vec);
            auto scaled = S * point;
            if (!scaled.equals(gmath::Vector4f(2.0f, 3.0f, 4.0f, 1.0f))) {
                std::cerr << "  Scale failed\n";
                return 0;
            }
            
            // Тест поворота вокруг оси Z на 90 градусов
            float angle_90 = 3.14159265358979323846f / 2.0f; // π/2
            auto Rz = gmath::Matrix4f::rotation_z(angle_90);
            gmath::Vector4f vec_x(1.0f, 0.0f, 0.0f, 1.0f);
            auto rotated = Rz * vec_x;
            
            // При повороте (1,0,0) на 90° вокруг Z получаем (0,1,0)
            if (!rotated.equals(gmath::Vector4f(0.0f, 1.0f, 0.0f, 1.0f), 0.0001f)) {
                std::cerr << "  Rotation Z failed: got " << rotated << "\n";
                return 0;
            }
            
            // Тест перспективной проекции (базовая проверка структуры)
            auto P = gmath::Matrix4f::perspective(90.0f, 1.0f, 0.1f, 100.0f);
            // Проверяем, что матрица перспективы имеет правильную структуру
            if (!approx_equal(P(3, 2), -1.0f)) {
                std::cerr << "  Perspective projection structure incorrect\n";
                return 0;
            }
            
            std::cout << "  Matrix4 multiplication tests passed!\n";
            return 1;
        }
        catch (const std::exception& e) {
            std::cerr << "  Matrix4 test failed: " << e.what() << "\n";
            return 0;
        }
    }

    // Тест комбинированных преобразований
    int test_combined_transformations() {
        std::cout << "Testing combined transformations...\n";
        
        try {
            // Создаем точку в локальном пространстве
            gmath::Vector4f local_point(1.0f, 0.0f, 0.0f, 1.0f);
            
            // Создаем последовательность преобразований:
            // 1. Масштабирование в 2 раза
            // 2. Поворот на 90° вокруг Z
            // 3. Перенос на (5, 0, 0)
            
            gmath::Matrix4f S = gmath::Matrix4f::scale(gmath::Vector3f(2.0f, 2.0f, 2.0f));
            gmath::Matrix4f R = gmath::Matrix4f::rotation_z(3.14159265358979323846f / 2.0f);
            gmath::Matrix4f T = gmath::Matrix4f::translation(gmath::Vector3f(5.0f, 0.0f, 0.0f));
            
            // Комбинированное преобразование: T * R * S * point
            // Порядок важен: сначала масштаб, потом поворот, потом перенос
            gmath::Matrix4f M = T * R * S;
            
            // Применяем преобразование
            auto transformed = M * local_point;
            
            // Проверяем вручную:
            // 1. Масштаб: (1,0,0) * 2 = (2,0,0)
            // 2. Поворот на 90°: (2,0,0) -> (0,2,0)
            // 3. Перенос: (0,2,0) + (5,0,0) = (5,2,0)
            gmath::Vector4f expected(5.0f, 2.0f, 0.0f, 1.0f);
            
            if (!transformed.equals(expected, 0.0001f)) {
                std::cerr << "  Combined transformations failed: got " << transformed 
                          << ", expected " << expected << "\n";
                return 0;
            }
            
            // Проверяем ассоциативность умножения матриц
            gmath::Matrix4f M2 = (T * R) * S;
            gmath::Matrix4f M3 = T * (R * S);
            
            if (!M2.equals(M3)) {
                std::cerr << "  Matrix multiplication is not associative!\n";
                return 0;
            }
            
            std::cout << "  Combined transformations tests passed!\n";
            return 1;
        }
        catch (const std::exception& e) {
            std::cerr << "  Combined transformations test failed: " << e.what() << "\n";
            return 0;
        }
    }

    // Тест для операций присваивания
    int test_assignment_operations() {
        std::cout << "Testing assignment operations...\n";
        
        try {
            // Тест для Vector3
            gmath::Vector3f v1(1.0f, 2.0f, 3.0f);
            gmath::Vector3f v2(4.0f, 5.0f, 6.0f);
            
            v1 += v2;
            if (!v1.equals(gmath::Vector3f(5.0f, 7.0f, 9.0f))) return 0;
            
            v1 -= gmath::Vector3f(1.0f, 1.0f, 1.0f);
            if (!v1.equals(gmath::Vector3f(4.0f, 6.0f, 8.0f))) return 0;
            
            v1 *= 2.0f;
            if (!v1.equals(gmath::Vector3f(8.0f, 12.0f, 16.0f))) return 0;
            
            v1 /= 4.0f;
            if (!v1.equals(gmath::Vector3f(2.0f, 3.0f, 4.0f))) return 0;
            
            // Тест для Matrix3
            float values1[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
            float values2[3][3] = {{9, 8, 7}, {6, 5, 4}, {3, 2, 1}};
            
            gmath::Matrix3f m1(values1);
            gmath::Matrix3f m2(values2);
            
            m1 += m2;
            if (!approx_equal(m1(0, 0), 10.0f)) return 0;
            
            m1 -= m2;
            if (!m1.equals(gmath::Matrix3f(values1))) return 0;
            
            m1 *= 3.0f;
            if (!approx_equal(m1(1, 1), 15.0f)) return 0;
            
            m1 /= 3.0f;
            if (!m1.equals(gmath::Matrix3f(values1))) return 0;
            
            // Тест составного умножения матриц
            m1 *= gmath::Matrix3f::edinich();
            if (!m1.equals(gmath::Matrix3f(values1))) return 0;
            
            std::cout << "  Assignment operations tests passed!\n";
            return 1;
        }
        catch (const std::exception& e) {
            std::cerr << "  Assignment operations test failed: " << e.what() << "\n";
            return 0;
        }
    }

    // Тест для проверки граничных случаев и исключений
    int test_edge_cases() {
        std::cout << "Testing edge cases...\n";
        
        try {
            // Тест деления на ноль для векторов
            gmath::Vector3f v(1.0f, 2.0f, 3.0f);
            try {
                auto result = v / 0.0f;
                std::cerr << "  Division by zero should have thrown!\n";
                return 0;
            } catch (const std::runtime_error&) {
                // Ожидаемое исключение
            }
            
            // Тест деления на ноль для матриц
            gmath::Matrix3f m = gmath::Matrix3f::edinich();
            try {
                auto result = m / 0.0f;
                std::cerr << "  Matrix division by zero should have thrown!\n";
                return 0;
            } catch (const std::runtime_error&) {
                // Ожидаемое исключение
            }
            
            // Тест нормализации нулевого вектора
            gmath::Vector3f zero_vec(0.0f, 0.0f, 0.0f);
            auto normalized = zero_vec.normalized();
            if (!normalized.equals(zero_vec)) {
                std::cerr << "  Normalization of zero vector failed\n";
                return 0;
            }
            
            // Тест доступа за границы матрицы
            gmath::Matrix4f mat4;
            try {
                auto val = mat4(4, 0);
                std::cerr << "  Out of bounds access should have thrown!\n";
                return 0;
            } catch (const std::out_of_range&) {
                // Ожидаемое исключение
            }
            
            std::cout << "  Edge cases tests passed!\n";
            return 1;
        }
        catch (const std::exception& e) {
            std::cerr << "  Edge cases test failed: " << e.what() << "\n";
            return 0;
        }
    }

    // Главная тестовая функция
    int math_test() {
        std::cout << "========================================\n";
        std::cout << "Starting Math Module Tests\n";
        std::cout << "========================================\n\n";
        
        int total_score = 0;
        int total_tests = 0;
        
        // Запускаем все тесты
        auto run_test = [&](const std::string& name, auto test_func) {
            total_tests++;
            std::cout << "\nTest " << total_tests << ": " << name << "\n";
            std::cout << std::string(40, '-') << "\n";
            
            int result = test_func();
            total_score += result;
            
            if (result) {
                std::cout << "✓ PASSED\n";
            } else {
                std::cout << "✗ FAILED\n";
            }
            
            return result;
        };
        
        run_test("Vector2 Operations", test_vector2);
        run_test("Vector3 Operations", test_vector3);
        run_test("Vector4 Operations", test_vector4);
        run_test("Matrix3 Multiplication", test_matrix3_multiplication);
        run_test("Matrix4 Multiplication", test_matrix4_multiplication);
        run_test("Combined Transformations", test_combined_transformations);
        run_test("Assignment Operations", test_assignment_operations);
        run_test("Edge Cases", test_edge_cases);
        
        // Выводим итоги
        std::cout << "\n========================================\n";
        std::cout << "Test Results: " << total_score << "/" << total_tests << " passed\n";
        
        if (total_score == total_tests) {
            std::cout << "✓ ALL TESTS PASSED!\n";
        } else {
            std::cout << "✗ SOME TESTS FAILED\n";
        }
        std::cout << "========================================\n";
        
        return (total_score == total_tests) ? 1 : 0;
    }
}

// Главная функция для запуска тестов
int main() {
    return gmath_test::math_test() ? 0 : 1;
}