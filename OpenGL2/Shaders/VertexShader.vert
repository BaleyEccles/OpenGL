#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormals;
layout (location = 2) in vec2 aTexture;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
flat uniform int frame;

uniform vec3 Light;

out vec4 Pos;
out vec4 Normal;
out vec2 Texture;
flat out int Frame;

out vec3 outLight;

void main()
{
    Frame = frame;
#if 1
    Pos = projection * view * model * vec4(aPos, 1.0f);
    Normal = projection * view * model * vec4(aNormals, 1.0f);
    Texture = aTexture;
#else
    Pos = aPos;
    Normal = aNormals;
    Texture = aTexture;
#endif
    outLight = vec3(Light.x, Light.y, Light.z);
    gl_Position = Pos;
}