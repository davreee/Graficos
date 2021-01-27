#version 410

uniform vec3 Kd;
uniform vec3 Ks;
uniform vec3 Id;
uniform vec3 Is;

uniform float shininess;
uniform vec3 lightPosition; 

in vec3 normal;
in vec3 position;

out vec4 fragColor;

vec3 diffuseAndSpecular() {
    vec3 n = normalize( normal );

    vec3 l = normalize( lightPosition-position );
    vec3 v = normalize( -position );
    vec3 r = reflect( -l, n );

    vec3 diffuse = (Id * Kd * max( dot(l,n), 0.0));
    vec3 specular;

    specular = (Is * Ks * pow( max( dot(r,v), 0.0), shininess));

    return diffuse+specular;
} 

void main() {
    fragColor = vec4(diffuseAndSpecular(), 1.0);
}