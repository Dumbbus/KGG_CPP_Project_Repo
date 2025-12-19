cmake_minimum_required(VERSION 3.20)
project(KGG_CPP_Project_Repo LANGUAGES CXX C)

include(FetchContent)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

cmake_policy(SET CMP0072 NEW)
set(OpenGL_GL_PREFERENCE GLVND)

# ---------- Google Tests ----------
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE) # ВАЖНО для MSVC

FetchContent_Declare(
        googletest
        SOURCE_DIR ${CMAKE_SOURCE_DIR}/external/googletest
)
FetchContent_MakeAvailable(googletest)

# ---------- OpenGL / GLFW ----------
find_package(glfw3 CONFIG REQUIRED)
find_package(OpenGL REQUIRED)

# ---------- SFML ----------
FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.2
)
FetchContent_MakeAvailable(SFML)

# ---------- Core Library ----------
add_library(KGG_Core
        src/Render/Render.cpp
        src/Render/shader.cpp
        src/Render/Mesh.cpp
        src/ReadWrite/Reader.cpp
        src/Light/Normal.cpp
        src/Scene/Camera.cpp
        src/UI/Button.cpp
        src/Window/Window.cpp
        src/Window/Framebuffer.cpp
        src/Render/Rasterizer.cpp
)

target_include_directories(KGG_Core
        PUBLIC include
)

target_link_libraries(KGG_Core
        PUBLIC
        glfw
        OpenGL::GL
        SFML::Graphics
)

# ---------- Main App ----------
add_executable(KGG_CPP_Project_Repo
        src/app/main.cpp
)

target_link_libraries(KGG_CPP_Project_Repo
        PRIVATE KGG_Core
)


# ---------- Tests ----------
enable_testing()

add_executable(Test_Normals
        test/Test_Normals.cpp
)

target_link_libraries(Test_Normals
        PRIVATE
        KGG_Core
        GTest::gtest_main
)

add_test(NAME NormalsTests COMMAND Test_Normals)