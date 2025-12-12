cmake_minimum_required(VERSION 3.10)

project(KGG_CPP_Project_Repo VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Включаем подпапки с заголовочными файлами
include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/Light
        ${CMAKE_CURRENT_SOURCE_DIR}/Math
        ${CMAKE_CURRENT_SOURCE_DIR}/ReadWrite
        ${CMAKE_CURRENT_SOURCE_DIR}/Window
)

# Собираем все cpp-файлы из подпапок
file(GLOB LIGHT_SOURCES "Light/*.cpp")
file(GLOB MATH_SOURCES "Math/*.cpp")
file(GLOB RW_SOURCES "ReadWrite/*.cpp")
file(GLOB WINDOW_SOURCES "Window/*.cpp")

# Основной список исходников
set(SOURCES
        main.cpp
        ${LIGHT_SOURCES} ${LIGHT_HEADERS}
        ${MATH_SOURCES} ${MATH_HEADERS}
        ${RW_SOURCES} ${RW_HEADERS}
        ${WINDOW_SOURCES} ${WINDOW_HEADERS}
)

# Создаем исполняемый файл
add_executable(${PROJECT_NAME} ${SOURCES})

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