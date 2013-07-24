#include "Shader.h"


Shader::Shader(void)
{
}

Shader::~Shader(void)
{
}

bool Shader::Init(const char* vsFile, const char* fsFile)
{
	shader_vp = glCreateShader(GL_VERTEX_SHADER);
	shader_fp = glCreateShader(GL_FRAGMENT_SHADER);

	std::string vsText = readFile(vsFile);
	std::string fsText = readFile(fsFile);

	const char* vsTemp = vsText.c_str();
	const char* fsTemp = fsText.c_str();


	glShaderSource(shader_vp, 1, &vsTemp, 0);
	glShaderSource(shader_fp, 1, &fsTemp, 0);

	glCompileShader(shader_vp);
	Validate(shader_vp, vsFile);

	glCompileShader(shader_fp);
	Validate(shader_fp, fsFile);

	shader_id = glCreateProgram();
	glAttachShader(shader_id, shader_fp);
	glAttachShader(shader_id, shader_vp);
	glBindAttribLocation(shader_id, 0, "in_Position");
	glBindAttribLocation(shader_id, 2, "in_Normal");
	glLinkProgram(shader_id);

	return true;
}

void Shader::Validate(GLuint shader, const char* file)
{
	const unsigned int BUFFER_SIZE = 512;
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, BUFFER_SIZE);
    GLsizei length = 0;
    
    glGetShaderInfoLog(shader, BUFFER_SIZE, &length, buffer);

    if (length > 0)
	{
        std::cerr << "Shader " << shader << " (" << (file?file:"") << ") compile error:" << buffer << std::endl;
	}
}

std::string Shader::readFile(const char* fileName)
{
	std::fstream fileStream(fileName, std::ios::in);
	std::string shaderText;

	if(fileStream.is_open())
	{
		std::stringstream buf;
		buf << fileStream.rdbuf();
		shaderText = buf.str();
	}
	return shaderText;
}

void Shader::Bind()
{
	glUseProgram(shader_id);
}

void Shader::Unbind()
{
	glUseProgram(0);
}

unsigned int Shader::Id()
{
	return shader_id;
}