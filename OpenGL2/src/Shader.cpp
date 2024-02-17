#include "Shader.h"

Shader::Shader(std::vector<std::string> Path, std::vector<GLenum> Type)
	:FilePath(Path), ShaderType(Type)
{
	CompileShaders();
	AttachShaders();
}

Shader::~Shader()
{
}

void Shader::UseShader()
{
    glUseProgram(ShaderProgram);
}



void Shader::CompileShaders()
{
  for (int i = 0; i < FilePath.size(); i++)
    {
      std::ifstream File;
      File.open(FilePath[i]);
      std::string Contents((std::istreambuf_iterator<char>(File)), std::istreambuf_iterator<char>());
   
      File.close();
      const char* Source = Contents.c_str();
      Shaders.push_back(glCreateShader(ShaderType[i]));
      glShaderSource(Shaders[i], 1, &Source, NULL);
      glCompileShader(Shaders[i]);

      {// Check if compilation failed
	int  success;
	char infoLog[512];
	glGetShaderiv(Shaders[i], GL_COMPILE_STATUS, &success);
	    
	if (!success)
	  {
	    glGetShaderInfoLog(Shaders[i], 512, NULL, infoLog);
	    std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << "PATH: " << FilePath[i] << "\n" << infoLog << std::endl;
	  }
      }
    }
}

void Shader::AttachShaders()
{
    ShaderProgram = glCreateProgram();
    for (int i = 0; i < Shaders.size(); i++)
    {
        glAttachShader(ShaderProgram, Shaders[i]);
    }
    glLinkProgram(ShaderProgram);
    {// Check if linking failed
        int  success;
        char infoLog[512];
        glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &success);

        if (!success)
        {
            glGetProgramInfoLog(ShaderProgram, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::LINKING::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
    }
}
