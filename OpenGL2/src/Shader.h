#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class Shader {
public:
	Shader(std::vector<std::string> Path, std::vector<GLenum> Type);
	~Shader();

	void UseShader();

	inline GLint GetUniformLocation(const std::string name) { return glGetUniformLocation(ShaderProgram, name.c_str());};
	inline void SetUniform1i(const std::string name, int value)									{ glUniform1i(GetUniformLocation(name), value); };
	inline void SetUniform2i(const std::string name, int value1, int value2)					{ glUniform2i(GetUniformLocation(name), value1, value2); };
	inline void SetUniform1f(const std::string name, float value)								{ glUniform1f(GetUniformLocation(name), value); };
	inline void SetUniform2f(const std::string name, float value, float value2)					{ glUniform2f(GetUniformLocation(name), value, value2); };
	inline void SetUniform4f(const std::string name, float f0, float f1, float f2, float f3)	{ glUniform4f(GetUniformLocation(name), f0, f1, f2, f3); };
	inline void SetUniform3f(const std::string name, float f0, float f1, float f2)				{ glUniform3f(GetUniformLocation(name), f0, f1, f2); };
	inline void SetUniformM4(const std::string name, glm::mat4 mat)								{ glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &mat[0][0]); };


private:
	std::vector<unsigned int> Shaders;
	std::vector<std::string> FilePath;
	std::vector<GLenum> ShaderType;
	unsigned int ShaderProgram;

	void CompileShaders();
	void AttachShaders();

};
