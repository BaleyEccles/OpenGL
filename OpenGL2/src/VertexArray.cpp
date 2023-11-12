#include "VertexArray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &VertexArrayObject);
}

VertexArray::~VertexArray()
{
}

void VertexArray::Render()
{
	glBindVertexArray(VertexArrayObject);
	for (int i = 0; i < VertexBuffers.size(); i++)
	{
		glBindBuffer(VertexBuffers[i].ObjectType, VertexBufferObjects[i]);
	}
	glBindBuffer(IndexBuf.ObjectType, IndexBufferObject);
	glDrawElements(GL_TRIANGLES, IndexBuf.Data.size(), IndexBuf.DataType, 0);
}

void VertexArray::AddVertexBuffer(VertexBuffer buffer)
{
	if (buffer.Data.size() != 0)
	{
		glBindVertexArray(VertexArrayObject);
		VertexBuffers.insert(VertexBuffers.begin(), buffer);
		VertexBufferObjects.insert(VertexBufferObjects.begin(), NULL);
		glGenBuffers(1, &VertexBufferObjects[0]);

		glBindBuffer(VertexBuffers[0].ObjectType, VertexBufferObjects[0]);
		glBufferData(VertexBuffers[0].ObjectType, VertexBuffers[0].Data.size() * sizeof(VertexBuffers[0].Data[0]), &VertexBuffers[0].Data[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(VertexBuffers[0].ShaderIndex);

		glBindBuffer(VertexBuffers[0].ObjectType, VertexBufferObjects[0]);
		glVertexAttribPointer(VertexBuffers[0].ShaderIndex, VertexBuffers[0].Stride, VertexBuffers[0].DataType, GL_FALSE, VertexBuffers[0].Stride * sizeof(float), (void*)0);
		glBindBuffer(VertexBuffers[0].ObjectType, 0);
		glBindVertexArray(0);
	}
	else {
		std::cout << "Input Buffer Has Size Zero!!" << std::endl;
	}

}

void VertexArray::UpdateVertexBuffers(bool KeepPrevData)
{
	if (KeepPrevData == true)
	{
		VertexArrayObject = NULL;
		glGenVertexArrays(1, &VertexArrayObject);
	}

	for (int i = 0; i < VertexBuffers.size(); i++)
	{
		glBindVertexArray(VertexArrayObject);
		VertexBufferObjects[i] = NULL;
		glGenBuffers(1, &VertexBufferObjects[i]);

		glBindBuffer(VertexBuffers[i].ObjectType, VertexBufferObjects[i]);
		glBufferData(VertexBuffers[i].ObjectType, VertexBuffers[i].Data.size() * sizeof(VertexBuffers[i].Data[0]), &VertexBuffers[i].Data[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(VertexBuffers[i].ShaderIndex);

		glBindBuffer(VertexBuffers[i].ObjectType, VertexBufferObjects[i]);
		glVertexAttribPointer(VertexBuffers[i].ShaderIndex, VertexBuffers[i].Stride, VertexBuffers[i].DataType, GL_FALSE, VertexBuffers[i].Stride * sizeof(float), (void*)0);
		glBindBuffer(VertexBuffers[i].ObjectType, 0);
		glBindVertexArray(0);
	}
}

void VertexArray::AddIndexBuffer(IndexBuffer buffer)
{
	glBindVertexArray(VertexArrayObject);
	IndexBuf = buffer;
	glGenBuffers(1, &IndexBufferObject);

	glBindBuffer(IndexBuf.ObjectType, IndexBufferObject);
	glBufferData(IndexBuf.ObjectType, IndexBuf.Data.size() * sizeof(IndexBuf.Data[0]), &IndexBuf.Data[0], GL_STATIC_DRAW);
	
	glBindBuffer(IndexBuf.ObjectType, 0);
}