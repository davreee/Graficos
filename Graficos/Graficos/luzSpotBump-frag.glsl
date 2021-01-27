#version 410
#define M_PI 3.1415926535897932384626433832795

uniform vec3 Ks;
uniform vec3 Id;
uniform vec3 Is;

uniform float shininess;
uniform float spotAngle;
uniform sampler2D TexSamplerColor; 
uniform sampler2D TexSamplerBump;

in vec3 position;
in vec2 texCoord; 
in vec3 lDir;
in vec3 vDir;
in vec3 dDir;

out vec4 fragColor;

vec3 diffuseAndEspecular(vec4 texColor, vec4 normal){
    vec3 Kad = texColor.rgb; 
    vec3 n = normal.rgb;
    n = normalize(n);
    vec3 l = normalize( lDir );
    vec3 d = normalize(dDir);
    float cosGamma = cos(spotAngle * 180.0 / M_PI);
    float spotFactor = 1.0;
    if (cos(dot(-l, d)) < cosGamma) { spotFactor = 0.0; }
    
    vec3 v = normalize( vDir );
    vec3 r = reflect( -l, n );

    vec3 diffuse = (Id * Kad * max( dot(l,n), 0.0));
    vec3 specular = (Is * Ks * pow( max( dot(r,v), 0.0), shininess));

    return spotFactor * (diffuse + specular);
}

void main() {
    vec4 texColor = texture(TexSamplerColor, texCoord);
    vec4 normal = (2.0 * texture(TexSamplerBump, texCoord)) - 1.0;
    fragColor = vec4(diffuseAndEspecular(texColor, normal), 1.0);
}