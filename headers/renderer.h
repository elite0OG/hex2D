#pragma once
#include<stdio.h>
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#define GLM_ENABLE_EXPERIMENTAL
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>  
#include<array>
#include<fstream>
#include<string>
#include<sstream>
#include<iostream>
#include"WindowHandel.h"
#include"ShaderClass.h"


#define LOG_INFO  0
#define LOG_WARN  1
#define LOG_ERROR  3
#define vec2Zero glm::vec2{0.f,0.f}
#define RED  glm::vec4{255.f,0.f,0.f,1.f}
#define BLUE  glm::vec4{0.f,0.f,255.f,1.f}
#define DEFALT_RENDERER_TYPE 0
 


void log(unsigned int LOG, const char* v);
void log(unsigned int LOG, std::string v);
std::string sstc(std::string t1, std::string t2);


class Renderer
{
public:
	void init(glm::vec2 windowsize);
	void ShutDown();
	void RendererHint(unsigned int hint, int value);
	/// pos.z don't work because renderer only use 2D so Z axis is useless it fallow for all drawcall!!
	void DrawTriangle(glm::vec3 pos , glm::vec4 color); 
	void DrawQuad(glm::vec3 pos, glm::vec4 color);

	void DrawTriangleV(glm::vec3 pos, glm::vec2 size,glm::vec2 RotetionAngle,float angle ,glm::vec4 color);
	void DrawQuadV(glm::vec3 pos, glm::vec2 size, glm::vec2 RotetionAngle, float angle, glm::vec4 color);
	void load_PVM();
	void ClearBackground(glm::vec4 color);
	void beginDrawing();
	void endDrawing(GLFWwindow* h);
	void PrintProjection();
private:
	std::array<GLfloat, 12> verticis;
	const unsigned int indices[6] = {1, 2, 3,0, 1, 3};
	GLuint m_VAO;
	GLuint m_VBO;   
	GLuint m_EBO;
	glm::vec2 rendersize;
	glm::mat4 model = glm::mat4(1.f);
	glm::mat4 projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);
	 
	glm::mat4 view = glm::mat4(1.0f);   
	Shader shader;

	bool isdrawablity = false;
	 
};