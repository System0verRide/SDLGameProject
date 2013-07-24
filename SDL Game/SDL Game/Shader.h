#pragma once
#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class Shader
{
public:
	Shader(void);
	~Shader(void);

public:
	bool Init(const char* vsFile, const char* fsFile);
	void Bind();
	void Unbind();

	unsigned int Id();

private:
	unsigned int shader_id;
	unsigned int shader_vp;
	unsigned int shader_fp;

private:
	std::string readFile(const char* fileName);
	void Validate(GLuint shader, const char* file = 0);
};

