#include "Atmosphere.h"


Atmosphere::Atmosphere(void)
{
}


Atmosphere::~Atmosphere(void)
{
}

int Atmosphere::getMiddlePoint(int p1, int p2)
{
	bool firstIsSmaller = p1 < p2;
	int64_t smallerIndex = firstIsSmaller ? p1 : p2;
	int64_t greaterIndex = firstIsSmaller ? p2 : p1;
	int64_t key = (smallerIndex << 32) + greaterIndex;

	int ret;
	std::map<int64_t, int>::iterator it = middlePointCache.find(key);
	if(it != middlePointCache.end())
	{
		return it->second;
	}

	glm::vec3 point1 = vertices.at(p1);
	glm::vec3 point2 = vertices.at(p2);

	glm::vec3 middle = glm::vec3((point1.x+point2.x) / 2.0f, (point1.y+point2.y) / 2.0f, (point1.z+point2.z) / 2.0f);

	int i = addVertex(middle);

	middlePointCache.insert(std::pair<int64_t, int>(key, i));
	return i;
}

int Atmosphere::addVertex(const glm::vec3& vec)
{
	vertices.push_back(glm::normalize(vec));
	return index++;
}

void Atmosphere::Init()
{
	index = 0;

	float t = (1.0 + std::sqrt(5.0)) / 2.0f;

	addVertex(glm::vec3(-1, t, 0));
	addVertex(glm::vec3(1, t, 0));
	addVertex(glm::vec3(-1, -t, 0));
	addVertex(glm::vec3(1, -t, 0));

	addVertex(glm::vec3(0, -1, t));
	addVertex(glm::vec3(0, 1, t));
	addVertex(glm::vec3(0, -1, -t));
	addVertex(glm::vec3(0, 1, -t));

	addVertex(glm::vec3(t, 0, -1));
	addVertex(glm::vec3(t, 0, 1));
	addVertex(glm::vec3(-t, 0, -1));
	addVertex(glm::vec3(-t, 0, 1));

	faces.push_back(Indices(0, 11, 5));
	faces.push_back(Indices(0, 5, 1));
	faces.push_back(Indices(0, 1, 7));
	faces.push_back(Indices(0, 7, 10));
	faces.push_back(Indices(0, 10, 11));

	faces.push_back(Indices(1, 5, 9));
	faces.push_back(Indices(5, 11, 4));
	faces.push_back(Indices(11, 10, 2));
	faces.push_back(Indices(10, 7, 6));
	faces.push_back(Indices(7, 1, 8));

	faces.push_back(Indices(3, 9, 4));
	faces.push_back(Indices(3, 4, 2));
	faces.push_back(Indices(3, 2, 6));
	faces.push_back(Indices(3, 6, 8));
	faces.push_back(Indices(3, 8, 9));

	faces.push_back(Indices(4, 9, 5));
	faces.push_back(Indices(2, 4, 11));
	faces.push_back(Indices(6, 2, 10));
	faces.push_back(Indices(8, 6, 7));
	faces.push_back(Indices(9, 8, 1));

	int iterations = ConfigLoader::ReadInt("iterations");

	for(int i = 0; i < iterations; i++)
	{
		std::vector<Indices> faces2;
		faces2.reserve(faces.size());
		for(int i = 0; i < faces.size(); i++)
		{
			int a = getMiddlePoint(faces[i].v1, faces[i].v2);
			int b = getMiddlePoint(faces[i].v2, faces[i].v3);
			int c = getMiddlePoint(faces[i].v3, faces[i].v1);

			faces2.push_back(Indices(faces[i].v1, a, c));
			faces2.push_back(Indices(faces[i].v2, b, a));
			faces2.push_back(Indices(faces[i].v3, c, b));
			faces2.push_back(Indices(a, b, c));
		}
		faces = faces2;
	}

	for(int i = 0; i < faces.size(); i++)
	{
		indices.push_back(faces[i].v1);
		indices.push_back(faces[i].v2);
		indices.push_back(faces[i].v3);
	}

	noise::module::RidgedMulti perlinGen;
	perlinGen.SetFrequency(1);
	int seed = ConfigLoader::ReadInt("seed");
	perlinGen.SetSeed(seed);
	noise::module::Clamp clampGen;
	clampGen.SetSourceModule(0, perlinGen);
	clampGen.SetBounds(0, 1);

	std::cout << "Number of Vertices: " << vertices.size() << std::endl;

	for(int i = 0; i < vertices.size(); i++)
	{
		float scaler = clampGen.GetValue(vertices.at(i).x, vertices.at(i).y, vertices.at(i).z);
		scaler /= 20;
		glm::vec3 newVertex = vertices.at(i) + scaler;
		vertices.at(i) = newVertex;
	}

	for(int i = 0; i < vertices.size(); i++)
	{
		normals.push_back(glm::vec3(0,0,0));
	}

	for(int i = 0; i < faces.size(); i++)
	{
		glm::vec3 vertexA = vertices[faces[i].v1];
		glm::vec3 vertexB = vertices[faces[i].v2];
		glm::vec3 vertexC = vertices[faces[i].v3];

		glm::vec3 firstEdge = vertexB - vertexA;
		glm::vec3 secondEdge = vertexC - vertexA;

		glm::vec3 normal = glm::cross(firstEdge, secondEdge);
		normal = glm::normalize(normal);

		normals[faces[i].v1] += normal;
		normals[faces[i].v2] += normal;
		normals[faces[i].v3] += normal;
	}

	//Normalize again
	for(int i = 0; i < normals.size(); i++)
	{
		normals[i] = glm::normalize(normals[i]);
	}

	glGenVertexArrays(1, &IDVao[0]);
	glBindVertexArray(IDVao[0]);

	glGenBuffers(3, &IDVbo[0]);

	glBindBuffer(GL_ARRAY_BUFFER, IDVbo[0]);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GL_FLOAT) * 3, &vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IDVbo[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GL_UNSIGNED_INT), &indices[0], GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)1, 1, GL_UNSIGNED_INT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, IDVbo[2]);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(GL_FLOAT) * 3, &normals[0], GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);
}

void Atmosphere::Draw()
{
	glBindVertexArray(IDVao[0]);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Atmosphere::Destroy()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glDeleteVertexArrays(2, IDVao);
}