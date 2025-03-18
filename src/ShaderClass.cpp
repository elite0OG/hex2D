#include "renderer.h"
 
std::string Shader::read_file(const char* filePath)
{
	std::ifstream file(filePath);
	if (!file.is_open())
	{
		log(LOG_ERROR, "Could not open shader");
		return "";
	}
	else {
		log(LOG_INFO, sstc("Shader file opened: ",filePath).c_str()); }

	std::stringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}

void Shader::check_compile_errors(GLuint shader, const std::string& type)
{
    GLint success;
    char infoLog[1024];

    if (type == "PROGRAM")
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
            log(LOG_ERROR, sstc("PROGRAM LINKING FAILED: ",infoLog).c_str()  );
		}
		else { log(LOG_INFO, "PROGRAM LINKING PASS:"); }
    }
    else
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
			log(LOG_ERROR, sstc(" SHADER COMPILATION FAILED:",infoLog).c_str());
		}
		else { log(LOG_INFO, "SHADER COMPILATION PASS"); }
    }
}

void Shader::load_shader(const char* vFile, const char* fFile)
{
	// Read shader source code from files
	std::string vShaderCode = read_file(vFile);
	std::string fShaderCode = read_file(fFile);

	if (vShaderCode.empty() )
	{
		log(LOG_ERROR, "Shader source code is empty! vertex");
		return;
	} 
	if (fShaderCode.empty())
	{
		log(LOG_ERROR, "Shader source code is empty! fragment");
		return;
	}


	VertSource = vShaderCode.c_str();
	FragSource = fShaderCode.c_str();

	// Compile vertex shader
	m_VertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(m_VertexShader, 1, &VertSource, nullptr);
	glCompileShader(m_VertexShader);
	check_compile_errors(m_VertexShader, "VERTEX");

	// Compile fragment shader
	m_FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(m_FragmentShader, 1, &FragSource, nullptr);
	glCompileShader(m_FragmentShader);
	check_compile_errors(m_FragmentShader, "FRAGMENT");

	// Link shaders into a program
	m_ID = glCreateProgram();
	glAttachShader(m_ID, m_VertexShader);
	glAttachShader(m_ID, m_FragmentShader);
	glLinkProgram(m_ID);
	check_compile_errors(m_ID, "PROGRAM");

	// Delete shaders after linking
	glDeleteShader(m_VertexShader);
	glDeleteShader(m_FragmentShader);
}
