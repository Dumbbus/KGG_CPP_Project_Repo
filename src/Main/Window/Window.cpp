//
// Created by akemi on 09.12.2025.
//
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Config.hpp>
#include "../Headers/Window.hpp"
#include "../Headers/glad.h"
#include "../../Headers/Render.h"
#include "GL/glu.h"

#include "Vector3.hpp"
void Window::create_Window() {
    sf::Window window(sf::VideoMode({800, 600});

    while (window.isOpen()) {

        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        window.display();
    }
}