cmake_minimum_required(VERSION 3.20)
project(KGG_CPP_Project_Repo LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

cmake_policy(SET CMP0072 NEW)
set(OpenGL_GL_PREFERENCE GLVND)

# ---------- OpenGL / GLFW ----------
find_package(glfw3 CONFIG REQUIRED)
find_package(OpenGL REQUIRED)

# ---------- GLAD ----------
add_library(glad STATIC External/khrplatform/glad.c)
target_include_directories(glad PUBLIC External/khrplatform)
set_target_properties(glad PROPERTIES LINKER_LANGUAGE C)

# ---------- SFML ----------
include(FetchContent)
FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.2
)
FetchContent_MakeAvailable(SFML)

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
)

target_include_directories(KGG_CPP_Project_Repo
        PUBLIC Include
        PRIVATE src
)

target_link_libraries(KGG_CPP_Project_Repo
        PRIVATE
        glad
        glfw
        OpenGL::GL
        SFML::Graphics
)

# ---------- Tests ----------
enable_testing()

add_executable(Test_Normals Test/Test_Normals.cpp)
target_include_directories(Test_Normals PRIVATE Include)

find_package(GTest CONFIG REQUIRED)
target_link_libraries(Test_Normals PRIVATE GTest::gtest_main glad)

add_test(NAME Testing_Normals COMMAND Test_Normals)
