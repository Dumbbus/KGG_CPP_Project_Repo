#include <iostream>
#include "Window/Window.hpp"
#include <GLFW/glfw3.h>
#include "backends/imgui_impl_opengl3.h"
#include <SFML/Graphics.hpp>

#include "imgui-SFML.h"
#include "Render/Rasterizer.h"
#include "Window/Framebuffer.h"
constexpr uint32_t WIDTH = 800;
constexpr uint32_t HEIGHT = 600;

void Window::create_Window() {
    sf::RenderWindow window(
     sf::VideoMode({WIDTH, HEIGHT}),
     "SFML + ImGui"
 );
    render::Framebuffer fb(WIDTH, HEIGHT);
    sf::Texture texture(sf::Vector2u(WIDTH, HEIGHT));

    sf::Sprite sprite(texture);


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
        fb.clear(render::Color::black());

        render::Rasterizer::draw_colored_triangle(
            fb,
            {200.f, 100.f},
            {600.f, 150.f},
            {400.f, 500.f},
            render::Color::red(),
            render::Color::blue(),
            render::Color::green()
            );
        ImGui::SFML::Update(window, deltaClock.restart());


        texture.setRepeated(false);
        texture.update(fb.get_data());

           window.clear(sf::Color(100, 0, 0));
        window.draw(sprite);
        ImGui::Begin("Hello");
        ImGui::Text("SFML 3 + ImGui works");
        ImGui::End();
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    return;

}
