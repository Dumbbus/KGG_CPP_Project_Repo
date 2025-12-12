
#pragma once

#include <concepts>
#include <cmath>
#include <ostream>
#include <stdexcept>

#include "MConcepts.hpp"


namespace gmath {

    

    /**
     * @class Vector2
     * @brief Шаблонный класс для работы с 2D векторами
     * @tparam T Тип координат вектора (float или double)
     *      
     */
    template<is_float_double T> class Vector2 {
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
                       
            /**
             * @brief Скалярное произведение векторов
             * @param other Второй вектор
             * @return Скалярное произведение - число
             */
            [[nodiscard]] T dot(const Vector2& other) const {
                return x * other.x + y * other.y;
            }
                        
            [[nodiscard]] T length_squared() const noexcept {
                return x * x + y * y;
            }
            
            [[nodiscard]] T length() const noexcept {
                return std::sqrt(length_squared());
            }
            
            [[nodiscard]] Vector2 normalized() const {
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

    using Vector2f = Vector2<float>;
    using Vector2d = Vector2<double>;    
}

