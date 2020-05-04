#include "MeshLoader.h"

namespace MeshLoader
{
	void LoadVertices(ifstream& inFile, Mesh& mesh);
	void LoadNormals(ifstream& inFile, Mesh& mesh);
	void LoadTexCoords(ifstream& inFile, Mesh& mesh);
	void LoadIndices(ifstream& inFile, Mesh& mesh);

	void LoadVertices(ifstream& inFile, Mesh& mesh)
	{
		inFile >> mesh.VertexCount;

		if (mesh.VertexCount > 0)
		{
			mesh.Vertices = new Vertex[mesh.VertexCount];

			for (int i = 0; i < mesh.VertexCount; i++)
			{
				inFile >> mesh.Vertices[i].x;
				inFile >> mesh.Vertices[i].y;
				inFile >> mesh.Vertices[i].z;
			}
		}
	}

	void LoadTexCoords(ifstream& inFile, Mesh& mesh)
	{
		inFile >> mesh.TexCoordCount;

		if (mesh.TexCoordCount > 0)
		{
			mesh.TexCoords = new TexCoord[mesh.TexCoordCount];

			for (int i = 0; i < mesh.TexCoordCount; i++)
			{
				inFile >> mesh.TexCoords[i].u;
				inFile >> mesh.TexCoords[i].v;
			}
		}
	}

	void LoadNormals(ifstream& inFile, Mesh& mesh)
	{
		inFile >> mesh.NormalCount;

		if (mesh.NormalCount > 0)
		{
			mesh.Normals = new Vector3[mesh.NormalCount];

			for (int i = 0; i < mesh.NormalCount; i++)
			{
				inFile >> mesh.Normals[i].x;
				inFile >> mesh.Normals[i].y;
				inFile >> mesh.Normals[i].z;
			}
		}
	}

	void LoadIndices(ifstream& inFile, Mesh& mesh)
	{
		inFile >> mesh.IndexCount;

		if (mesh.IndexCount > 0)
		{
			mesh.Indices = new GLushort[mesh.IndexCount];

			for (int i = 0; i < mesh.IndexCount; i++)
			{
				inFile >> mesh.Indices[i];
			}
		}
	}
	
	Mesh* MeshLoader::Load(char* path)
	{
		Mesh* mesh = new Mesh();

		ifstream inFile;

		inFile.open(path);

		if (!inFile.good())
		{
			cerr << "Can't open mesh " << path << endl;
			return nullptr;
		}

		LoadVertices(inFile, *mesh);
		LoadTexCoords(inFile, *mesh);
		LoadNormals(inFile, *mesh);
		LoadIndices(inFile, *mesh);
		cout << "loaded " << path << endl;
		return mesh;
	}

	Mesh* MeshLoader::LoadOBJ(char* path)
	{
		Mesh* mesh = new Mesh();
		ifstream inFile(path);
		if (!inFile.good())
		{
			cerr << "Can't open file " << path << endl;
			return nullptr;
		}

		string prefix = "";
		
		string line = "";
		stringstream ss;
		int verticesCounter = 0;
		int texCoordCounter = 0;
		int normalsCounter = 0;
		int indicesCounter = 0;

		GLint temp_GLint = 0;

		vector<TexCoord> texCoordsTemp;
		vector<Vector3> normalsTemp;
		vector<Vertex> verticesTemp;
		vector<GLushort> indicesTemp;
		while (getline(inFile, line))
		{
			ss.clear();
			ss.str(line);
			ss >> prefix;			
			
			float temp = 0, temp2 = 0, temp3 = 0;

			if (prefix == "vt") //vertex texcoords
			{
				while (ss.peek() == ' ')
				{
					ss.ignore(1, ' ');
				}
				ss >> temp >> temp2;
				texCoordsTemp.push_back({ temp, temp2 });
			}
			else if (prefix == "vn") //vertex normals
			{
				while (ss.peek() == ' ')
				{
					ss.ignore(1, ' ');
				}
				ss >> temp >> temp2 >> temp3;
				normalsTemp.push_back({ temp, temp2 });
			}
			else if (prefix == "v") //Vertex positions
			{
				while (ss.peek() == ' ')
				{
					ss.ignore(1, ' ');
				}
				ss >> temp >> temp2 >> temp3;
				verticesTemp.push_back({ temp, temp2, temp3 });
			}
			else if (prefix == "f") //faces
			{
				while (ss >> temp_GLint)
				{
					if(temp_GLint != '/' && temp_GLint != ' ')
					{
						indicesTemp.push_back((temp_GLint - 1));
						mesh->IndexCount++;
					}
					if (ss.peek() == '/')
					{
						ss.ignore(10, ' ');
					}
				}
			}
			else
			{
				//std::cout << "skip: " << prefix << endl;
			}
		}

		mesh->VertexCount = verticesTemp.size();
		mesh->Vertices = new Vertex[mesh->VertexCount];
		for (int i = 0; i < mesh->VertexCount; i++)
		{
			mesh->Vertices[i].x = verticesTemp[i].x;
			mesh->Vertices[i].y = verticesTemp[i].y;
			mesh->Vertices[i].z = verticesTemp[i].z;
		}

		mesh->TexCoordCount = texCoordsTemp.size();
		mesh->TexCoords = new TexCoord[mesh->TexCoordCount];
		for (int i = 0; i < mesh->TexCoordCount; i++)
		{
			mesh->TexCoords[i].u = texCoordsTemp[i].u;
			mesh->TexCoords[i].v = texCoordsTemp[i].v;
		}

		mesh->NormalCount = normalsTemp.size();
		mesh->Normals = new Vector3[mesh->NormalCount];
		for (int i = 0; i < mesh->NormalCount; i++)
		{
			mesh->Normals[i].x = normalsTemp[i].x;
			mesh->Normals[i].y = normalsTemp[i].y;
			mesh->Normals[i].z = normalsTemp[i].z;
		}

		mesh->Indices = new GLushort[mesh->IndexCount];
		for (int i = 0; i < mesh->IndexCount; i++)
		{
			mesh->Indices[i] = indicesTemp[i];
		}

		//mesh->IndexCount = sizeof(indicesTemp);

		std::cout << "Loaded " << path << endl;
		return mesh;
	}
}