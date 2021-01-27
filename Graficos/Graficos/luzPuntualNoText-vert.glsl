#version 410
layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vNormal;

uniform mat4 mPV;
uniform mat4 mView;
uniform mat4 mModel;

uniform float pointSize; 

out vec3 position;
out vec3 normal; 

void main ()
{    
    gl_PointSize= pointSize;
    normal = vec3( transpose(inverse(mView * mModel)) * vec4(vNormal, 0.0) );
    position = vec3( mView * mModel * vec4(vPosition, 1.0) ); 
    gl_Position = mPV * mModel * vec4(vPosition, 1.0); 
}