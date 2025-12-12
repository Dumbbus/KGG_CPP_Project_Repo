
#pragma once

#include <concepts>
#include <cmath>
#include <ostream>
#include <stdexcept>

namespace gmath {

    template<typename T> concept isFloatDouble = std::is_floating_point_v<T>;

    template<isFloatDouble T> class Vector2 {
        public:
            T x, y;
            
            Vector2() : x(0), y(0) {}
            Vector2(T x, T y) : x(x), y(y) {}            
            
            Vector2(const Vector2& other) = default;
            Vector2& operator=(const Vector2& other) = default;
                        
            Vector2 operator+(const Vector2& other) const {
                return Vector2(x + other.x, y + other.y);
            }
            
            Vector2 operator-(const Vector2& other) const {
                return Vector2(x - other.x, y - other.y);
            }
            
            Vector2 operator*(T scalar) const {
                return Vector2(x * scalar, y * scalar);
            }
            
            Vector2 operator/(T scalar) const {
                if (scalar == 0) {
                    throw std::runtime_error("Division by zero");
                }
                return Vector2(x / scalar, y / scalar);
            }
                                
            Vector2& operator+=(const Vector2& other) {
                x += other.x;
                y += other.y;
                return *this;
            }
            
            Vector2& operator-=(const Vector2& other) {
                x -= other.x;
                y -= other.y;
                return *this;
            }
            
            Vector2& operator*=(T scalar) {
                x *= scalar;
                y *= scalar;
                return *this;
            }
            
            Vector2& operator/=(T scalar) {
                if (scalar == 0) {
                    throw std::runtime_error("Division by zero");
                }
                x /= scalar;
                y /= scalar;
                return *this;
            }
                                
            Vector2 operator-() const {
                return Vector2(-x, -y);
            }
            
            bool operator==(const Vector2& other) const {
                return x == other.x && y == other.y;
            }
            
            bool operator!=(const Vector2& other) const {
                return !(*this == other);
            }
            
            friend std::ostream& operator<<(std::ostream& os, const Vector2& vec) {
                os << "(" << vec.x << ", " << vec.y << ")";
                return os;
            }
                        
            [[nodiscard]] T dot(const Vector2& other) const {
                return x * other.x + y * other.y;
            }
                        
            [[nodiscard]] T lengthSquared() const {
                return x * x + y * y;
            }
            
            [[nodiscard]] T length() const {
                return std::sqrt(lengthSquared());
            }
            
            [[nodiscard]] Vector2 normalized() const {
                T len = length();                
                return *this / len;
            }
            
            void normalize() {
                T len = length();                
                *this /= len;
            }
    };

    using Vector2f = Vector2<float>;
    using Vector2d = Vector2<double>;    
}

