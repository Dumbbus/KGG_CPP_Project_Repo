#include <iostream>
#include "Window/Window.hpp"
#include <GLFW/glfw3.h>
#include <SFML/Graphics.hpp>
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui-SFML.h"
#include "imgui.h"
#include "ReadWrite/Object.h"
#include "ReadWrite/Reader.h"
#include "Render/Rasterizer.h"
#include "Window/Framebuffer.h"
#include "ReadWrite/Reader.h"
constexpr uint32_t WIDTH = 800;
constexpr uint32_t HEIGHT = 600;
std::vector<Object> objects;
void Window::create_Window() {
    Reader reader;
    //читаем объект
    Object value = reader.Read("resources/models/tetrahedron.obj");
    //запихиваем его в список объектов
    objects.insert(objects.begin(), value);

    sf::RenderWindow window(
    sf::VideoMode({WIDTH, HEIGHT}),
     "SFML + ImGui"
 );
    render::Framebuffer fb(WIDTH, HEIGHT);
    sf::Texture texture(sf::Vector2u(WIDTH, HEIGHT));

    sf::Sprite sprite(texture);


    window.setFramerateLimit(60);

    ImGui::SFML::Init(window);
    //Записываем значения объекта в переменные (просто для удобства. Можно убрать)
    sf::Clock deltaClock;
    vector<Vector3<float>> faces = objects.at(0).faces;
    vector<Vector3<float>> verticies = objects.at(0).vertices;

    Vector2 a = {verticies.at(0).x, verticies.at(0).y};
    Vector2 b = {verticies.at(1).x, verticies.at(1).y};
    Vector2 c = {verticies.at(2).x, verticies.at(2).y};

    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
            ImGui::SFML::ProcessEvent(window, *event);

            if (event->is<sf::Event::Closed>())
                window.close();
        }
        fb.clear(render::Color::black());

        render::Rasterizer::draw_triangle(fb, a, b, c, 255);

        ImGui::SFML::Update(window, deltaClock.restart());
        texture.update(fb.get_data());
        window.clear(sf::Color(100, 0, 0));
        window.draw(sprite);
        ImGui::Begin("Hello");
        ImGui::Text("SFML 3 + ImGui works");
        ImGui::Image(texture);
        ImGui::End();
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    return;

}
