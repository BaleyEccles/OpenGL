#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormals;

uniform float alpha;
uniform float beta;
uniform float gamma;

uniform vec3 Light;

uniform float Scale;


out vec3 Pos;
out vec3 Normal;

out vec3 outLight;

void main()
{
    mat3 yaw = mat3( 
    cos(alpha),     sin(alpha),     0,
    -sin(alpha),    cos(alpha),     0,
    0,              0,              1
    );
    mat3 pitch = mat3( 
    cos(beta),     0,              sin(beta),
    0,              1,              0,
    -sin(beta),    0,              cos(beta)
    );
    mat3 roll = mat3( 
    1, 0, 0,
    0, cos(gamma), sin(gamma),
    0, -sin(gamma),cos(gamma)
    );
    Pos = (yaw*pitch*roll*aPos)/Scale;

    outLight = yaw*pitch*roll*vec3(Light.x,Light.y,Light.z);


    Normal = aNormals;

    gl_Position = vec4(Pos.x, Pos.y, Pos.z , 1.0);
}