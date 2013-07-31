#pragma once
#include <GL/glew.h>
#include <glm.hpp>
#include <vector>
#include <map>
#include <iostream>
#include <math.h>
#include <stdint.h>
#include <noise\noise.h>
#include "ConfigLoader.h"

#define LAT 64
#define LON 32

struct Indices
{
	int v1;
	int v2;
	int v3;

	Indices(int v1, int v2, int v3)
	{
		this->v1 = v1;
		this->v2 = v2;
		this->v3 = v3;
	}
};

class Atmosphere
{
public:
	Atmosphere(void);
	~Atmosphere(void);

public:
	void Init();
	void Draw();
	void Destroy();

private:
	int getMiddlePoint(int p1, int p2);
	int addVertex(const glm::vec3& vec);

private:
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<Indices> faces;
	std::vector<unsigned int> indices;
	int index;
	std::map<int64_t, int> middlePointCache;

	unsigned int IDVao[1];
	unsigned int IDVbo[3];
};

