#version 330 core

in vec4 Pos;
in vec4 Normal;
in vec3 outLight;

out vec4 FragColor;

void main()
{
    float cosTheta = clamp( dot(Normal,vec4(outLight,1.0)), 0,1);
#if 0
    FragColor = Normal;
#else
    FragColor = vec4(cosTheta*vec3(0.0f,1.0f,1.0f),1.0f);
#endif
} 