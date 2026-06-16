cmake_minimum_required(VERSION 3.31)
project(GiPO)

set(CMAKE_CXX_STANDARD 20)

add_library(glad STATIC glad.c)
set_target_properties(glad PROPERTIES LINKER_LANGUAGE C)
target_include_directories(glad PUBLIC "${CMAKE_SOURCE_DIR}/include")

file(GLOB IMGUI_SOURCES "${CMAKE_SOURCE_DIR}/include/imgui/*.cpp")

add_executable(GiPO src/main.cpp
        src/Renderer.cpp
        include/Renderer.h
        include/Shader.h
        src/Camera.cpp
        include/Camera.h
        ${IMGUI_SOURCES}
        src/Frame.cpp
        include/Frame.h)

target_include_directories(GiPO PRIVATE
        "${CMAKE_SOURCE_DIR}/include"
        "${CMAKE_SOURCE_DIR}/include/imgui"
)

target_link_libraries(GiPO PRIVATE
        glad
        "${CMAKE_SOURCE_DIR}/lib/glfw3.lib"
        opengl32
        gdi32
        user32
        shell32
)
