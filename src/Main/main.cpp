//
// Created by akemi on 09.12.25.
//

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Vector2.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"
#include "Matrix3.hpp"
#include "../Headers/Window.hpp"

int main() {
    gmath::Vector3<float> a(1.0f, 2.0f, 3.0f);
    std::cout << a << std::endl;

    Window::create_Window();

    return 0;
}
