#include "VertexArray.h"
#include "Shader.h"
#include "glm/glm.hpp"

class Item {
public:
	Item(Shader shader);

	~Item();

	void AddVertexArray(VertexArray Array);
	void Render();
	void SetUniform(std::string Name, float Data);
	void SetUniform(std::string Name, int Data);
	void SetUniform(std::string Name, glm::vec3 Data);
	void SetUniform(std::string Name, glm::mat4 Data);

	void ApplyFur();

private:

	std::vector<VertexArray> m_VertexVector;
	Shader m_Shader;

};


