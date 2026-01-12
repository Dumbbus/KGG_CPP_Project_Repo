#include "Window/Window.hpp"

#include <iostream>
#include <SFML/Graphics.hpp>
#include "imgui-SFML.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "ImGuiFileDialog.h"
#include "ReadWrite/Object.hpp"
#include "ReadWrite/Reader.h"
#include "Render/Rasterizer.h"
#include "Window/Framebuffer.h"
#include "Scene/Camera.h"
#include "Scene/Projection.h"
#include "Scene/Transform.h"
#include "Render/Mesh.hpp"
#include "Render/Render.h"
#include "Scene/Scene.h"
using namespace std;
constexpr uint32_t WIDTH = 800;
constexpr uint32_t HEIGHT = 600;
bool opened = true;
bool* openedd = &opened;
vector<Scene*> scenes;//Vector of pointers to scenes
Reader reader;
Viewport viewport{(double) HEIGHT, (double) WIDTH};
Render renderer;
int chosen_scene = 0;
int chosen_object = 0;
gmath::Vector3<double> kfkd = {0, 0, -4};
bool is_flat_shading = true;
constexpr double MIN_DISTANCE = 3.5;

void style() {
    ImVec4* colors = ImGui::GetStyle().Colors;
colors[ImGuiCol_Text]                   = ImVec4(0.90f, 0.90f, 0.90f, 1.00f);
colors[ImGuiCol_TextDisabled]           = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
colors[ImGuiCol_WindowBg]               = ImVec4(0.01f, 0.15f, 0.02f, 0.85f);
colors[ImGuiCol_ChildBg]                = ImVec4(0.22f, 0.19f, 0.19f, 0.00f);
colors[ImGuiCol_PopupBg]                = ImVec4(0.11f, 0.11f, 0.14f, 0.92f);
colors[ImGuiCol_Border]                 = ImVec4(0.50f, 0.50f, 0.50f, 0.50f);
colors[ImGuiCol_BorderShadow]           = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
colors[ImGuiCol_FrameBg]                = ImVec4(0.43f, 0.43f, 0.43f, 0.39f);
colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.09f, 0.52f, 0.23f, 0.40f);
colors[ImGuiCol_FrameBgActive]          = ImVec4(0.06f, 0.54f, 0.30f, 0.69f);
colors[ImGuiCol_TitleBg]                = ImVec4(0.05f, 0.25f, 0.10f, 0.83f);
colors[ImGuiCol_TitleBgActive]          = ImVec4(0.05f, 0.30f, 0.09f, 0.87f);
colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(0.07f, 0.43f, 0.34f, 0.20f);
colors[ImGuiCol_MenuBarBg]              = ImVec4(0.12f, 0.40f, 0.32f, 0.80f);
colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.20f, 0.25f, 0.30f, 0.60f);
colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.56f, 0.56f, 0.76f, 0.30f);
colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.23f, 0.23f, 0.58f, 0.40f);
colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.41f, 0.39f, 0.80f, 0.60f);
colors[ImGuiCol_CheckMark]              = ImVec4(0.90f, 0.90f, 0.90f, 0.50f);
colors[ImGuiCol_SliderGrab]             = ImVec4(1.00f, 1.00f, 1.00f, 0.30f);
colors[ImGuiCol_SliderGrabActive]       = ImVec4(0.41f, 0.39f, 0.80f, 0.60f);
colors[ImGuiCol_Button]                 = ImVec4(0.26f, 0.57f, 0.63f, 0.62f);
colors[ImGuiCol_ButtonHovered]          = ImVec4(0.35f, 0.72f, 0.46f, 0.79f);
colors[ImGuiCol_ButtonActive]           = ImVec4(0.46f, 0.80f, 0.79f, 1.00f);
colors[ImGuiCol_Header]                 = ImVec4(0.32f, 0.68f, 0.36f, 0.45f);
colors[ImGuiCol_HeaderHovered]          = ImVec4(0.15f, 0.67f, 0.12f, 0.80f);
colors[ImGuiCol_HeaderActive]           = ImVec4(0.53f, 0.53f, 0.87f, 0.80f);
colors[ImGuiCol_Separator]              = ImVec4(0.50f, 0.50f, 0.50f, 0.60f);
colors[ImGuiCol_SeparatorHovered]       = ImVec4(0.60f, 0.60f, 0.70f, 1.00f);
colors[ImGuiCol_SeparatorActive]        = ImVec4(0.70f, 0.70f, 0.90f, 1.00f);
colors[ImGuiCol_ResizeGrip]             = ImVec4(1.00f, 1.00f, 1.00f, 0.10f);
colors[ImGuiCol_ResizeGripHovered]      = ImVec4(0.78f, 0.82f, 1.00f, 0.60f);
colors[ImGuiCol_ResizeGripActive]       = ImVec4(0.78f, 0.82f, 1.00f, 0.90f);
colors[ImGuiCol_TabHovered]             = ImVec4(0.12f, 0.41f, 0.25f, 0.80f);
colors[ImGuiCol_Tab]                    = ImVec4(0.15f, 0.64f, 0.56f, 0.79f);
colors[ImGuiCol_TabSelected]            = ImVec4(0.00f, 0.61f, 0.30f, 0.84f);
colors[ImGuiCol_TabSelectedOverline]    = ImVec4(0.53f, 0.53f, 0.87f, 0.80f);
colors[ImGuiCol_TabDimmed]              = ImVec4(0.28f, 0.28f, 0.57f, 0.82f);
colors[ImGuiCol_TabDimmedSelected]      = ImVec4(0.35f, 0.35f, 0.65f, 0.84f);
colors[ImGuiCol_TabDimmedSelectedOverline]  = ImVec4(0.53f, 0.53f, 0.87f, 0.80f);
colors[ImGuiCol_PlotLines]              = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
colors[ImGuiCol_PlotLinesHovered]       = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
colors[ImGuiCol_PlotHistogram]          = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
colors[ImGuiCol_PlotHistogramHovered]   = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
colors[ImGuiCol_TableHeaderBg]          = ImVec4(0.27f, 0.27f, 0.38f, 1.00f);
colors[ImGuiCol_TableBorderStrong]      = ImVec4(0.31f, 0.31f, 0.45f, 1.00f);
colors[ImGuiCol_TableBorderLight]       = ImVec4(0.26f, 0.26f, 0.28f, 1.00f);
colors[ImGuiCol_TableRowBg]             = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
colors[ImGuiCol_TableRowBgAlt]          = ImVec4(1.00f, 1.00f, 1.00f, 0.07f);
colors[ImGuiCol_TextLink]               = ImVec4(0.53f, 0.53f, 0.87f, 0.80f);
colors[ImGuiCol_TextSelectedBg]         = ImVec4(0.00f, 0.00f, 1.00f, 0.35f);
colors[ImGuiCol_DragDropTarget]         = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
colors[ImGuiCol_NavHighlight]           = ImVec4(0.45f, 0.45f, 0.90f, 0.80f);
colors[ImGuiCol_NavWindowingHighlight]  = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
colors[ImGuiCol_NavWindowingDimBg]      = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
colors[ImGuiCol_ModalWindowDimBg]       = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
}

void Window::create_Window() {
    Camera camera({0, 0, 0}, {0, 0, -5}, {0, 1, 0});
    Projection projection(90.0, (double) WIDTH / HEIGHT, 0.35, 100.0);
    //здесь создаётся сцена, в будующем можно создать ещё
    scenes.push_back(new Scene(camera, projection));

    sf::RenderWindow window(
    sf::VideoMode({WIDTH, HEIGHT}), "3dViewer");
    Framebuffer fb(WIDTH, HEIGHT);
    sf::Texture texture(sf::Vector2u(WIDTH, HEIGHT));
    sf::Sprite sprite(texture);
    Rasterizer rasterizer;
    window.setFramerateLimit(60);
    float ambient = 1.0f;
    gmath::Vector3f light_direction = {0.0f, 0.0f, 1.0f};
    light_direction.normalize();


    ImGui::SFML::Init(window);
    //Записываем значения объекта в переменные (просто для удобства. Можно убрать)
    sf::Clock deltaClock;

    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            ImGui::SFML::ProcessEvent(window, *event);
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (const auto* wheel = event->getIf<sf::Event::MouseWheelScrolled>()) {
                if (wheel->wheel == sf::Mouse::Wheel::Vertical) {
                    Scene* scene = scenes.at(chosen_scene);
                    gmath::Vector3d dir = scene->camera.get_target() - scene->camera.get_eye();
                    dir.normalize();

                    float distance = (scene->camera.get_target() - scene->camera.get_eye()).length();
                    float zoom_step = wheel->delta * 0.1 * distance;

                    double new_distance = distance - zoom_step;

                    if (new_distance > MIN_DISTANCE) {
                        scene->camera.set_position(scene->camera.get_eye() + dir * zoom_step);
                        //scene->camera.set_target(scene->camera.get_target() + dir * zoom_step);
                    }

                    std::cout << "Eye: " << scene->camera.get_eye() << "\n";
                    std::cout << "Target: " << scene->camera.get_target() << "\n";
                }
            }

            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->scancode == sf::Keyboard::Scan::LShift) {
                    cout << "Hello world" << endl;
                }
            }
        }

        //clear
        fb.clear(Color::white());
        fb.clear_depth(1.0f);

        //scene drawing
        if (scenes.at(chosen_scene)->objects3d.size() != 0) {
            for (Object& object : scenes.at(chosen_scene)->objects3d) {
                object.transform.rotate({0, -0.01, -0.01});
                //object.transform.translate({0, 0, 0.05f});

                // const auto processed_mesh = Render::process_mesh(
                //     object.mesh.get_vertices(),
                //     object.transform.get_model_matrix(),
                //     scenes.at(chosen_scene)->projection.get_projection_matrix(),
                //     scenes.at(chosen_scene)->camera.get_view_matrix(),
                //     WIDTH,
                //     HEIGHT
                //     );

                const auto processed_mesh = Render::process_mesh_with_normals(
                    object.mesh.get_vertices(),
                    object.mesh.get_normals(),
                    object.transform.get_model_matrix(),
                    scenes.at(chosen_scene)->projection.get_projection_matrix(),
                    scenes.at(chosen_scene)->camera.get_view_matrix(),
                    WIDTH,
                    HEIGHT
                );

                std::vector<gmath::Vector3d> transformed_face_normals;
                transformed_face_normals.reserve(object.mesh.m_faces.size());
                if (is_flat_shading) {
                    transformed_face_normals = Render::process_face_normals(
                        object.mesh.get_faces_normals(),
                        object.transform.get_model_matrix(),
                        scenes.at(chosen_scene)->projection.get_projection_matrix(),
                        scenes.at(chosen_scene)->camera.get_view_matrix()
                    );
                }

                // rasterizer.draw_shape(fb,
                //     processed_mesh,
                //     object.mesh.m_faces, Color::yellow());

                rasterizer.draw_shape_soft_shadow(
                    fb,
                    processed_mesh,
                    object.mesh.m_faces,
                    transformed_face_normals,
                        is_flat_shading,
                    light_direction,
                    ambient,
                    Color::yellow()
                    );

                // rasterizer.draw_wireframe(
                //     fb,
                //     processed_mesh,
                //     object.mesh.m_faces,
                //     Color::black()
                // );
            }
        }
        ImGui::SFML::Update(window, deltaClock.restart());
        //


        //Imgui
        style();
        //ImGui::ShowDemoWindow();

        //Menu begin
        if (ImGui::BeginMainMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("Create")) {

                }
                if (ImGui::MenuItem("Open", "Ctrl+O")) {
                    IGFD::FileDialogConfig config;
                    config.path = ".";
                    config.filePathName = "/home/lunarimoonlin/KGG_CPP_Project_Repo/resources/models/";
                    ImGuiFileDialog::Instance()->OpenDialog(
                        "FileChooser", "File Explorer",
                        ".obj", config);
                }
                if (ImGui::MenuItem("Scene", "Alt+S")) {

                }
                if (ImGui::MenuItem("Save", "Ctrl+S")) {
                }
                if (ImGui::MenuItem("Save as..")) {
                }
                ImGui::EndMenu();
            }
            ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
            ImGui::EndMainMenuBar();
        }
        //Menu end

        //File explorer instance processing
        // |
        // |
        // V
        if (ImGuiFileDialog::Instance()->Display("FileChooser")) {
            if (ImGuiFileDialog::Instance()->IsOk()) {
                std::string filePath = ImGuiFileDialog::Instance()->GetFilePathName();
                // vec.at(n)->val == (*vec.at(n)).val
                scenes.at(chosen_scene)->addObject3d(reader.Read(filePath));
                scenes.at(chosen_scene)->objects3d.back().transform.set_position(kfkd);
                scenes.at(chosen_scene)->objects3d.back().transform.rotate({0, -0.1, -0.1});
                kfkd.x--;
                kfkd.y--;
                kfkd.z--;
            }
            ImGuiFileDialog::Instance()->Close();
        }

        //Render
        texture.update(fb.get_data());
        window.clear(sf::Color(100, 0, 0));
        window.draw(sprite);
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
}
