#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include "Shader.h"
#include "Object.h"
#include <random>
#include "glm/glm.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

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
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
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
    //// Vertex Shader
    //std::ifstream VertShader("Shaders/VertexShader.vert");
    //std::string VertContents((std::istreambuf_iterator<char>(VertShader)),
    //    std::istreambuf_iterator<char>());
    //VertShader.close();
    //const char* vertexShaderSource = VertContents.c_str();
    //unsigned int vertexShader;
    //vertexShader = glCreateShader(GL_VERTEX_SHADER);
    //glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    //glCompileShader(vertexShader);
    //{// Check if compilation failed
    //    int  success;
    //    char infoLog[512];
    //    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    //
    //    if (!success)
    //    {
    //        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    //        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    //    }
    //}
    //
    //// Fragment Shader
    //std::ifstream FragShader("Shaders/FragmentShader.frag");
    //std::string FragContents((std::istreambuf_iterator<char>(FragShader)),
    //    std::istreambuf_iterator<char>());
    //FragShader.close();
    ////FragContents.c_str();
    //const char* fragmentShaderSource = FragContents.c_str();
    //unsigned int fragmentShader;
    //fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    //glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    //glCompileShader(fragmentShader);
    //{// Check if compilation failed
    //    int  success;
    //    char infoLog[512];
    //    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    //
    //    if (!success)
    //    {
    //        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    //        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    //    }
    //}
    //
    //// Attach Shaders
    //unsigned int shaderProgram;
    //shaderProgram = glCreateProgram();
    //glAttachShader(shaderProgram, vertexShader);
    //glAttachShader(shaderProgram, fragmentShader);
    //glLinkProgram(shaderProgram);
    //{// Check if linking failed
    //    int  success;
    //    char infoLog[512];
    //    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    //
    //    if (!success)
    //    {
    //        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    //        std::cout << "ERROR::SHADER::LINKING::COMPILATION_FAILED\n" << infoLog << std::endl;
    //    }
    //}


    Object Obj1("assets/teapot.obj");


    std::vector<float> vertices = Obj1.Verticies;
    std::vector<float> vertexNormals = Obj1.VertexNormals;

    std::vector<unsigned int> TriIndices = Obj1.TriangleIndices;

    unsigned int VBO, VAO, EBO, NBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &NBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), &vertices[0], GL_STATIC_DRAW);


    glBindBuffer(GL_ARRAY_BUFFER, NBO);
    glBufferData(GL_ARRAY_BUFFER, vertexNormals.size() * sizeof(vertexNormals[0]), &vertexNormals[0], GL_STATIC_DRAW);



    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, TriIndices.size() * sizeof(TriIndices[0]), &TriIndices[0], GL_STATIC_DRAW);


    // What the vertex array 'looks like'
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, NBO);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

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

    float scale = Obj1.MaxVertexValue;


    int i = 0;
    while (!glfwWindowShouldClose(window))
    {
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

        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawElements(GL_TRIANGLES, TriIndices.size(), GL_UNSIGNED_INT, 0);
        //glDrawArrays(GL_TRIANGLES, 0, vertices.size()/3);

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

        if (frame % 1000 == 0)
        {
            //lightx = ((float)rand() / RAND_MAX) - 0.5f;
            //lighty = ((float)rand() / RAND_MAX) - 0.5f;
            //lightz = ((float)rand() / RAND_MAX) - 0.5f;

        }
        if (frame % 10 == 0)
        {
            //scale += 0.1f;
            //std::cout << scale << std::endl;
        }

        frame += 1;
        glfwSwapBuffers(window);
        glfwPollEvents();

    }


    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}