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
#include<vector>
#include<fstream>
#include<string>
#include<sstream>
#include<iostream>
#include"WindowHandel.h"
#include"ShaderClass.h"
#include<stb_image.h>
#include <imgui.h>                // Core ImGui functions
#include<imgui_impl_opengl3.h>
#include<imgui_impl_glfw.h>


#define LOG_INFO  0
#define LOG_WARN  1
#define LOG_ERROR  3
#define vec2Zero glm::vec2{0.f,0.f}
#define RED  glm::vec4{255.f,0.f,0.f,1.f}
#define BLUE  glm::vec4{0.f,0.f,255.f,1.f}
#define CONBLUE glm::vec4{ 100.f, 149.f, 237.f, 255.f }
#define HEXBLACK glm::vec4{ 27.f, 27.f, 27.f, 255.f }
#define DEFALT_RENDERER_TYPE 0
 



	void Hlog(unsigned int LOG, const char* v);
	void Hlog(unsigned int LOG, std::string v);

std::string sstc(std::string t1, std::string t2);



class Renderer
{
public:
	void init(WindowHandel handel);
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
	void endDrawing( );
	void DrawTextHex(const char* s, glm::vec2 pos, glm::vec4 color);
	//GLuint LoadFontTexture(const char* fontPath);
	//void RenderText(const char* text, glm::vec2 pos, float scale);
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

	//GLFWwindow* handel;
	WindowHandel h;
	//GLTtext* text = gltCreateText();
	//GLuint fontTexture;
	//stbtt_bakedchar charData[96];
	//stbtt_aligned_quad q;
	 
};