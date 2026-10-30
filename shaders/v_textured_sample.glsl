#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texture;

struct Material {
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

uniform mat4 uModel_matrix;
uniform mat4 uView_matrix;
uniform mat4 uProjection_matrix;
uniform vec3 uColor;
uniform vec3 uLight_color;
uniform vec3 uLight_position;
uniform vec3 uView_position;
uniform Material uMaterial;

out vec2 oTexture;
out vec3 oNormal;
out vec3 oFragment_position;

void main() {
    oTexture = texture;
    oNormal = normal;
    oFragment_position = vec3(uModel_matrix * vec4(position, 1.0));
    gl_Position = uProjection_matrix * uView_matrix * uModel_matrix * vec4(position, 1.0);
} 