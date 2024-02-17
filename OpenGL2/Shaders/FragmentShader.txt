#version 330 core

in vec4 Pos;
in vec4 Normal;
in vec2 Texture;
flat in int Frame;

in vec3 outLight;

out vec4 FragColor;


const uint k = 1103515245U;
vec3 hash(uvec3 x)
{
    x = ((x>>8U)^x.yzx)*k;
    x = ((x>>8U)^x.yzx)*k;
    x = ((x>>8U)^x.yzx)*k;
    
    return vec3(x)*(1.0/float(0xffffffffU));
}

void main()
{
    float cosTheta = clamp( dot(Normal,vec4(outLight,1.0)), 0,1);
#if 0
    FragColor = Normal;
#else
    FragColor = vec4(cosTheta*vec3(0.0f,1.0f,1.0f),1.0f);
#endif
    uvec3 p = uvec3(100.0f*Texture.x,100.0f*Texture.y,1.0f);
    //FragColor = vec4(Texture.x,Texture.y,0.0f,1.0f);
    vec3 rand = hash(p);
    if(rand.x > 0.1f){
        FragColor = vec4(0.5f, 0.99f, 0.0f, 1.0f);
    }
    else {
            FragColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);

    }
} 