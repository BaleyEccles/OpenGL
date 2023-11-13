#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include "glm/glm.hpp"

class Object
{
public:
	Object(std::string FilePath);
	~Object();

	std::vector<float> Verticies;	
	std::vector<float> VertexNormals;
	std::vector<float> VertexTexture;
	std::vector<unsigned int> Indices;

	int VertexSize;
	int IndexSize;
	float MaxVertexValue = 0.0f;
	float maxX = 0.0f;
	float minX = 0.0f;
	float maxY = 0.0f;
	float minY = 0.0f;
	float maxZ = 0.0f;
	float minZ = 0.0f;
private:
	void FormatFile(std::string FilePath);
	void CreateVerticies(std::string FilePath);
	void CreateVertexNormals(std::string FilePath);
	void CreateVertexTextureCoords(std::string FilePath);
	void CreateIndicies(std::string FilePath);
	void QuadToTri(std::vector<unsigned int> QuadIndices);
	void GenerateVertexNormalsFromVerticies();
};

