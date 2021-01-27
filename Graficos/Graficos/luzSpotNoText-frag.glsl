#version 410
#define M_PI 3.1415926535897932384626433832795

uniform vec3 Kd;
uniform vec3 Ks;
uniform vec3 Id;
uniform vec3 Is;

uniform float shininess;
uniform vec3 lightPosition; 
uniform vec3 lightDirection;
uniform float spotAngle;

in vec3 normal;
in vec3 position;

out vec4 fragColor;

vec3 diffuseAndEspecular(){
    vec3 l = normalize( lightPosition-position );
    vec3 d = normalize(lightDirection);
    float cosGamma = cos(spotAngle * 180.0 / M_PI);
    float spotFactor = 1.0;
    if (cos(dot(-l, d)) < cosGamma) { spotFactor = 0.0; }
    vec3 n = normalize( normal );
    vec3 v = normalize( -position );
    vec3 r = reflect( -l, n );

    vec3 diffuse = (Id * Kd * max( dot(l,n), 0.0));
    vec3 specular = (Is * Ks * pow( max( dot(r,v), 0.0), shininess));

    return spotFactor * (diffuse + specular);
}

void main() {
    fragColor = vec4(diffuseAndEspecular(), 1.0);
}