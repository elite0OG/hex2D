#define STB_IMAGE_IMPLEMENTATION

//glViewport

#include "GLRenderer.h"


 
std::string sstc(std::string t1, std::string t2)
{

	return (t1 + t2);
}
 
void GLRenderer::init(WindowHandel& handel)
{
	this->h = handel;
	 {

		verticis =
		{
			 0.5f,  0.5f, 0.0f,  // top right
			 0.5f, -0.5f, 0.0f,  // bottom right
			-0.5f, -0.5f, 0.0f,  // bottom left
			-0.5f,  0.5f, 0.0f   // top left 
		};

		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);
		glGenBuffers(1, &m_EBO);

		glBindVertexArray(m_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(verticis), verticis.data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glBindVertexArray(0);


		shader.load_shader("Resources/Shaders/def_vert.glsl", "Resources/Shaders/def_frag.glsl");

		ImGui::CreateContext();                           // 1️⃣ Create ImGui context
		ImGuiIO& io = ImGui::GetIO(); (void)io;          // 2️⃣ Get IO (for inputs, fonts)
		ImGui::StyleColorsDark();                         // 3️⃣ Set dark mode (optional)

		// 4️⃣ Initialize GLFW + OpenGL for ImGui
		ImGui_ImplGlfw_InitForOpenGL(h.GetHandel(), true);
		ImGui_ImplOpenGL3_Init("#version 460");  // Use your GLSL version

	}
	 
}

 

void GLRenderer::ShutDown()
{
	Hlog(LOG_INFO, "GLRenderer closed successfully");

	 
		glDeleteBuffers(1, &m_VBO);
		glDeleteBuffers(1, &m_EBO);
		glDeleteVertexArrays(1, &m_VAO);
		ImGui_ImplOpenGL3_Shutdown();
		if (ImGui::GetCurrentContext()) {
			ImGui_ImplGlfw_Shutdown();
			ImGui::DestroyContext();
		}
	

	
}

 

void GLRenderer::DrawTriangle(glm::vec3 pos, glm::vec4 color)
{
	if(isdrawablity){
		shader.use();
		glBindVertexArray(m_VAO);
		glUniform4f(glGetUniformLocation(shader.GetID(), "color"), color.x, color.y, color.z, color.w);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3{ pos.x  ,pos.y  ,0.f });
		model = glm::scale(model, glm::vec3(100.f, 100.f, 1.f));
		load_PVM();
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
	}
}

void GLRenderer::DrawQuad(glm::vec3 pos, glm::vec4 color)
{
	if(isdrawablity){
		shader.use();
		glBindVertexArray(m_VAO);
		glUniform4f(glGetUniformLocation(shader.GetID(), "color"), color.x, color.y, color.z, color.w);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3{ pos.x  ,pos.y  ,0.f });
		model = glm::scale(model, glm::vec3(100.f, 100.f, 1.f));
		load_PVM();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	}
}

void GLRenderer::DrawTriangleV(glm::vec3 pos, glm::vec2 size, glm::vec2 RotetionAngle, float angle, glm::vec4 color)
{
	if (isdrawablity) {
		shader.use();
		glBindVertexArray(m_VAO);
		glUniform4f(glGetUniformLocation(shader.GetID(), "color"), color.x, color.y, color.z, color.w);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3{ pos.x  ,pos.y  ,0.f });
		model = glm::scale(model, glm::vec3(size.x,size.y,1.f));
		if (RotetionAngle != vec2Zero && angle != 0.f)
			model = glm::rotate(model,angle, glm::vec3(RotetionAngle.y, RotetionAngle.x, 0.f));
		load_PVM();
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
	}
}

void GLRenderer::DrawQuadV(glm::vec3 pos, glm::vec2 size, glm::vec2 RotetionAngle, float angle, glm::vec4 color)
{
	if (isdrawablity) {
		shader.use();

		glBindVertexArray(m_VAO);
		glUniform4f(glGetUniformLocation(shader.GetID(), "color"), color.x, color.y, color.z, color.w);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3{ pos.x ,pos.y ,0.f });
		model = glm::scale(model, glm::vec3(size.x, size.y, 1.f));

		if(RotetionAngle != vec2Zero && angle != 0.f)
			model = glm::rotate(model, angle, glm::vec3(RotetionAngle.y, RotetionAngle.x, 0.f));

		load_PVM();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
}

void GLRenderer::load_PVM()
{
	glUniformMatrix4fv(glGetUniformLocation(shader.GetID(), "P"), 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(shader.GetID(), "V"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(shader.GetID(), "M"), 1, GL_FALSE, glm::value_ptr(model));
}

void GLRenderer::ClearBackground(glm::vec4 color) 
{
	if(isdrawablity){
		glClearColor(color.x/255.f, color.y / 255.f, color.z / 255.f, color.w / 255.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}

void GLRenderer::beginDrawing()
{
	isdrawablity = true;
	glfwPollEvents();

	 
		glDisable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);

		// ✅ Initialize ImGui Frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	 
	 
}

void GLRenderer::endDrawing() {
	if (v)
	{
		glfwSwapInterval(1);
	}else glfwSwapInterval(0);
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(h.GetHandel());
	
	 
}

void GLRenderer::DrawTextHex(const char* s, glm::vec2 pos, glm::vec4 color)
{
	

	//gltSetText(text,  s);
	//// Draw any amount of text between begin and end
	//gltColor(color.x/255.f, color.y / 255.f, color.z / 255.f, color.w / 255.f);
	//gltDrawText2D(text, pos.x, pos.y, 2.f);


	
}

void GLRenderer::PrintProjection()
{
	Hlog(LOG_INFO, ("Projection: " + glm::to_string(projection)).c_str());
}
