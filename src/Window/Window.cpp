#include "Window/Window.hpp"
#include <SFML/Graphics.hpp>
#include "imgui-SFML.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "ImGuiFileDialog.h"
#include "ReadWrite/Object.h"
#include "ReadWrite/Reader.h"
#include "Render/Rasterizer.h"
#include "Window/Framebuffer.h"
constexpr uint32_t WIDTH = 800;
constexpr uint32_t HEIGHT = 600;
bool opened = true;
bool* openedd = &opened;
std::vector<Object> objects3d;
Reader reader;
Object object3d;





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

    objects3d.insert(objects3d.begin(), object3d);

    sf::RenderWindow window(
    sf::VideoMode({WIDTH, HEIGHT}), "3dViewer");
    render::Framebuffer fb(WIDTH, HEIGHT);
    sf::Texture texture(sf::Vector2u(WIDTH, HEIGHT));
    sf::Sprite sprite(texture);

    window.setFramerateLimit(60);

    ImGui::SFML::Init(window);//
    //Записываем значения объекта в переменные (просто для удобства. Можно убрать)
    sf::Clock deltaClock;
    vector<Vector3<float>> faces;
    vector<Vector3<float>> verticies;
    Vector2<float> a;
    Vector2<float> b;
    Vector2<float> c;
    Vector2<float> d;
    vector<Vector2<float>> vec;

    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
            ImGui::SFML::ProcessEvent(window, *event);
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        fb.clear(render::Color::black());
        if (!vec.empty()) {
            render::Rasterizer::draw_triangle(fb, vec.at(faces.at(3).x), vec.at(faces.at(3).y), vec.at(faces.at(3).z), 75);
            render::Rasterizer::draw_triangle(fb, vec.at(faces.at(1).x), vec.at(faces.at(1).y), vec.at(faces.at(1).z), 100);
            render::Rasterizer::draw_triangle(fb, vec.at(faces.at(0).x), vec.at(faces.at(0).y), vec.at(faces.at(0).z), 200);
            //render::Rasterizer::draw_triangle(fb, vec.at(faces.at(2).x), vec.at(faces.at(2).y), vec.at(faces.at(2).z), 60);
        }
        ImGui::SFML::Update(window, deltaClock.restart());

        texture.update(fb.get_data());
        window.clear(sf::Color(100, 0, 0));
        window.draw(sprite);

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
                if (ImGui::MenuItem("Save", "Ctrl+S")) {
                }
                if (ImGui::MenuItem("Save as..")) {
                }
                ImGui::EndMenu();
            }
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
                object3d = reader.Read(filePath);
                objects3d.insert(objects3d.begin(), object3d);


                faces = objects3d.at(0).faces;
                verticies = objects3d.at(0).vertices;
                a = {verticies.at(0).x, verticies.at(0).y};
                b = {verticies.at(1).x, verticies.at(1).y};
                c = {verticies.at(2).x, verticies.at(2).y};
                d = {verticies.at(3).x-10, verticies.at(3).y};
                vec = {a, b, c, d};
            }
            ImGuiFileDialog::Instance()->Close();
        }

        //Render
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    return;

}
