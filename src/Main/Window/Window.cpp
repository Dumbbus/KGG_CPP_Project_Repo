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
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.majorVersion = 2;
    settings.minorVersion = 1;
    sf::Window window(sf::VideoMode({800, 600}, 64), "Simple 3D Cube",
                      static_cast<sf::State>(sf::Style::Default), settings);
    if (!gladLoadGL()) {
        return;
    }
    //Активация глубины
    glEnable(GL_DEPTH_TEST);
    //glDepthMask(GL_TRUE);

    // Projection matrix
    //Переключение стака матриц на матрицу проекции
    glMatrixMode(GL_PROJECTION);
    //Замена текущей матрицы на выбранную
    glLoadIdentity();
    //Ниже выделена текущая реализация работы с перспективой камеры
    //
    //gluPerspective(70.f, 800.f / 600.f, 1.f, 100.f);
    float fov = 70.f * 3.14159f / 180.f;
    float aspect = 800.f / 600.f;
    float near = 1.f;
    float far = 100.f;

    float top = tan(fov / 2.f) * near;
    float right = top * aspect;

    glFrustum(-right, right, -top, top, near, far);
    //


    glMatrixMode(GL_MODELVIEW);

    float angle = 0.f;


    while (window.isOpen()) {
        //usleep(20000);
        // pollEvent теперь возвращает std::optional<Event>
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }
        //очиска каналов глубины
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        //умножить текущую матрицу в стаке на матрицу переноса (передаётся параметрами в скобочках)
        //тоесть переместить модель на xyz без потери пропорций
        glTranslatef(0.f, 0.f, -10.f);
        glRotatef(angle, 1.f, -1.f, -1.f);
        drawcube();
        angle += 0.003f;
        window.display();
    }
}
    void Window::drawcube(){
    //загружаем куб в стак
        glBegin(GL_QUADS);

        // Front
        glColor3f(1.f, 0.f, 0.f);
        glVertex3f(-1.f, -1.f,  1.f);
        glVertex3f( 1.f, -1.f,  1.f);
        glVertex3f( 1.f,  1.f,  1.f);
        glVertex3f(-1.f,  1.f,  1.f);

    glColor3f(1.f, 0.f, 0.f);
    glVertex3f(-2.f, -1.f,  1.f);
    glVertex3f( 2.f, -1.f,  1.f);
    glVertex3f( 2.f,  1.f,  1.f);
    glVertex3f(-1.f,  1.f,  1.f);

        // Back
        glColor3f(0.f, 1.f, 0.f);
        glVertex3f(-1.f, -1.f, -1.f);
        glVertex3f(-1.f,  1.f, -1.f);
        glVertex3f( 1.f,  1.f, -1.f);
        glVertex3f( 1.f, -1.f, -1.f);

        // Left
        glColor3f(0.f, 0.f, 1.f);
        glVertex3f(-1.f, -1.f, -1.f);
        glVertex3f(-1.f, -1.f,  1.f);
        glVertex3f(-1.f,  1.f,  1.f);
        glVertex3f(-1.f,  1.f, -1.f);

        // Right
        glColor3f(1.f, 1.f, 0.f);
        glVertex3f(1.f, -1.f, -1.f);
        glVertex3f(1.f,  1.f, -1.f);
        glVertex3f(1.f,  1.f,  1.f);
        glVertex3f(1.f, -1.f,  1.f);

        // Top
        glColor3f(0.f, 1.f, 1.f);
        glVertex3f(-1.f, 1.f, -1.f);
        glVertex3f(-1.f, 1.f,  1.f);
        glVertex3f( 1.f, 1.f,  1.f);
        glVertex3f( 1.f, 1.f, -1.f);

        // Bottom
        glColor3f(1.f, 0.f, 1.f);
        glVertex3f(-1.f, -1.f, -1.f);
        glVertex3f( 1.f, -1.f, -1.f);
        glVertex3f( 1.f, -1.f,  1.f);
        glVertex3f(-1.f, -1.f,  1.f);

        glEnd();
    }