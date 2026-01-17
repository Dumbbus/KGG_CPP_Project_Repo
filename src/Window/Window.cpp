#include "Window/Window.hpp"

#include <iostream>
#include <SFML/Graphics.hpp>
#include "imgui-SFML.h"
#include "imgui.h"
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
#include "Light/Light_Point.hpp"
using namespace std;
constexpr uint32_t WIDTH = 800;
constexpr uint32_t HEIGHT = 600;
bool opened = true;
bool* openedd = &opened;
vector<Scene*> scenes;//Vector of pointers to scenes
Reader reader;
//Viewport viewport{(double) HEIGHT, (double) WIDTH};
Render renderer;
Object* pointer_to_object;
vector<Object*> objects_for_rotation;
int chosen_scene = 0;
int chosen_object = 0;
int chosen_polygon = 0;
bool is_flat_shading = false;
bool SCENE_SELECTER = false;
bool OBJECT_SELECTOR = false;
bool EDITOR = false;

constexpr double MIN_DISTANCE = 3.5;

std::string getOSName() {
    #ifdef _WIN32
    return "Windows 32-bit";
    #elif _WIN64
    return "Windows 64-bit";
    #elif __linux__
    return "Linux";
    #endif
}
void loadTextures(Object& object) {
        if (!object.mesh.m_texture) {
             object.mesh.m_texture = std::make_unique<Texture>();
        }
        if (!object.mesh.m_texture) {
            std::cout << "Texture pointer is null!\n";
        }

        sf::Image image;
        if (getOSName() == "Windows 32-bit" || getOSName() == "Windows 64-bit") {
            if (!image.loadFromFile("C:/MainFolder/KGG_CPP_Project_Repo/resources/models/caracal_texture.png")) {
                cout << "Failed to load img" << endl;
            }
        }
        else if (getOSName() == "Linux") {
            if (!image.loadFromFile("/home/akemi/CGG/GROUP_TASK/KGG_CPP_Project_Repo/resources/models/caracal_texture.png")) {
                cout << "Failed to load img" << endl;
            }
        }
        object.mesh.m_texture->width = image.getSize().x;
        object.mesh.m_texture->height = image.getSize().y;
        object.mesh.m_texture->channels = 4;
        object.mesh.m_texture->pixels.assign(image.getPixelsPtr(), image.getPixelsPtr() + object.mesh.m_texture->width * object.mesh.m_texture->height * 4);
}
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
void errase(Object* object) {
    Object* object_delete = object;
    auto& objects = scenes.at(chosen_scene)->objects3d;
    auto find_for_deletion = std::find_if(objects.begin(), objects.end(),
    [object_delete](const Object& obj) {
      return &obj == object_delete;  // Compare addresses
        });
    objects.erase(find_for_deletion);
}
void menues_pos(sf::RenderWindow& window, int indent) {
    ImGui::SetNextWindowPos(ImVec2(window.getSize().x/6 * indent, 19));
    ImGui::SetNextWindowSize(ImVec2(window.getSize().x/6, window.getSize().y - 19));
}
struct {
    double x = 0;
    double y = 0;
    double z = 0;
}pos_for_editor;
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
    float ambient = 0.25f;
    Light_Point lights_dots;
    lights_dots.add_light({{1.0f, 1.0f, -1.0f}, Color::blue(), 0.5f});
    //lights_dots.add_light({{0, 0, 5}, {255, 255, 255, 255}});

    ImGui::SFML::Init(window);

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
                    Camera& cam = scene->camera;

                    cam.set_distance(std::max(cam.get_distance() - wheel->delta * 0.1 * cam.get_distance(), MIN_DISTANCE));
                    cam.rotate_camera(0, 0);

                    std::cout << "Eye: " << scene->camera.get_eye() << "\n";
                    std::cout << "Target: " << scene->camera.get_target() << "\n";
                }
            }

            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->scancode == sf::Keyboard::Scan::LShift) {
                    cout << "Hello world" << endl;
                }
            }

            if (const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>()) {
                static int lastX = mouseMoved->position.x;
                static int lastY = mouseMoved->position.y;

                int dx = mouseMoved->position.x - lastX;
                int dy = mouseMoved->position.y - lastY;

                lastX = mouseMoved->position.x;
                lastY = mouseMoved->position.y;

                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                    Scene* scene = scenes.at(chosen_scene);
                    scene->camera.rotate_camera((float)dx, (float)dy);
                }

                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
                    Scene* scene = scenes.at(chosen_scene);
                    scene->camera.pan((float)dx, (float)dy);
                }
            }
        }

        //clear
        fb.clear(Color::white());
        fb.clear_depth(1.0f);

        //scene drawing
        if (scenes.at(chosen_scene)->objects3d.size() != 0) {
            for (Object& object : scenes.at(chosen_scene)->objects3d) {

                gmath::Matrix4d view_mat = scenes.at(chosen_scene)->camera.look_at();
                //gmath::Vector4d light_in_view = (view_mat * light_direction).normalized();
                //gmath::Vector3f light_dir_v = {(float)light_in_view.x, (float)light_in_view.y, (float)light_in_view.z};
                std::vector<Light> lights = lights_dots.transfer_light_to_view(
                    view_mat, object.transform.get_model_matrix(),
                    WIDTH, HEIGHT);
                //object.mesh.recompute_normals();

                const auto processed_mesh = Render::process_mesh(
                    object.mesh,
                    object.transform.get_model_matrix(),
                    scenes.at(chosen_scene)->camera.look_at(),
                    scenes.at(chosen_scene)->projection.get_projection_matrix(),
                    WIDTH,
                    HEIGHT
                );

                if (!object.mesh.m_texture) {
                    loadTextures(object);
                }

                std::vector<gmath::Vector3d> face_normals;
                if (is_flat_shading) {
                    face_normals = renderer.process_face_normals(
                        object.mesh.m_face_normals,
                        object.transform.get_model_matrix(),
                        scenes.at(chosen_scene)->camera.look_at()
                        );
                }

                rasterizer.draw_scene(
                    fb,
                    processed_mesh,
                    face_normals,
                    object.mesh.m_texture.get(),
                    is_flat_shading,
                    lights,
                    ambient,
                    Color::yellow()
                    );

                // rasterizer.draw_wireframe(
                //     fb,
                //     processed_mesh,
                //     Color::black()
                // );
            }
            for (Object* object : objects_for_rotation) {
                object->transform.rotate({0, 0.1, 0});
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
                if (ImGui::MenuItem("Scene")) {
                    SCENE_SELECTER = true;
                }
                if (ImGui::MenuItem("Edit")) {
                    OBJECT_SELECTOR = true;
                }
                if (ImGui::MenuItem("Open", "Ctrl+O")) {
                    IGFD::FileDialogConfig config;
                    config.path = ".";
                    config.filePathName = "/home/lunarimoonlin/KGG_CPP_Project_Repo/resources/models/";
                    ImGui::SetNextWindowSize(ImVec2(400, 500), ImGuiCond_FirstUseEver);
                    ImGuiFileDialog::Instance()->OpenDialog(
                        "FileChooser", "File Explorer",
                        ".obj", config);
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
        //menu end
        //scene menu start
        if (SCENE_SELECTER) {

            menues_pos(window,0);
            ImGui::Begin(" ", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);

            if (ImGui::Button("Create scene"))
            {
                scenes.emplace_back(new Scene(camera, projection));
            }

            for (int i = 0; i < scenes.size(); i++){
                if (ImGui::Button(("Scene" + std::to_string(i)).c_str()))
                {
                    chosen_scene = i;
                }
            }
            if (ImGui::Button("Close"))
            {
                SCENE_SELECTER = false;
            }
            ImGui::End();
        }
        //scene menu end
        //other menues
        if (OBJECT_SELECTOR) {
            if (SCENE_SELECTER) {
                menues_pos(window, 1);
            }
            else {
                menues_pos(window, 0);
            }
            int i = 0;
            ImGui::Begin("f", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
            for (Object& object : scenes.at(chosen_scene)->objects3d) {
                ImGui::PushID(i);
                ImGui::Text(object.name.c_str());
                if (ImGui::Button("Delete")) {
                    errase(&object);
                }
                ImGui::SameLine();
                if (ImGui::Button("Edit")) {
                    OBJECT_SELECTOR = false;
                    EDITOR = true;
                    pointer_to_object = &object;
                }
                ImGui::PopID();
                i++;
            }
            if (ImGui::Button("Close")) {
                OBJECT_SELECTOR = false;
            }
            ImGui::End();
        }
        if (EDITOR) {

            if (SCENE_SELECTER) {
                menues_pos(window, 1);
            }
            else {
                menues_pos(window, 0);
            }
            ImGui::Begin("f", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
            if (ImGui::InputInt("Delete poly", &chosen_polygon)) {
                chosen_polygon = abs(chosen_polygon);
                if (chosen_polygon > pointer_to_object->mesh.m_polygons.size()) {
                    chosen_polygon = pointer_to_object->mesh.m_polygons.size();
                }
                pointer_to_object->mesh.m_polygons.erase(pointer_to_object->mesh.m_polygons.begin() + chosen_polygon);
            }
            if (ImGui::Button("Add poly")) {
            }
            if (ImGui::Button("Move whole")) {
                gmath::Vector3<double> p(pos_for_editor.x, pos_for_editor.y, pos_for_editor.z);
                pointer_to_object->transform.set_position(p);
            }
            ImGui::InputDouble("x", &pos_for_editor.x);
            ImGui::InputDouble("y", &pos_for_editor.y);
            ImGui::InputDouble("z", &pos_for_editor.z);
            if (ImGui::Button("Make Rotate")) {
                objects_for_rotation.emplace_back(pointer_to_object);
            }
            if (ImGui::Button("Close")) {
                OBJECT_SELECTOR = true;
                EDITOR = false;
            }
            ImGui::End();
        }



        //File explorer instance processing
        // |
        // |
        // V
        if (ImGuiFileDialog::Instance()->Display("FileChooser")) {
            if (ImGuiFileDialog::Instance()->IsOk()) {
                gmath::Vector3<double> p(0, 0, -5);
                std::string filePath = ImGuiFileDialog::Instance()->GetFilePathName();
                // vec.at(n)->val == (*vec.at(n)).val
                scenes.at(chosen_scene)->addObject3d(reader.Read(filePath));
                scenes.at(chosen_scene)->objects3d.back().transform.set_position(p);
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

