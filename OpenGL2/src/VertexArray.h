#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <any>

struct VertexBuffer
{    
    GLenum ObjectType;
    unsigned int ShaderIndex;
    std::vector<float> Data;
    unsigned int Stride;
    GLenum DataType;
};

struct IndexBuffer
{
    GLenum ObjectType;
    std::vector<unsigned int> Data;
    GLenum DataType;
};

class VertexArray {
public:
    VertexArray();
    ~VertexArray();

    void AddVertexBuffer(VertexBuffer buffer);
    void UpdateVertexBuffers(bool KeepPrevData = false);

    void AddIndexBuffer(IndexBuffer buffer);

    void Render();

    std::vector<VertexBuffer> VertexBuffers;
private:
    unsigned int VertexArrayObject;
    unsigned int IndexBufferObject;
    std::vector<unsigned int> VertexBufferObjects;
    IndexBuffer IndexBuf;
};
