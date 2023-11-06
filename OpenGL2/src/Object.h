#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

class Object
{
public:
	Object(std::string FilePath);
	~Object();

	std::vector<float> Verticies;	
	std::vector<float> VertexNormals;
	std::vector<unsigned int> TriangleIndices;

	int VertexSize;
	int IndexSize;

	float MaxVertexValue;

private:
	void FormatFile(std::string FilePath);
	void CreateVerticies(std::string FilePath);
	void CreateVertexNormals(std::string FilePath);
	void CreateIndicies(std::string FilePath);
	void QuadToTri(std::vector<unsigned int> QuadIndices);

};
