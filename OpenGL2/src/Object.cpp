#include "Object.h"

Object::Object(std::string FilePath)
{

  CreateVerticies(FilePath);

  CreateIndicies(FilePath);

  CreateVertexNormals(FilePath);

  CreateVertexTextureCoords(FilePath);


}

Object::~Object()
{

}

void Object::FormatFile(std::string FilePath)
{
  std::fstream Obj(FilePath);
  Obj.open("FileName.txt", std::ios::in);
  if (!Obj) {
    std::cout << "File doesn’t exist.";
  }
  else {
    std::vector<char> TempFile;
    char x;
    while (1) {
      Obj >> x;
      TempFile.push_back(x);
      if (Obj.eof()) {
	break;
      }
      Obj << x;
    }
    for (int i = 0; i < TempFile.size(); i++)
      {
	if (TempFile[i] == ' ' && TempFile[i + 1] == ' ')
	  {
	    //
	  }
      }
  }
  Obj.close();

}


void Object::CreateVerticies(std::string FilePath)
{
  // Seg faults here i cannot be bothered at the moment. Have a nice day tomorrow baley <3
  std::ifstream Obj(FilePath);
  for (std::string line; std::getline(Obj, line); )
    {
      //std::cout << line << std::endl;
      if (line[0] == 'v' && line[1] == ' ')
	{//v  40.6266  28.3457  -1.10804
	  std ::vector<int> start;
	  std::vector<int> end;
	  for (int i = 0; i < line.size(); i++)
	    {
	      if (line[i] == ' ' && line[i + 1] != ' ')
		{
		  start.push_back(i + 1);
		}
	      if (line[i] == ' ' && line[i - 1] != ' ')
		{
		  end.push_back(i);
		}
	    }
	  end.erase(end.begin());
	  end.push_back(line.size());

	  for (int i = 0; i < start.size(); i++)
	    {
	      std::string Vert;
	      for (int k = 0; k < end[i] - start[i]; k++)
		{
		  Vert.push_back(line[start[i] + k]);
		}
	      Verticies.push_back(std::stof(Vert));
	    }
	}
    }
  float TempMax = *max_element(Verticies.begin(), Verticies.end());
  float TempMin = *min_element(Verticies.begin(), Verticies.end());

  MaxVertexValue = abs(TempMax) > abs(TempMin) ? TempMax : abs(TempMin);

  float maxx = 0.0f;
  float minx = 0.0f;
  float maxy = 0.0f;
  float miny = 0.0f;
  float maxz = 0.0f;
  float minz = 0.0f;
  for (int i = 0; i < Verticies.size() / 3; i++)
    {
      if (maxx < Verticies[(3 * i) + 0]) { maxx = Verticies[(3 * i) + 0]; }
      if (minx > Verticies[(3 * i) + 0]) { minx = Verticies[(3 * i) + 0]; }

      if (maxy < Verticies[(3 * i) + 1]) { maxy = Verticies[(3 * i) + 1]; }
      if (miny > Verticies[(3 * i) + 1]) { miny = Verticies[(3 * i) + 1]; }

      if (maxz < Verticies[(3 * i) + 2]) { maxz = Verticies[(3 * i) + 2]; }
      if (minz > Verticies[(3 * i) + 2]) { minz = Verticies[(3 * i) + 2]; }

    }
  for (int i = 0; i < Verticies.size(); i++)
    {
      Verticies[i] = Verticies[i] / MaxVertexValue;
    }
  //VertexSize = Verticies.size();
  Obj.close();
}


void Object::CreateVertexNormals(std::string FilePath)
{

  std::ifstream Obj(FilePath);
  for (std::string line; std::getline(Obj, line); )
    {
      //std::cout << line << std::endl;
      if (line[0] == 'v' && line[1] == 'n')
	{//v  40.6266  28.3457  -1.10804
	  std::vector<int> start;
	  std::vector<int> end;
	  for (int i = 0; i < line.size(); i++)
	    {
	      if (line[i] == ' ' && line[i + 1] != ' ')
		{
		  start.push_back(i + 1);
		}
	      if (line[i] == ' ' && line[i - 1] != ' ')
		{
		  end.push_back(i);
		}
	    }
	  end.erase(end.begin());
	  end.push_back(line.size());

	  for (int i = 0; i < start.size(); i++)
	    {
	      std::string Vert;
	      for (int k = 0; k < end[i] - start[i]; k++)
		{
		  Vert.push_back(line[start[i] + k]);
		}
	      VertexNormals.push_back(std::stof(Vert));
	    }
	}
    }
  Obj.close();

  if (VertexNormals.size() == 0)
    {// There is a problem here I think it has to do with quads, as the models with only triagles work well (try sphere with and without creating normals)
      GenerateVertexNormalsFromVerticies(); 
    }

  // Normalizes the vectors
  for (int i = 0; i < VertexNormals.size() / 3; i++)
    {
      glm::vec3 Vec{ VertexNormals[3 * i + 0], VertexNormals[3 * i + 1], VertexNormals[3 * i + 2] };
      glm::vec3 Norm = glm::normalize(Vec);
      VertexNormals[3 * i + 0] = Norm.x;
      VertexNormals[3 * i + 1] = Norm.y;
      VertexNormals[3 * i + 2] = Norm.z;
    }
}



void Object::GenerateVertexNormalsFromVerticies()
{
  for (int i = 0; i < Verticies.size(); i++)
    {
      VertexNormals.push_back(0.0f);
    }
  for (int i = 0; i < Indices.size()/3; i++)// This is wrong IDK how, it is supposed to generate the normals for each face.
    {
      glm::vec3 A{ Verticies[3 * Indices[3 * i + 0] + 0], Verticies[3 * Indices[3 * i + 0] + 1], Verticies[3 * Indices[3 * i + 0] + 2] };
      glm::vec3 B{ Verticies[3 * Indices[3 * i + 1] + 0], Verticies[3 * Indices[3 * i + 1] + 1], Verticies[3 * Indices[3 * i + 1] + 2] };
      glm::vec3 C{ Verticies[3 * Indices[3 * i + 2] + 0], Verticies[3 * Indices[3 * i + 2] + 1], Verticies[3 * Indices[3 * i + 2] + 2] };
      glm::vec3 D = cross(B - A, C - A);

      VertexNormals[3 * Indices[3 * i + 0] + 0] -= D.x;
      VertexNormals[3 * Indices[3 * i + 0] + 1] -= D.y;
      VertexNormals[3 * Indices[3 * i + 0] + 2] -= D.z;
					    						  
      VertexNormals[3 * Indices[3 * i + 1] + 0] -= D.x;
      VertexNormals[3 * Indices[3 * i + 1] + 1] -= D.y;
      VertexNormals[3 * Indices[3 * i + 1] + 2] -= D.z;
					    						  
      VertexNormals[3 * Indices[3 * i + 2] + 0] -= D.x;
      VertexNormals[3 * Indices[3 * i + 2] + 1] -= D.y;
      VertexNormals[3 * Indices[3 * i + 2] + 2] -= D.z;
    }

}

void Object::CreateVertexTextureCoords(std::string FilePath)
{

  std::ifstream Obj(FilePath);
  for (std::string line; std::getline(Obj, line); )
    {
      //std::cout << line << std::endl;
      if (line[0] == 'v' && line[1] == 't')
	{//v  40.6266  28.3457  -1.10804
	  std::vector<int> start;
	  std::vector<int> end;
	  for (int i = 0; i < line.size(); i++)
	    {
	      if (line[i] == ' ' && line[i + 1] != ' ')
		{
		  start.push_back(i + 1);
		}
	      if (line[i] == ' ' && line[i - 1] != ' ')
		{
		  end.push_back(i);
		}
	    }
	  end.erase(end.begin());
	  end.push_back(line.size());

	  for (int i = 0; i < start.size(); i++)
	    {
	      std::string Vert;
	      for (int k = 0; k < end[i] - start[i]; k++)
		{
		  Vert.push_back(line[start[i] + k]);
		}
	      VertexTexture.push_back(std::stof(Vert));
	    }
	}
    }
  Obj.close();

}

void Object::CreateIndicies(std::string FilePath)
{

  std::ifstream Obj(FilePath);
  std::vector<unsigned int> QuadIndices;

  for (std::string line; std::getline(Obj, line); )
    {
      //std::cout << line << std::endl;
      if (line[0] == 'f' && line[1] == ' ')
	{//v  40.6266  28.3457  -1.10804
	  std::vector<int> start;
	  std::vector<int> end;
	  for (int i = 0; i < line.size(); i++)
	    {
	      if (line[i] == ' ' && line[i + 1] != ' ')
		{
		  start.push_back(i + 1);
		}
	      if (line[i] == ' ' && line[i - 1] != ' ')
		{
		  end.push_back(i);
		}
	    }
	  end.erase(end.begin());
	  end.push_back(line.size());

	  for (int i = 0; i < start.size(); i++)
	    {
	      std::string Ind;
	      for (int k = 0; k < end[i] - start[i]; k++)
		{
		  Ind.push_back(line[start[i] + k]);
		}
	      if (start.size() == 3 && end.size() == 3)
		{
		  Indices.push_back(std::stof(Ind) - 1);
		}
	      else if (start.size() == 4 && end.size() == 4)
		{
		  QuadIndices.push_back(std::stof(Ind) - 1);
		}
	      else {
		throw "WTF";
	      }
	    }


	}
    }
  QuadToTri(QuadIndices);

  for (int i = 0; i < Indices.size(); i++)
    {
      //std::cout << TriangleIndices[i] << std::endl;
    }
  Obj.close();
}

void Object::QuadToTri(std::vector<unsigned int> QuadIndices)
{
  std::vector<unsigned int> TriIndTemp;
  for (int i = 0; i < QuadIndices.size() / 4; i++)
    {
      TriIndTemp.push_back(QuadIndices[(4 * i) + 0]);	//1
      TriIndTemp.push_back(QuadIndices[(4 * i) + 1]);	//2
      TriIndTemp.push_back(QuadIndices[(4 * i) + 2]);	//3
      TriIndTemp.push_back(QuadIndices[(4 * i) + 0]);	//1
      TriIndTemp.push_back(QuadIndices[(4 * i) + 3]);	//4
      TriIndTemp.push_back(QuadIndices[(4 * i) + 2]);	//3
    }
  for (int i = 0; i < TriIndTemp.size(); i++)
    {
      Indices.push_back(TriIndTemp[i]);
    }
}
