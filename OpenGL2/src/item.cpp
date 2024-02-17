#include "item.h"



Item::Item(Shader shader)
	:m_Shader(shader)
{
}

Item::~Item()
{
}

void Item::AddVertexArray(VertexArray Array)
{
	m_VertexVector.push_back(Array);
}

void Item::Render()
{
	m_Shader.UseShader();
	for (int i = 0; i < m_VertexVector.size(); i++)
	{
		m_VertexVector[i].Render();
	}
}

void Item::SetUniform(std::string Name, float Data)
{
	m_Shader.UseShader();
	m_Shader.SetUniform1f(Name, Data);
}

void Item::SetUniform(std::string Name, int Data)
{
	m_Shader.UseShader();
	m_Shader.SetUniform1i(Name, Data);
}

void Item::SetUniform(std::string Name, glm::vec3 Data)
{
	m_Shader.UseShader();
	m_Shader.SetUniform3f(Name, Data.x, Data.y, Data.z);
}

void Item::SetUniform(std::string Name, glm::mat4 Data)
{
	m_Shader.UseShader();
	m_Shader.SetUniformM4(Name, Data);
}

void Item::ApplyFur()
{
	std::vector<VertexArray> TempFurVec;
	int Size = m_VertexVector.size();
	for (int k = 0; k < Size; k++)
	{
		for (int i = 0; i < 100; i++)
		{
			VertexArray ArrayL1 = m_VertexVector[k];
			for (int j = 0; j < ArrayL1.VertexBuffers[0].Data.size() / 3; j++)
			{
				ArrayL1.VertexBuffers[2].Data[3 * j + 0] += i * 0.001f * ArrayL1.VertexBuffers[1].Data[3 * j + 0];
				ArrayL1.VertexBuffers[2].Data[3 * j + 1] += i * 0.001f * ArrayL1.VertexBuffers[1].Data[3 * j + 1];
				ArrayL1.VertexBuffers[2].Data[3 * j + 2] += i * 0.001f * ArrayL1.VertexBuffers[1].Data[3 * j + 2];
				//                    ^  Dependent on the posof the vertex (text,normal,vert)  ^   
			}
			ArrayL1.UpdateVertexBuffers(true);
			TempFurVec.push_back(ArrayL1);
		}
	}
	for (int i = 0; i < TempFurVec.size(); i++)
	{
		m_VertexVector.push_back(TempFurVec[i]);
	}
}
