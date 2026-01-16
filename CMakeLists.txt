# requirements
cmake_minimum_required(VERSION 3.20)
project(KGG_CPP_Project_Repo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# OpenGL / GLFW
cmake_policy(SET CMP0072 NEW)
set(OpenGL_GL_PREFERENCE GLVND)

find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

# FetchContent
include(FetchContent)

# SFML
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.1
)
FetchContent_MakeAvailable(SFML)

# ImGui
FetchContent_Declare(ImGui
        GIT_REPOSITORY https://github.com/ocornut/imgui
        GIT_TAG v1.91.1
)
FetchContent_MakeAvailable(ImGui)

add_library(imgui STATIC
        ${imgui_SOURCE_DIR}/imgui.cpp
        ${imgui_SOURCE_DIR}/imgui_draw.cpp
        ${imgui_SOURCE_DIR}/imgui_tables.cpp
        ${imgui_SOURCE_DIR}/imgui_widgets.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)

target_include_directories(imgui PUBLIC
        ${imgui_SOURCE_DIR}
        ${imgui_SOURCE_DIR}/backends
)

target_link_libraries(imgui PUBLIC glfw OpenGL::GL)

# ImGui-SFML
set(IMGUI_SFML_FIND_SFML OFF)

FetchContent_Declare(ImGui-SFML
        GIT_REPOSITORY https://github.com/SFML/imgui-sfml
        GIT_TAG v3.0
)

set(IMGUI_DIR ${imgui_SOURCE_DIR})

FetchContent_MakeAvailable(ImGui-SFML)

# ImGuiFileDialog
FetchContent_Declare(ImGuiFileDialog
        GIT_REPOSITORY https://github.com/aiekick/ImGuiFileDialog
        GIT_TAG master # Рекомендуется указать тег для стабильности
)

FetchContent_MakeAvailable(ImGuiFileDialog)

# ВАЖНО: ImGuiFileDialog - это таргет, созданный внутри библиотеки.
# Мы насильно пробрасываем ему пути к заголовкам ImGui, которые он не может найти.
if(TARGET ImGuiFileDialog)
    target_include_directories(ImGuiFileDialog PUBLIC ${imgui_SOURCE_DIR})
endif()

# CORE
add_library(kgg_core
        src/Render/Render.cpp
        src/Render/shader.cpp
        src/Render/Mesh.cpp
        src/Render/Rasterizer.cpp
        src/Render/Texture.cpp

        src/Scene/Camera.cpp
        src/Scene/Scene.cpp
        src/Scene/Transform.cpp
        src/Scene/Projection.cpp

        src/Light/Normal.cpp

        src/ReadWrite/Reader.cpp
        src/ReadWrite/Object.cpp
        src/ReadWrite/Write.cpp

        src/Window/Framebuffer.cpp
        src/Window/Window.cpp
)

target_include_directories(kgg_core PUBLIC include)

target_link_libraries(kgg_core
        PUBLIC
        SFML::System
        OpenGL::GL
        ImGui-SFML::ImGui-SFML
        ImGuiFileDialog
)

add_compile_definitions(_USE_MATH_DEFINES)

# APP
add_executable(KGG_CPP_Project_Repo
        src/app/main.cpp
        src/UI/Button.cpp
        src/Window/Window.cpp
        src/Window/Framebuffer.cpp
)

target_link_libraries(KGG_CPP_Project_Repo
        PRIVATE
        kgg_core
        SFML::Graphics
        imgui
        ImGui-SFML::ImGui-SFML
        ImGuiFileDialog
)

# TESTS
enable_testing()

FetchContent_Declare(googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(Tests
        test/Test_Normals.cpp
        test/Test_Camera.cpp
        test/Test_Projection.cpp
        test/Test_Transform.cpp
        test/Test_Framebuffer.cpp
        test/Test_Texture.cpp
        test/Test_Render.cpp
        test/Test_Rasterizer.cpp
)

target_link_libraries(Tests
        PRIVATE
        kgg_core
        GTest::gtest_main
)

add_test(NAME TESTS COMMAND Tests)