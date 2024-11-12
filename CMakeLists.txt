# Set the minimum required CMake version
# Works with ARM architecture
cmake_minimum_required(VERSION 3.10)
project(GameEngine)
set(CMAKE_CXX_STANDARD 17)
add_executable(MyExecutable src/main.cpp src/glad.c)

find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)

target_include_directories(MyExecutable PRIVATE include)

target_link_libraries(MyExecutable OpenGL::GL glfw)