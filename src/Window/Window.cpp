#include <iostream>
#include "Window/Window.hpp"
#include <GLFW/glfw3.h>
#include <SFML/Graphics.hpp>
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui-SFML.h"
#include "imgui.h"
#include "Render/Rasterizer.h"
#include "Window/Framebuffer.h"
#include "Scene/Camera.h"
#include "Scene/Projection.h"
#include "Scene/Transform.h"
#include "Render/Mesh.hpp"
#include "Render/Render.h"
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

    // Вершины пирамиды (x, y, z)
    std::vector<gmath::Vector3<double>> pyramid_vertices = {
        { 0.0,  1.0,  0.0}, // 0: Верхушка
        {-1.0, -1.0,  1.0}, // 1: Левый передний угол основания
        { 1.0, -1.0,  1.0}, // 2: Правый передний угол основания
        { 0.0, -1.0, -1.0}  // 3: Задний угол основания
    };

    // Нормали (можно оставить нулевыми или упрощенными)
    std::vector<gmath::Vector3<double>> pyramid_normals(4, {0, 0, 1});

    // Индексы граней (порядок вершин важен для правильной ориентации сторон)
    std::vector<int> pyramid_indices = {
        0, 1, 2, // Передняя грань
        0, 2, 3, // Правая грань
        0, 3, 1, // Левая грань
        1, 3, 2  // Основание
    };

    // Создаем куб или простой треугольник
    Mesh pyramide_mesh(pyramid_vertices, pyramid_normals, pyramid_indices);

    render::Object pyramide_obj(pyramide_mesh);
    pyramide_obj.transform.set_position({0, 0, -3});

    Camera camera({0, 0, 0}, {0, 0, -5}, {0, 1, 0});
    Projection projection(90.0, (double) WIDTH / HEIGHT, 0.1, 100.0);
    Viewport viewport{(double) HEIGHT, (double) WIDTH};
    Render renderer;

    window.setFramerateLimit(60);

    ImGui::SFML::Init(window);

    sf::Clock deltaClock;

    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            ImGui::SFML::ProcessEvent(window, *event);

            if (event->is<sf::Event::Closed>())
                window.close();
        }
        pyramide_obj.transform.rotate({0, 0.01, 0});

        fb.clear(render::Color::black());
        fb.clear_depth(1.0f);

        render::Rasterizer::draw_shape(fb, pyramide_obj, renderer, camera, projection, viewport);

        ImGui::SFML::Update(window, deltaClock.restart());
        texture.update(fb.get_data());
        window.clear(sf::Color(100, 0, 0));
        window.draw(sprite);
        ImGui::Begin("Hello");
        ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
        //ImGui::Image(texture);
        ImGui::End();
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
}
