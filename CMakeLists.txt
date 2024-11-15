# Set the minimum required CMake version
# Works with ARM architecture & x64 Macs 
cmake_minimum_required(VERSION 3.10)
project(GameEngine)
set(CMAKE_CXX_STANDARD 17)
add_executable(MyExecutable src/main.cpp src/glad.c)


if(CMAKE_SYSTEM_PROCESSOR STREQUAL "arm64")
    set(CMAKE_OSX_ARCHITECTURES "arm64" CACHE STRING "Build for ARM architecture on Apple Silicon" FORCE)
elseif(CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64")
    set(CMAKE_OSX_ARCHITECTURES "x86_64" CACHE STRING "Build for x64 architecture on Intel Macs" FORCE)
endif()

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the build type (Debug or Release)" FORCE)
endif()

find_package(OpenGL REQUIRED)

if(WIN32)
    # Find GLFW on Windows (installed via vcpkg or manually)
    find_package(glfw3 REQUIRED PATHS C:/path/to/vcpkg/installed/x64-windows/share/glfw3 NO_DEFAULT_PATH) #Update with your path for local build
elseif(APPLE)
    # Find GLFW on macOS (typically installed via Homebrew)
    find_package(glfw3 3.3 REQUIRED)
endif()



target_include_directories(MyExecutable PRIVATE include)

target_link_libraries(MyExecutable OpenGL::GL glfw)