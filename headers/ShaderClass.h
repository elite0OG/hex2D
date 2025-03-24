#pragma once

//#include"GLRenderer.h"
#include<string>
class Shader
{
public:

	~Shader();
	 

	void load_shader(const char* vFile, const char* fFile);
	unsigned int GetID();
	void use();
private:
	const char* VertSource;
	const char* FragSource;
	unsigned int  m_ID;
	unsigned int m_VertexShader;
	unsigned int m_FragmentShader;

	std::string read_file(const char* filePath);
	void check_compile_errors(unsigned int shader, const std::string& type);
};
