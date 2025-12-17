#pragma once

#include <array>
#include <ostream>
#include <stdexcept>

#include "MConcepts.hpp"
#include "Vector4.hpp"

namespace gmath {

    /**
     * @class Matrix4
     * @brief Шаблонный класс для работы с матрицами 4x4
     * @tparam T Тип элементов матрицы     
     */
    template<is_float_double T> class Matrix4 {
    private:        
        std::array<std::array<T, 4>, 4> data;
        
    public:

        Matrix4() {
            for (auto& row : data) {
                row.fill(T(0));
            }
        }
                
        Matrix4(const T values[4][4]) {
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    data[i][j] = values[i][j];
                }
            }
        }                                              
        
        /**
         * @brief Создает единичную матрицу
         * @return Единичная матрица 4x4
         */
        static Matrix4 edinich() {
            Matrix4 mat;
            for (size_t i = 0; i < 4; ++i) {
                mat.data[i][i] = T(1);
            }
            return mat;
        }
        
        /**
         * @brief Создает нулевую матрицу
         * @return Нулевая матрица 4x4
         */
        static Matrix4 zero() {
            return Matrix4();
        }        
                
        /**
         * @brief Доступ к элементу матрицы 
         * @param row Строка 
         * @param col Столбец 
         * @return Элемент         
         */
        const T& operator()(size_t row, size_t col) const {
            if (row >= 4 || col >= 4) {
                throw std::out_of_range("Out of range");                
            }
            return data[row][col];
        }                                
        
        /**
         * @brief Сложение матриц
         * @param other Матрица для сложения
         * @return Результат
         */
        Matrix4 operator+(const Matrix4& other) const {
            Matrix4 result;
            for (size_t i = 0; i < 4; ++i) {
                for (size_t j = 0; j < 4; ++j) {
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
        Matrix4 operator-(const Matrix4& other) const {
            Matrix4 result;
            for (size_t i = 0; i < 4; ++i) {
                for (size_t j = 0; j < 4; ++j) {
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
        Matrix4 operator*(const Matrix4& other) const {
            Matrix4 result;
            for (size_t i = 0; i < 4; ++i) {
                for (size_t j = 0; j < 4; ++j) {
                    T sum = T(0);
                    for (size_t k = 0; k < 4; ++k) {
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
        Vector4<T> operator*(const Vector4<T>& vec) const {
            return Vector4<T>(
                data[0][0] * vec.x + data[0][1] * vec.y + data[0][2] * vec.z + data[0][3] * vec.w,
                data[1][0] * vec.x + data[1][1] * vec.y + data[1][2] * vec.z + data[1][3] * vec.w,
                data[2][0] * vec.x + data[2][1] * vec.y + data[2][2] * vec.z + data[2][3] * vec.w,
                data[3][0] * vec.x + data[3][1] * vec.y + data[3][2] * vec.z + data[3][3] * vec.w
            );
        }
        
        /**
         * @brief Умножение матрицы на скаляр
         * @param scalar Скаляр для умножения
         * @return Результат 
         */
        Matrix4 operator*(T scalar) const {
            Matrix4 result;
            for (size_t i = 0; i < 4; ++i) {
                for (size_t j = 0; j < 4; ++j) {
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
        Matrix4 operator/(T scalar) const {
            if (scalar == T(0)) {
                throw std::runtime_error("Division by zero");
            }
            Matrix4 result;
            for (size_t i = 0; i < 4; ++i) {
                for (size_t j = 0; j < 4; ++j) {
                    result.data[i][j] = data[i][j] / scalar;
                }
            }
            return result;
        }                
        
        Matrix4& operator+=(const Matrix4& other) {
            for (size_t i = 0; i < 4; ++i) {
                for (size_t j = 0; j < 4; ++j) {
                    data[i][j] += other.data[i][j];
                }
            }
            return *this;
        }
        
        Matrix4& operator-=(const Matrix4& other) {
            for (size_t i = 0; i < 4; ++i) {
                for (size_t j = 0; j < 4; ++j) {
                    data[i][j] -= other.data[i][j];
                }
            }
            return *this;
        }
        
        Matrix4& operator*=(const Matrix4& other) {
            *this = *this * other;
            return *this;
        }
        
        Matrix4& operator*=(T scalar) {
            for (size_t i = 0; i < 4; ++i) {
                for (size_t j = 0; j < 4; ++j) {
                    data[i][j] *= scalar;
                }
            }
            return *this;
        }
        
        Matrix4& operator/=(T scalar) {
            if (scalar == T(0)) {
                throw std::runtime_error("Division by zero");
            }
            for (size_t i = 0; i < 4; ++i) {
                for (size_t j = 0; j < 4; ++j) {
                    data[i][j] /= scalar;
                }
            }
            return *this;
        }                
        
        bool operator==(const Matrix4& other) const {
            for (size_t i = 0; i < 4; ++i) {
                for (size_t j = 0; j < 4; ++j) {
                    if (data[i][j] != other.data[i][j]) {
                        return false;
                    }
                }
            }
            return true;
        }
        
        bool operator!=(const Matrix4& other) const {
            return !(*this == other);
        }
        
        /**
         * @brief Сравнение 
         * @param other Матрица для сравнения
         * @param eps Погрешность 
         * @return Результат
         */
        bool equals(const Matrix4& other, T eps = std::numeric_limits<T>::epsilon()) const {
            for (size_t i = 0; i < 4; ++i) {
                for (size_t j = 0; j < 4; ++j) {
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
        [[nodiscard]] Matrix4 transposed() const {
            Matrix4 result;
            for (size_t i = 0; i < 4; ++i) {
                for (size_t j = 0; j < 4; ++j) {
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
        
        friend std::ostream& operator<<(std::ostream& os, const Matrix4& mat) {
            os << "[";
            for (size_t i = 0; i < 4; ++i) {
                if (i != 0) os << " ";
                os << "[";
                for (size_t j = 0; j < 4; ++j) {
                    os << mat.data[i][j];
                    if (j < 3) os << ", ";
                }
                os << "]";
                if (i < 3) os << "\n";
            }
            os << "]";
            return os;
        }
    };
        
    using Matrix4f = Matrix4<float>;
    using Matrix4d = Matrix4<double>;        
}