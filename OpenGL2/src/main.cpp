#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include "Shader.h"
#include "Object.h"
#include <random>
#include "glm/glm.hpp"
#include "VertexArray.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void fps(int& nbFrames, double& lastTime, GLFWwindow* Window);

void GLAPIENTRY
MessageCallback(GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei length,
    const GLchar* message,
    const void* userParam)
{
    fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
        (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
        type, severity, message);
}


// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    srand(time(NULL));

    // glfw: initialize and configure
    // ------------------------------

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "0.000000", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(MessageCallback, 0);

    // Wireframe Enable
    glPolygonMode(GL_FRONT, GL_LINE);
    glPolygonMode(GL_BACK, GL_LINE);
    // Wireframe Disable
#if 1
    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_FILL);
#endif

    // Enable depth test
    glEnable(GL_DEPTH_TEST);

    Shader ShaderProgram(
        std::vector<std::string>{"Shaders/VertexShader.vert", "Shaders/FragmentShader.frag"},
        std::vector<GLenum>{GL_VERTEX_SHADER, GL_FRAGMENT_SHADER}
    );


    Object Obj1("assets/teapot.obj");

    std::vector<float> vertices = Obj1.Verticies;
    std::vector<float> vertexNormals = Obj1.VertexNormals;

    std::vector<unsigned int> TriIndices = Obj1.Indices;

    VertexArray Vert;
    VertexBuffer VertexBufferObject = {
        GL_ARRAY_BUFFER,
        0,
        Obj1.Verticies,
        3,
        GL_FLOAT
    };
    VertexBuffer NormalBufferObject = {
        GL_ARRAY_BUFFER,
        1,
        Obj1.VertexNormals,
        3,
        GL_FLOAT
    };
    IndexBuffer IndexBufferObject = {
        GL_ELEMENT_ARRAY_BUFFER,
        Obj1.Indices,
        GL_UNSIGNED_INT
    };

    Vert.AddVertexBuffer(VertexBufferObject);
    Vert.AddVertexBuffer(NormalBufferObject);
    Vert.AddIndexBuffer(IndexBufferObject);

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);

    float alpha = 0.0f;
    float beta = 0.0f;
    float gamma = 0.0f;
    float alphaSpeed = 0.0f;
    float betaSpeed = 0.0f;
    float gammaSpeed = 0.0f;


    glm::vec3 light = {
        ((float)rand() / RAND_MAX) - 0.5f,
        ((float)rand() / RAND_MAX) - 0.5f,
        ((float)rand() / RAND_MAX) - 0.5f
    };
    unsigned int frame = 0;
    int nbFrames = 0;
    double lastTime = glfwGetTime();
    float scale = Obj1.MaxVertexValue;


    int i = 0;
    while (!glfwWindowShouldClose(window))
    {
        fps(nbFrames, lastTime, window);
        // input
         // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ShaderProgram.UseShader();
        ShaderProgram.SetUniform1f("alpha", alpha);
        ShaderProgram.SetUniform1f("beta", beta);
        ShaderProgram.SetUniform1f("gamma", gamma);
        ShaderProgram.SetUniform3f("Light", light.x, light.y, light.z);
        ShaderProgram.SetUniform1f("Scale", scale);

        Vert.Render();

        if (frame % 10000 == 0)
        {
            alphaSpeed = ((float)rand() / RAND_MAX) - 0.5f;
            betaSpeed = ((float)rand() / RAND_MAX) - 0.5f;
            gammaSpeed = ((float)rand() / RAND_MAX) - 0.5f;

        }
        else {
            alpha += 0.001f * alphaSpeed;
            beta += 0.001f * betaSpeed;
            gamma += 0.001f * gammaSpeed;
        }

        frame += 1;
        glfwSwapBuffers(window);
        glfwPollEvents();

    }


    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void fps(int &nbFrames, double &lastTime, GLFWwindow* Window)
{
    double currentTime = glfwGetTime();
    nbFrames++;
    if (currentTime - lastTime >= 1.0) { // If last prinf() was more than 1 sec ago
        // printf and reset timer
        glfwSetWindowTitle(Window, std::to_string(double(nbFrames)).c_str());
        nbFrames = 0;
        lastTime += 1.0;

    }
}