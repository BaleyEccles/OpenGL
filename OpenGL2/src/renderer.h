#include "VertexArray.h"
#include "Shader.h"
#include "glm/glm.hpp"

class Renderer {
public:
	Renderer(Shader shader);

	~Renderer();

	void AddVertexArray(VertexArray Array);
	void Render();
	void SetUniform(std::string Name, float Data);
	void SetUniform(std::string Name, int Data);
	void SetUniform(std::string Name, glm::vec3 Data);

private:

	std::vector<VertexArray> m_VertexVector;
	Shader m_Shader;

};


