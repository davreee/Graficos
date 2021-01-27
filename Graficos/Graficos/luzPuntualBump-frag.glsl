#version 410

uniform vec3 Ks;
uniform vec3 Id;
uniform vec3 Is;

uniform float shininess;
uniform sampler2D TexSamplerColor; 
uniform sampler2D TexSamplerBump;

in vec3 position;
in vec3 lDir;
in vec3 vDir;
in vec2 texCoord; 

out vec4 fragColor;

vec3 diffuseAndSpecular(vec4 texColor, vec4 normal) {
    vec3 Kad = texColor.rgb; 
    vec3 n = normal.rgb;
    n = normalize(n);
    vec3 l = normalize( lDir );
    vec3 v = normalize( vDir);
    vec3 r = reflect( -l, n );

    vec3 diffuse = (Id * Kad * max( dot(l,n), 0.0));
    vec3 specular;

    specular = (Is * Ks * pow( max( dot(r,v), 0.0), shininess));

    return diffuse+specular;
} 

void main() {
    vec4 texColor = texture(TexSamplerColor, texCoord);
    vec4 normal = (2.0 * texture(TexSamplerBump, texCoord)) - 1.0;
    fragColor = vec4(diffuseAndSpecular(texColor, normal), 1.0);
}