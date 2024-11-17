#version 410 core
out vec4 FragColor;
in vec3 rectColor;
void main() {
    FragColor = vec4(rectColor, 1.0);
}