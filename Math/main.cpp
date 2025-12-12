#include "Vector2.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"
#include <iostream>

int main() {
    std::cout << 123 << "\n";

    gmath::Vector2f vec(2.3, 4.3);
    gmath::Vector2f vek(2.4, 6.2);

    float abv = vec.dot(vek);

    std::cout << abv << "\n";
}