#pragma once

#include"renderer.h"

class Shader
{
public:

	~Shader() {
		glDeleteShader(m_VertexShader);
		glDeleteShader(m_FragmentShader);
		glDeleteProgram(m_ID);
	}

	void load_shader(const char* vFile, const char* fFile);
	GLuint GetID() { return m_ID; }
	void use() { glUseProgram(m_ID); }
private:
	const char* VertSource;
	const char* FragSource;
	GLuint m_ID;
	GLuint m_VertexShader;
	GLuint m_FragmentShader;

	std::string read_file(const char* filePath);
	void check_compile_errors(GLuint shader, const std::string& type);
};
