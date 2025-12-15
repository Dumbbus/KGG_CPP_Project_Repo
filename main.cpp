#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <Vector3.hpp>

int main() {
    gmath::Vector3<float> a(1.0f, 2.0f, 3.0f);
    std::cout << a << std::endl;

    sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML Example");

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen()) {
        // pollEvent теперь возвращает std::optional<Event>
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}
