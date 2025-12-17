cmake_minimum_required(VERSION 3.10)
project(KGG_CPP_Project_Repo VERSION 1.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Включаем подпапки с заголовочными файлами
include_directories(
        src/main/light
        src/main/math
        src/main/readwrite
        src/main/window
        external/imgui
        headers

)

# Собираем все cpp-файлы из подпапок
file(GLOB LIGHT_SOURCES "src/main/light/*.cpp")
file(GLOB MATH_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/Main/Math/*.cpp")
file(GLOB RW_SOURCES "src/main/readwrite/*.cpp")
file(GLOB WINDOW_SOURCES "src/main/window/*.cpp")
file(GLOB GLAD_SOURCES "external/*.c")


# Основной список исходников
set(SOURCES
        src/main/main.cpp
        ${GLAD_SOURCES} ${GLAD_HEADERS}
        ${LIGHT_SOURCES} ${LIGHT_HEADERS}
        ${MATH_SOURCES} ${MATH_HEADERS}
        ${RW_SOURCES} ${RW_HEADERS}
        ${WINDOW_SOURCES} ${WINDOW_HEADERS}
        src/main/math/Vector2.hpp

)

# Создаем исполняемый файл
add_executable(
        ${PROJECT_NAME} ${SOURCES}
)

# Подключаем SFML через FetchContent
include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.2
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)

# Линкуем нужные SFML компоненты (Graphics подтянет Window и System автоматически)
target_link_libraries(${PROJECT_NAME} PRIVATE SFML::Graphics)