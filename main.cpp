//
// Created by akemi on 09.12.25.
//

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Math/Vector2.hpp"
#include "Math/Vector3.hpp"
#include "Math/Vector4.hpp"
#include "Math/Matrix3x3.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML Example");
    window.setFramerateLimit(60);

    
    gmath::Vector3f vec(1.0f, 2.0f, 3.0f);
    std::cout << vec << std::endl;
    gmath::Vector3f a(1.0f, 2.0f, 3.0f);
    std::cout << a << std::endl;

    gmath::Matrix3x3f m();    
    
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close(); 
            }
            
            /*Здесь же обработка нажатий*/
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}
