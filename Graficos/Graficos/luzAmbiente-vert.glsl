#version 410
layout(location = 0) in vec3 posicion;
layout (location = 2) in vec2 vTexCoord; 

uniform mat4 mM;
uniform mat4 mPV;
uniform float pointSize; 

out vec2 texCoord; 

void main ()
{    
    gl_PointSize= pointSize;
    texCoord = vTexCoord;
    gl_Position = mPV *mM *vec4 (posicion.x, posicion.y, posicion.z, 1);
}