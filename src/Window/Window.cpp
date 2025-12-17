//
// Created by akemi on 09.12.2025.
//
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "../Headers/Window.hpp"

#include "Vector3.hpp"
void Window::create_Window() {
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
}