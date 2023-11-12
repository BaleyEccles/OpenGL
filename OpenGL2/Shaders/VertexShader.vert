#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormals;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform vec3 Light;

out vec4 Pos;
out vec4 Normal;

out vec3 outLight;

void main()
{
#if 1
    Pos = projection * view * model * vec4(aPos, 1.0f);
    Normal = projection * view * model * vec4(aNormals, 1.0f);
#else
    Pos = aPos;
    Normal = aNormals;
#endif
    outLight = vec3(Light.x, Light.y, Light.z);
    gl_Position = Pos;
}