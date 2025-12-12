#pragma once

#include <concepts>
#include <cmath>
#include <ostream>
#include <stdexcept>

#include "MConcepts.hpp"

namespace gmath {

    //template<typename T> concept isFloatDouble = std::is_floating_point_v<T>;

    /**
     * @class Vector3
     * @brief Шаблонный класс для работы с 3D векторами
     * @tparam T Тип координат вектора (float или double)
     *      
     */
    template<is_float_double T> class Vector3 {
        public:
            T x, y, z;

            Vector3() : x(0), y(0), z(0) {}
            Vector3(T x, T y, T z) : x(x), y(y), z(z) {}
            Vector3(const Vector3& other) = default;          
        
            Vector3& operator=(const Vector3& other) = default;
            
            Vector3 operator+(const Vector3& other) const {
                return Vector3(x + other.x, y + other.y, z + other.z);
            }
            
            Vector3 operator-(const Vector3& other) const {
                return Vector3(x - other.x, y - other.y, z - other.z);
            }
            
            Vector3 operator*(T scalar) const {
                return Vector3(x * scalar, y * scalar, z * scalar);
            }
            
            Vector3 operator/(T scalar) const {
                if (scalar == 0) {
                    throw std::runtime_error("Division by zero");
                }
                return Vector3(x / scalar, y / scalar, z / scalar);
            }
                    
            Vector3& operator+=(const Vector3& other) {
                x += other.x;
                y += other.y;
                z += other.z;
                return *this;
            }
            
            Vector3& operator-=(const Vector3& other) {
                x -= other.x;
                y -= other.y;
                z -= other.z;
                return *this;
            }
            
            Vector3& operator*=(T scalar) {
                x *= scalar;
                y *= scalar;
                z *= scalar;
                return *this;
            }
            
            Vector3& operator/=(T scalar) {
                if (scalar == 0) {
                    throw std::runtime_error("Division by zero");
                }
                x /= scalar;
                y /= scalar;
                z /= scalar;
                return *this;
            }
                    
            Vector3 operator-() const {
                return Vector3(-x, -y, -z);
            }

            bool operator==(const Vector3& other) const {
                return x == other.x && y == other.y && z == other.z;
            }
            
            bool operator!=(const Vector3& other) const {
                return !(*this == other);
            }

            friend std::ostream& operator<<(std::ostream& os, const Vector3& vec) {
                os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
                return os;
            }

            [[nodiscard]] T dot(const Vector3& other) const {
                return x * other.x + y * other.y + z * other.z;
            }
            
            /**
             * @brief Вычисляет векторное произведение векторов
             * @param other Второй вектор
             * @return Векторное произведение - новый векор
             */
            [[nodiscard]] Vector3 cross(const Vector3& other) const {
                return Vector3(
                    y * other.z - z * other.y,
                    z * other.x - x * other.z,
                    x * other.y - y * other.x
                );
            }
            
            [[nodiscard]] T length_squared() const noexcept {
                return x * x + y * y + z * z;
            }
            
            [[nodiscard]] T length() const noexcept {
                return std::sqrt(length_squared());
            }
            
            [[nodiscard]] Vector3 normalized() const {
                T len = length();
                if (len == 0) return *this;
                return *this / len;
            }
            
            void normalize() {
                T len = length();
                if (len == 0) return;           
                *this /= len;
            }
    };

    using Vector3f = Vector3<float>;
    using Vector3d = Vector3<double>;    
}
