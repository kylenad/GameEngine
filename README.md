# GameEngine
Game engine made in C++ supporting 2D & 3D graphics.

## Currently Working On:
- Graphics implementation

## Includes:
- OpenGl (Version 4.1)
- GLFW
- Glad

## Compile Instructions:
Clone project and build using the CMake file. Run the generated executable file in the build folder.
- NOTE: Current CMake build compatible with arm64 architecture; update for x64
### GLFW(MACOS)
- Install GLFW through homebrew
```
brew install glfw
```
### GLFW(WINDOWSx64)
- Install vcpkg
```
git clone https://github.com/microsoft/vcpkg.git
```
- In local vcpkg directory, run the following commands to install vcpkg, and then glfw
```
.\bootstrap-vcpkg.bat
.\vcpkg install glfw3
```
- Update path in cmake file to include path to glwf install
```python
find_package(glfw3 REQUIRED PATHS C:/path/to/vcpkg/installed/x64-windows/share/glfw3 NO_DEFAULT_PATH)
```
- Find glfw3.dll file in vcpkg directory and copy it into the the project build directory where the .exe file is located
- .exe file should now function properly


## Resources:
- https://learnopengl.com/Introduction 


