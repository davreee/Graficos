#version 410
layout(location = 0) in vec3 posicion;

uniform mat4 mM;
uniform mat4 mPV;
uniform float pointSize; 

void main ()
{    
    gl_PointSize= pointSize;
    gl_Position = mPV * mM * vec4 (posicion.x, posicion.y, posicion.z, 1);
}