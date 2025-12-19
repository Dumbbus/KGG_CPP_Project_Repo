#include <iostream>
#include "Window/Window.hpp"
#include <GLFW/glfw3.h>
#include "backends/imgui_impl_opengl3.h"
#include <SFML/Graphics.hpp>

#include "imgui-SFML.h"


void Window::create_Window() {
    sf::RenderWindow window(
     sf::VideoMode({800, 600}, 64),
     "SFML + ImGui"
 );

    window.setFramerateLimit(60);

    ImGui::SFML::Init(window);

    sf::Clock deltaClock;

    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
            ImGui::SFML::ProcessEvent(window, *event);

            if (event->is<sf::Event::Closed>())
                window.close();
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::Begin("Hello");
        ImGui::Text("SFML 3 + ImGui works");
        ImGui::End();

        window.clear(sf::Color(30, 30, 40));
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    return;

}
