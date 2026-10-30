#version 330 core

in vec3 oRgb;

out vec4 color;

void main() {
    color = vec4(oRgb, 1.0);
}