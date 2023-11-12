#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "Shader.h"
#include "Object.h"
#include <random>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "VertexArray.h"
#include "item.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void fps(int& nbFrames, double& lastTime, GLFWwindow* Window);
void limitfps(double& startime, double& endtime);

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
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, " ", NULL, NULL);
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
    Object Obj2("assets/triangle.obj");


    VertexArray Vert1;
    {
        {
            VertexBuffer VertexBufferObject1 = {
                GL_ARRAY_BUFFER,
                0,
                Obj1.Verticies,
                3,
                GL_FLOAT
            };
            VertexBuffer NormalBufferObject1 = {
                GL_ARRAY_BUFFER,
                1,
                Obj1.VertexNormals,
                3,
                GL_FLOAT
            };
            IndexBuffer IndexBufferObject1 = {
                GL_ELEMENT_ARRAY_BUFFER,
                Obj1.Indices,
                GL_UNSIGNED_INT
            };
            Vert1.AddVertexBuffer(VertexBufferObject1);
            Vert1.AddVertexBuffer(NormalBufferObject1);
            Vert1.AddIndexBuffer(IndexBufferObject1);
        }
    }
    VertexArray Vert2;
    {
        {
            VertexBuffer VertexBufferObject = {
                GL_ARRAY_BUFFER,
                0,
                Obj2.Verticies,
                3,
                GL_FLOAT
            };
            VertexBuffer NormalBufferObject = {
                GL_ARRAY_BUFFER,
                1,
                Obj2.VertexNormals,
                3,
                GL_FLOAT
            };
            IndexBuffer IndexBufferObject = {
                GL_ELEMENT_ARRAY_BUFFER,
                Obj2.Indices,
                GL_UNSIGNED_INT
            };
            Vert2.AddVertexBuffer(VertexBufferObject);
            Vert2.AddVertexBuffer(NormalBufferObject);
            Vert2.AddIndexBuffer(IndexBufferObject);
        }
    }
    Item Teapot(ShaderProgram);
    Teapot.AddVertexArray(Vert2);
    Teapot.ApplyFur();
    Teapot.AddVertexArray(Vert1);

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);



    glm::vec3 light = {
        +1.0f,                //((float)rand() / RAND_MAX) - 0.5f,
        +1.0f,                //((float)rand() / RAND_MAX) - 0.5f,
        -1.0f                 //((float)rand() / RAND_MAX) - 0.5f
    };
    light = glm::normalize(light);
    unsigned int frame = 0;
    float scale = Obj1.MaxVertexValue;

    double startime = 0.0;
    double endtime = 0.0;

    float Constant = 0.01f;
    glm::vec3 location = glm::vec3(0.0f,0.0f,0.0f);


    while (!glfwWindowShouldClose(window))
    {
        // input
        startime = glfwGetTime();
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(90.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 150.0f);
        view = glm::translate(view, location);
        Teapot.SetUniform("projection", projection); // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
        Teapot.SetUniform("view", view);

        glm::mat4 model = glm::mat4(1.0f);
        float angle = 20.0f;
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        Teapot.SetUniform("model", model);
        Teapot.SetUniform("Light", light);

        Teapot.Render();

        
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            std::cout << location.z << std::endl;
            location.z += Constant;
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            location.z -= Constant;
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            location.x -= Constant;
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            location.x += Constant;
        }


        frame += 1;
        glfwSwapBuffers(window);
        glfwPollEvents();

        endtime = glfwGetTime();
        limitfps(startime, endtime);
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

void limitfps(double &startime, double &endtime)
{
    Sleep((1000.0 / 120.0) - (startime - endtime));
}
