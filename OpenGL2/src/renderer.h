#include "VertexArray.h"
#include "Shader.h"


class Renderer {
public:
	Renderer(Shader shader);

	~Renderer();

	void AddVertexArray();
	void Render();

private:

	std::vector<VertexArray> VertexVector;
	Shader m_Shader;

};