#version 330 core

in vec3 Pos;
in vec3 Normal;
in vec3 outLight;

out vec4 FragColor;

void main()
{
    float cosTheta = clamp( dot(Normal,outLight), 0,1);

#if 0
    FragColor = vec4(0.5*(1.0-Normal),1.0f);
#else
    FragColor = vec4(cosTheta*vec3(0.0f,1.0f,1.0f),1.0f);
#endif
} 