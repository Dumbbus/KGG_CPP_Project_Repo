#include <iostream>
#include "Vector2.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"
#include "Matrix3.hpp"
#include "Matrix4.hpp"

void testVector3() {
    std::cout << "Vector3:" << std::endl;
    
    gmath::Vector3f v1(1.0f, 2.0f, 3.0f);
    gmath::Vector3f v2(4.0f, 5.0f, 6.0f);
    
    std::cout << "v1 = " << v1 << std::endl;
    std::cout << "v2 = " << v2 << std::endl;
    
    gmath::Vector3f cross = v1.cross(v2);
    std::cout << "v1 cross v2 = " << cross << std::endl;
        
    std::cout << "v1.dot(cross) = " << v1.dot(cross) << " должно быть 0" << std::endl;
    std::cout << "v2.dot(cross) = " << v2.dot(cross) << " должно быть 0" << std::endl;
    
    std::cout << "Длина v1: " << v1.length() << std::endl;
    std::cout << "Нормализованный v1: " << v1.normalized() << std::endl;
    std::cout << "Длина нормализованного v1: " << v1.normalized().length() << std::endl;
    
    std::cout << "v1.dot(v2) = " << v1.dot(v2) << std::endl;
    
    std::cout << std::endl;
}

void testMatrix3() {
    std::cout << "matrix3:" << std::endl;
        
    gmath::Matrix3f edinich = gmath::Matrix3f::edinich();
        
    std::cout << "Единичная матрица 3x3:\n" << edinich << std::endl;
        
    std::cout << "Элемент (0,0): " << edinich(0, 0) << std::endl;
    std::cout << "Элемент (1,1): " << edinich(1, 1) << std::endl;
    std::cout << "Элемент (2,2): " << edinich(2, 2) << std::endl;
    std::cout << "Элемент (0,1) (должен быть 0): " << edinich(0, 1) << std::endl;
    
    gmath::Matrix3f zero = gmath::Matrix3f::zero();
    std::cout << "\nНулевая матрица 3x3:\n" << zero << std::endl;
        
    float values[3][3] = {
        {1.0f, 2.0f, 3.0f},
        {4.0f, 5.0f, 6.0f},
        {7.0f, 8.0f, 9.0f}
    };
    gmath::Matrix3f custom(values);
    std::cout << "\nПросто матрица:\n" << custom << std::endl;
        
    gmath::Vector3f vec3(1.0f, 2.0f, 3.0f);
    gmath::Vector3f result1 = edinich * vec3;
    std::cout << "\nУмножение единичной на вектор " << vec3 << ":\n";
    std::cout << "Результат: " << result1 << std::endl;
    std::cout << "Вектор не изменился: " << (vec3.equals(result1) ? "Да" : "Нет") << std::endl;
        
    gmath::Vector3f result2 = custom * vec3;
    std::cout << "\nУмножение просто матрицы на вектор " << vec3 << ":\n";
    std::cout << "Результат: " << result2 << std::endl;
        
    gmath::Matrix3f sum = edinich + custom;
    std::cout << "\nЕдиничная + просто матрица:\n" << sum << std::endl;
        
    gmath::Matrix3f mult = edinich * custom;
    std::cout << "Единичная * просто матрица:\n" << mult << std::endl;
    std::cout << "Результат равен исходной: " << (custom.equals(mult) ? "Да" : "Нет") << std::endl;
        
    gmath::Matrix3f transposed = custom.transposed();
    std::cout << "\nТранспонированная матрица (.transposed):\n" << transposed << std::endl;
        
    gmath::Matrix3f temp = custom;
    temp.transpose();
    std::cout << "Транспонирование через метод (.transpose):\n" << temp << std::endl;
    std::cout << "Результат совпадает: " << (temp.equals(transposed) ? "Да" : "Нет") << std::endl;
    
    std::cout << std::endl;
}

void testExceptions() {
    std::cout << "Exceptions" << std::endl;
    
    gmath::Vector3f vec(1.0f, 2.0f, 3.0f);
    gmath::Matrix3f mat;
    
    try {        
        gmath::Vector3f div_by_zero = vec / 0.0f;
    } catch (const std::runtime_error& e) {
        std::cout << "Nolik " << e.what() << std::endl;
    }
    
    try {        
        float value = mat(10, 10);
    } catch (const std::out_of_range& e) {
        std::cout << "Out of range " << e.what() << std::endl;
    }
    
    std::cout << std::endl;
}

int main() {

    testVector3();            
        
    testMatrix3();    
        
    testExceptions();            
    
    return 0;
}