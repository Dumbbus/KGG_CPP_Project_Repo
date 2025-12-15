#pragma once

#include <array>
#include <ostream>
#include <stdexcept>

#include "MConcepts.hpp"
#include "Vector3.hpp"

namespace gmath {

    /**
     * @class Matrix3
     * @brief Шаблонный класс для работы с матрицами 3x3
     * @tparam T Тип элементов матрицы     
     */
    template<is_float_double T> class Matrix3 {
    private:        
        std::array<std::array<T, 3>, 3> data;
        
    public:

        Matrix3() {
            for (auto& row : data) {
                row.fill(T(0));
            }
        }
                
        Matrix3(const T values[3][3]) {
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    data[i][j] = values[i][j];
                }
            }
        }                                              
        
        /**
         * @brief Создает единичную матрицу
         * @return Единичная матрица 3x3
         */
        static Matrix3 edinich() {
            Matrix3 mat;
            for (size_t i = 0; i < 3; ++i) {
                mat.data[i][i] = T(1);
            }
            return mat;
        }
        
        /**
         * @brief Создает нулевую матрицу
         * @return Нулевая матрица 3x3
         */
        static Matrix3 zero() {
            return Matrix3();
        }        
                
        
        /**
         * @brief Доступ к элементу матрицы 
         * @param row Строка 
         * @param col Столбец 
         * @return Элемент         
         */
        const T& operator()(size_t row, size_t col) const {
            if (row >= 3 || col >= 3) {
                throw std::out_of_range("Out of range");             
            }
            return data[row][col];
        }                                
        
        /**
         * @brief Сложение матриц
         * @param other Матрица для сложения
         * @return Результат
         */
        Matrix3 operator+(const Matrix3& other) const {
            Matrix3 result;
            for (size_t i = 0; i < 3; ++i) {
                for (size_t j = 0; j < 3; ++j) {
                    result.data[i][j] = data[i][j] + other.data[i][j];
                }
            }
            return result;
        }
        
        /**
         * @brief Вычитание матриц
         * @param other Матрица для вычитания
         * @return Результат 
         */
        Matrix3 operator-(const Matrix3& other) const {
            Matrix3 result;
            for (size_t i = 0; i < 3; ++i) {
                for (size_t j = 0; j < 3; ++j) {
                    result.data[i][j] = data[i][j] - other.data[i][j];
                }
            }
            return result;
        }
        
        /**
         * @brief Умножение матриц
         * @param other Матрица для умножения
         * @return Результат 
         */
        Matrix3 operator*(const Matrix3& other) const {
            Matrix3 result;
            for (size_t i = 0; i < 3; ++i) {
                for (size_t j = 0; j < 3; ++j) {
                    T sum = T(0);
                    for (size_t k = 0; k < 3; ++k) {
                        sum += data[i][k] * other.data[k][j];
                    }
                    result.data[i][j] = sum;
                }
            }
            return result;
        }
        
        /**
         * @brief Умножение матрицы на вектор
         * @param vec Вектор для умножения
         * @return Результат (Vector)
         */
        Vector3<T> operator*(const Vector3<T>& vec) const {
            return Vector3<T>(
                data[0][0] * vec.x + data[0][1] * vec.y + data[0][2] * vec.z,
                data[1][0] * vec.x + data[1][1] * vec.y + data[1][2] * vec.z,
                data[2][0] * vec.x + data[2][1] * vec.y + data[2][2] * vec.z
            );
        }
        
        /**
         * @brief Умножение матрицы на скаляр
         * @param scalar Скаляр для умножения
         * @return Результат 
         */
        Matrix3 operator*(T scalar) const {
            Matrix3 result;
            for (size_t i = 0; i < 3; ++i) {
                for (size_t j = 0; j < 3; ++j) {
                    result.data[i][j] = data[i][j] * scalar;
                }
            }
            return result;
        }
        
        /**
         * @brief Деление матрицы на скаляр
         * @param scalar Скаляр для деления
         * @return Результат          
         */
        Matrix3 operator/(T scalar) const {
            if (scalar == T(0)) {
                throw std::runtime_error("Division by zero");
            }
            Matrix3 result;
            for (size_t i = 0; i < 3; ++i) {
                for (size_t j = 0; j < 3; ++j) {
                    result.data[i][j] = data[i][j] / scalar;
                }
            }
            return result;
        }                
        
        Matrix3& operator+=(const Matrix3& other) {
            for (size_t i = 0; i < 3; ++i) {
                for (size_t j = 0; j < 3; ++j) {
                    data[i][j] += other.data[i][j];
                }
            }
            return *this;
        }
        
        Matrix3& operator-=(const Matrix3& other) {
            for (size_t i = 0; i < 3; ++i) {
                for (size_t j = 0; j < 3; ++j) {
                    data[i][j] -= other.data[i][j];
                }
            }
            return *this;
        }
        
        Matrix3& operator*=(const Matrix3& other) {
            *this = *this * other;
            return *this;
        }
        
        Matrix3& operator*=(T scalar) {
            for (size_t i = 0; i < 3; ++i) {
                for (size_t j = 0; j < 3; ++j) {
                    data[i][j] *= scalar;
                }
            }
            return *this;
        }
        
        Matrix3& operator/=(T scalar) {
            if (scalar == T(0)) {
                throw std::runtime_error("Division by zero");
            }
            for (size_t i = 0; i < 3; ++i) {
                for (size_t j = 0; j < 3; ++j) {
                    data[i][j] /= scalar;
                }
            }
            return *this;
        }                
        
        bool operator==(const Matrix3& other) const {
            for (size_t i = 0; i < 3; ++i) {
                for (size_t j = 0; j < 3; ++j) {
                    if (data[i][j] != other.data[i][j]) {
                        return false;
                    }
                }
            }
            return true;
        }
        
        bool operator!=(const Matrix3& other) const {
            return !(*this == other);
        }
        
        /**
         * @brief Сравнение 
         * @param other Матрица для сравнения
         * @param eps Погрешность 
         * @return Результат
         */
        bool equals(const Matrix3& other, T eps = std::numeric_limits<T>::epsilon()) const {
            for (size_t i = 0; i < 3; ++i) {
                for (size_t j = 0; j < 3; ++j) {
                    if (std::abs(data[i][j] - other.data[i][j]) > eps) {
                        return false;
                    }
                }
            }
            return true;
        }                
        
        /**
         * @brief Возвращает транспонированную матрицу
         * @return Транспонированная матрица
         */
        [[nodiscard]] Matrix3 transposed() const {
            Matrix3 result;
            for (size_t i = 0; i < 3; ++i) {
                for (size_t j = 0; j < 3; ++j) {
                    result.data[j][i] = data[i][j];
                }
            }
            return result;
        }
        
        /**
         * @brief Транспонирует матрицу
         */
        void transpose() {
            *this = transposed();
        }                                                                                                                          
        
        friend std::ostream& operator<<(std::ostream& os, const Matrix3& mat) {
            os << "[";
            for (size_t i = 0; i < 3; ++i) {
                if (i != 0) os << " ";
                os << "[";
                for (size_t j = 0; j < 3; ++j) {
                    os << mat.data[i][j];
                    if (j < 2) os << ", ";
                }
                os << "]";
                if (i < 2) os << "\n";
            }
            os << "]";
            return os;
        }
    };
        
    using Matrix3f = Matrix3<float>;
    using Matrix3d = Matrix3<double>;        
}