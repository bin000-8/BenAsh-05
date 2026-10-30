#version 330 core

in vec2 oTexture;

out vec4 final_texture;

uniform sampler2D uTex0;

void main() {
    final_texture = texture(uTex0, oTexture);
}