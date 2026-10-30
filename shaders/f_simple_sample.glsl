#version 330 core

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

uniform vec3 uColor;
uniform vec3 uLight_color;
uniform vec3 uLight_position;
uniform vec3 uView_position;
uniform Material uMaterial;

in vec3 oRgb;
in vec3 oNormal;
in vec3 oFragment_position;

out vec4 color;

void main() {
    // Ambient
    vec3 ambient = uMaterial.ambient * uLight_color;

    // Diffuse
    vec3 normal = normalize(oNormal);
    vec3 light_direction = normalize(uLight_position - oFragment_position);
    float prediffuse = max(dot(normal, light_direction), 0.0); // max returns the larger of 2 values
    vec3 diffuse = prediffuse * uMaterial.diffuse * uLight_color;

    // Specular
    vec3 view_direction = normalize(uView_position - oFragment_position);
    vec3 reflect_direction = reflect(-light_direction, normal);
    float prespecular = pow(max(dot(view_direction, reflect_direction), 0.0), uMaterial.shininess);
    vec3 specular = prespecular * uMaterial.specular * uLight_color;

    vec3 result = (ambient + diffuse + specular) * uColor;
    color = vec4(result, 1.0);
}