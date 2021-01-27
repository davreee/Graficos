#version 410

uniform vec3 Ka;
uniform vec3 Ia;

out vec4 fragColor;

vec3 ambient() {
    vec3 ambient = (Ia * Ka);
    return ambient;
}
void main() {
    fragColor = vec4(ambient(), 1.0);
}