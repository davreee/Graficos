#version 410

uniform vec3 Ia;
uniform vec3 Ka;
uniform sampler2D TexSamplerColor; 

in vec2 texCoord; 
out vec4 fragColor;


vec3 ambient(vec4 texColor) {
    vec3 Kad = texColor.rgb;
    vec3 ambient = (Ia * Kad);
    return ambient;
}

void main() {
    vec4 texColor = texture(TexSamplerColor, texCoord);
    fragColor = vec4(ambient(texColor), 1.0);
}