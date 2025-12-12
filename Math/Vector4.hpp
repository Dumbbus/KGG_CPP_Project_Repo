#pragma once

#include <concepts>
#include <cmath>
#include <ostream>
#include <stdexcept>

#include "MConcepts.hpp"

namespace gmath {

    //template<typename T> concept isFloatDouble = std::is_floating_point_v<T>;

    /**
     * @class Vector4
     * @brief Шаблонный класс для работы с 4D векторами
     * @tparam T Тип координат вектора (float или double)
     *      
     */
    template<is_float_double T> class Vector4 {
        public:
            T x, y, z, w;
            
            Vector4() : x(0), y(0), z(0), w(0) {}
            Vector4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}                                 
            
            Vector4(const Vector4& other) = default;
            Vector4& operator=(const Vector4& other) = default;
                        
            Vector4 operator+(const Vector4& other) const {
                return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
            }
            
            Vector4 operator-(const Vector4& other) const {
                return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
            }
            
            Vector4 operator*(T scalar) const {
                return Vector4(x * scalar, y * scalar, z * scalar, w * scalar);
            }
            
            Vector4 operator/(T scalar) const {
                if (scalar == 0) {
                    throw std::runtime_error("Division by zero");
                }
                return Vector4(x / scalar, y / scalar, z / scalar, w / scalar);
            }
                                
            Vector4& operator+=(const Vector4& other) {
                x += other.x;
                y += other.y;
                z += other.z;
                w += other.w;
                return *this;
            }
            
            Vector4& operator-=(const Vector4& other) {
                x -= other.x;
                y -= other.y;
                z -= other.z;
                w -= other.w;
                return *this;
            }
                                    
            Vector4& operator*=(T scalar) {
                x *= scalar;
                y *= scalar;
                z *= scalar;
                w *= scalar;
                return *this;
            }
            
            Vector4& operator/=(T scalar) {
                if (scalar == 0) {
                    throw std::runtime_error("Division by zero");
                }
                x /= scalar;
                y /= scalar;
                z /= scalar;
                w /= scalar;
                return *this;
            }
                                
            Vector4 operator-() const {
                return Vector4(-x, -y, -z, -w);
            }
            
            bool operator==(const Vector4& other) const {
                return x == other.x && y == other.y && z == other.z && w == other.w;
            }
            
            bool operator!=(const Vector4& other) const {
                return !(*this == other);
            }
            
            friend std::ostream& operator<<(std::ostream& os, const Vector4& vec) {
                os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ")";
                return os;
            }
            
            [[nodiscard]] T dot(const Vector4& other) const {
                return x * other.x + y * other.y + z * other.z + w * other.w;
            }            
                        
            [[nodiscard]] T length_squared() const noexcept {
                return x * x + y * y + z * z + w * w;
            }
            
            [[nodiscard]] T length() const noexcept {
                return std::sqrt(length_squared());
            }
            
            [[nodiscard]] Vector4 normalized() const {
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

    using Vector4f = Vector4<float>;
    using Vector4d = Vector4<double>;    
}
