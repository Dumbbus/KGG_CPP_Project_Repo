#pragma once

#include <concepts>
#include <cmath>
#include <ostream>
#include <stdexcept>

namespace gmath {

    //template<typename T> concept isFloatDouble = std::is_floating_point_v<T>;

    template<isFloatDouble T> class Vector3 {
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
            
            [[nodiscard]] Vector3 cross(const Vector3& other) const {
                return Vector3(
                    y * other.z - z * other.y,
                    z * other.x - x * other.z,
                    x * other.y - y * other.x
                );
            }
            
            [[nodiscard]] T lengthSquared() const {
                return x * x + y * y + z * z;
            }
            
            [[nodiscard]] T length() const {
                return std::sqrt(lengthSquared());
            }
            
            [[nodiscard]] Vector3 normalized() const {
                T len = length();
                if (len == 0) return *this;
                return *this / len;
            }
            
            void normalize() {
                T len = length();
                if (len != 0) {
                    *this /= len;
                }
            }
    };

    using Vector3f = Vector3<float>;
    using Vector3d = Vector3<double>;    
}