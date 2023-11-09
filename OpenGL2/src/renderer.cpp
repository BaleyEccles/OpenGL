#include "renderer.h"

Renderer::Renderer(Shader shader)
	:m_Shader(shader)
{
}

Renderer::~Renderer()
{
}

void Renderer::AddVertexArray(VertexArray Array)
{
	m_VertexVector.push_back(Array);
}

void Renderer::Render()
{
	m_Shader.UseShader();
	for (int i = 0; i < m_VertexVector.size(); i++)
	{
		m_VertexVector[i].Render();
	}
}

void Renderer::SetUniform(std::string Name, float Data)
{
	m_Shader.UseShader();
	m_Shader.SetUniform1f(Name, Data);
}

void Renderer::SetUniform(std::string Name, int Data)
{
	m_Shader.UseShader();
	m_Shader.SetUniform1i(Name, Data);
}

void Renderer::SetUniform(std::string Name, glm::vec3 Data)
{
	m_Shader.UseShader();
	m_Shader.SetUniform3f(Name, Data.x, Data.y, Data.z);
}