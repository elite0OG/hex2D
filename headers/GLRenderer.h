#pragma once

#pragma warning( disable : 4005 )
#define WIN32_LEAN_AND_MEAN 
#define GLM_ENABLE_EXPERIMENTAL
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/string_cast.hpp>  

#include<array>
#include<vector>
#include<fstream>
#include<string>
#include<sstream>

#include"ShaderClass.h"
#include"WindowHandel.h"
#include"logger.h"



#define vec2Zero glm::vec2{0.f,0.f}
#define RED  glm::vec4{255.f,0.f,0.f,1.f}
#define BLUE  glm::vec4{0.f,0.f,255.f,1.f}
#define CONBLUE glm::vec4{ 100.f, 149.f, 237.f, 255.f }
#define HEXBLACK glm::vec4{ 27.f, 27.f, 27.f, 255.f }
#define WHITE glm::vec4{ 255.f, 255.f, 255.f, 255.f }
#define DEFALT_GLRenderer_TYPE 0


 
std::string sstc(std::string t1, std::string t2);



class GLRenderer
{
public:
	bool v = true;
	void init(WindowHandel& handel);
	void ShutDown();
	 
	/// pos.z don't work because GLRenderer only use 2D so Z axis is useless it fallow for all drawcall!!
	void DrawTriangle(glm::vec3 pos , glm::vec4 color); 
	void DrawQuad(glm::vec3 pos, glm::vec4 color);

	void DrawTriangleV(glm::vec3 pos, glm::vec2 size,glm::vec2 RotetionAngle,float angle ,glm::vec4 color);
	void DrawQuadV(glm::vec3 pos, glm::vec2 size, glm::vec2 RotetionAngle, float angle, glm::vec4 color);
	void load_PVM();
	void ClearBackground(glm::vec4 color);
	void beginDrawing();
	void endDrawing( );
	void DrawImguiText(const char* text, glm::vec2 pos, float fontS);

	void DrawTextHex(const char* s, glm::vec2 pos, glm::vec4 color);
	//GLuint LoadFontTexture(const char* fontPath);
	//void RenderText(const char* text, glm::vec2 pos, float scale);
	void PrintProjection();
private:
	std::array<float, 12> verticis;
	const unsigned int indices[6] = {1, 2, 3,0, 1, 3};
	unsigned int m_VAO;
	unsigned int m_VBO;   
	unsigned int m_EBO;
	 
	glm::mat4 model = glm::mat4(1.f);
	glm::mat4 projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);
	 
	glm::mat4 view = glm::mat4(1.0f);   
	Shader shader;

	bool isdrawablity = false;

	 
	WindowHandel h;
	 
	 
};