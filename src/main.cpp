//
// Created by akemi on 09.12.25.
//

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Math/Vector2.hpp"
#include "Math/Vector3.hpp"
#include <Math/Vector4.hpp>
#include <Math/Matrix3.hpp>
#include "Window/Window.hpp"

int main() {
    const gmath::Vector3<float> a(1.0f, 2.0f, 3.0f);
    std::cout << a << std::endl;

    Window::create_Window();

    return 0;
}
