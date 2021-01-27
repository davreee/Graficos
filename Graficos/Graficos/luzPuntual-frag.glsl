#version 410

uniform vec3 Ks;
uniform vec3 Id;
uniform vec3 Is;

uniform float shininess;
uniform vec3 lightPosition; 
uniform sampler2D TexSamplerColor; 

in vec2 texCoord; 
in vec3 normal;
in vec3 position;

out vec4 fragColor;

vec3 diffuseAndSpecular(vec4 texColor) {
    vec3 Kad = texColor.rgb; 
    vec3 n = normalize( normal );

    vec3 l = normalize( lightPosition-position );
    vec3 v = normalize( -position );
    vec3 r = reflect( -l, n );

    vec3 diffuse = (Id * Kad * max( dot(l,n), 0.0));
    vec3 specular;

    specular = (Is * Ks * pow( max( dot(r,v), 0.0), shininess));

    return diffuse+specular;
} 

void main() {
    vec4 texColor = texture(TexSamplerColor, texCoord);
    fragColor = vec4(diffuseAndSpecular(texColor), 1.0);
}