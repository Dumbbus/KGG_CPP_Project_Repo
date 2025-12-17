// Source - https://stackoverflow.com/a/43464668
// Posted by Matt Martin
// Retrieved 2025-12-17, License - CC BY-SA 3.0

#define GLFW_DLL

#include <iostream>
#include "Window/Window.hpp"
#include <GLFW/glfw3.h>
#include <GL/gl.h>

void Window::create_Window() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return;
    }
    int width = 800;
    int height = 600;
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    GLFWwindow* window = glfwCreateWindow(width, height, "Test", NULL, NULL);
    if (!window) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);
    while (!glfwWindowShouldClose(window)) {
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);

        // Swap buffers and process events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Cleanup
    glfwDestroyWindow(window);
    glfwTerminate();
    return;
}