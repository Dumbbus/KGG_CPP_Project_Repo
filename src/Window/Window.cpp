// Source - https://stackoverflow.com/a/43464668
// Posted by Matt Martin
// Retrieved 2025-12-17, License - CC BY-SA 3.0
#include <iostream>
#include "Window/Window.hpp"
#include <GLFW/glfw3.h>
#include <GL/gl.h>

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "Window/Framebuffer.h"
#include "Render/Rasterizer.h"

void Window::create_Window() {
    // if (!glfwInit()) {
    //     std::cerr << "Failed to initialize GLFW\n";
    //     return;
    // }
    // int width = 800;
    // int height = 600;
    // GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    // GLFWwindow* window = glfwCreateWindow(width, height, "Test", NULL, NULL);
    // if (!window) {
    //     std::cout << "Failed to create GLFW window" << std::endl;
    //     glfwTerminate();
    //     return;
    // }
    // glfwMakeContextCurrent(window);
    // while (!glfwWindowShouldClose(window)) {
    //     // Clear the screen
    //     glClear(GL_COLOR_BUFFER_BIT);
    //
    //     // Swap buffers and process events
    //     glfwSwapBuffers(window);
    //     glfwPollEvents();
    // }
    //
    // // Cleanup
    // glfwDestroyWindow(window);
    // glfwTerminate();
    // return;

    constexpr uint32_t WIDTH = 800;
    constexpr uint32_t HEIGHT = 600;

    sf::RenderWindow window(sf::VideoMode({WIDTH, HEIGHT}), "Render Test");

    render::Framebuffer fb(WIDTH, HEIGHT);

    sf::Texture texture(sf::Vector2u(WIDTH, HEIGHT));

    sf::Sprite sprite(texture);

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event -> is<sf::Event::Closed>()) {
                window.close();
            }
        }

        fb.clear(render::Color::black());
        //fb.set_pixel(400, 300, render::Color::red());

         // render::Rasterizer::draw_triangle(
         //     fb,
         //     {200.f, 100.f},
         //     {600.f, 150.f},
         //     {400.f, 500.f},
         //     render::Color::green()
         //     );

        render::Rasterizer::draw_colored_triangle(
            fb,
            {200.f, 100.f},
            {600.f, 150.f},
            {400.f, 500.f},
            render::Color::red(),
            render::Color::blue(),
            render::Color::green()
            );


        texture.update(fb.get_data());

        window.clear();
        window.draw(sprite);
        window.display();
    }
}
