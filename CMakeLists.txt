cmake_minimum_required(VERSION 3.20)
project(KGG_CPP_Project_Repo LANGUAGES CXX C)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


cmake_policy(SET CMP0072 NEW)
set(OpenGL_GL_PREFERENCE GLVND)

# ---------- OpenGL / GLFW ----------
find_package(glfw3 CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
#
# ---------- SFML ----------
include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.1
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)
FetchContent_Declare(ImGui
        GIT_REPOSITORY https://github.com/ocornut/imgui
        GIT_TAG v1.91.1
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
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

target_link_libraries(imgui PUBLIC glfw)

FetchContent_GetProperties(ImGui SOURCE_DIR IMGUI_DIR)
set(IMGUI_SFML_FIND_SFML OFF)

FetchContent_Declare(ImGui-SFML
        GIT_REPOSITORY https://github.com/SFML/imgui-sfml
        GIT_TAG v3.0
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(ImGui-SFML)

# -------------------------------------
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
#set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)
# ---------- Main App ----------
add_executable(KGG_CPP_Project_Repo
        src/app/main.cpp
        src/Render/Render.cpp
        src/Render/shader.cpp
        src/Render/Mesh.cpp
        src/ReadWrite/Reader.cpp
        src/Light/Normal.cpp
        src/Scene/Camera.cpp
        src/UI/Button.cpp
        src/Window/Window.cpp
        src/app/main.cpp
        src/app/main.cpp
        src/Window/Framebuffer.cpp
        src/Render/Rasterizer.cpp
)

target_include_directories(KGG_CPP_Project_Repo
        PUBLIC include
        PRIVATE src
)
target_link_libraries(KGG_CPP_Project_Repo
        PRIVATE
        imgui
        glfw
        OpenGL::GL
        SFML::Graphics
        ImGui-SFML::ImGui-SFML
)
# ---------- Tests ----------
enable_testing()

add_executable(Test_Normals
        test/Test_Normals.cpp
)

target_link_libraries(Test_Normals
        PRIVATE
        GTest::gtest_main
)

add_test(NAME NormalsTests COMMAND Test_Normals)