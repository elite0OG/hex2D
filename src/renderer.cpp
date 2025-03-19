#define STB_IMAGE_IMPLEMENTATION

//glViewport

#include "renderer.h"
 
void Hlog(unsigned int LOG, const char* v)
{
	switch (LOG) {
	case LOG_INFO:
		printf("\x1b[32mLOG_INFO: %s\n\x1b[0m", v);
		break;
	case LOG_WARN:
		printf("\x1b[33mLOG_WARN: %s\n\x1b[0m", v);
		break;
	case LOG_ERROR:
		printf("\x1b[31mLOG_ERROR: %s\n\x1b[0m", v);
		break;
	default:
		printf("\x1b[37mLOG_NOR: %s\n\x1b[0m", v);
		break;
	}
	
}

void Hlog(unsigned int LOG, std::string v)
{

	switch (LOG) {
	case LOG_INFO:
		std::cout << "\x1b[32mLOG_INFO: " << v << "\x1b[0m\n";
		break;
	case LOG_WARN:
		std::cout << "\x1b[33mLOG_WARN: " << v << "\x1b[0m\n";
		break;
	case LOG_ERROR:
		std::cout << "\x1b[31mLOG_ERROR: " << v << "\x1b[0m\n";
		break;
	default:
		std::cout << "\x1b[37mLOG_NOR: " << v << "\x1b[0m\n";  // Default case
		break;
	}
}

std::string sstc(std::string t1, std::string t2)
{

	return (t1 + t2);
}
 
void Renderer::init(WindowHandel handel)
{
	h = handel;
	if(handel.GetApiClint() == API_GL){

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

 

void Renderer::ShutDown()
{
	Hlog(LOG_INFO, "Renderer closed successfully");

	if (h.GetApiClint() == API_GL)  // OpenGL shutdown
	{
		glDeleteBuffers(1, &m_VBO);
		glDeleteBuffers(1, &m_EBO);
		glDeleteVertexArrays(1, &m_VAO);
		ImGui_ImplOpenGL3_Shutdown();
	}

	if (ImGui::GetCurrentContext()) {
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}
}

void Renderer::RendererHint(unsigned int hint, int value)
{
	if (hint == DEFALT_RENDERER_TYPE && value == 4)
	{
		Hlog(LOG_INFO, "THE RENDERER WILL ONLY GOING TO DRAW QUAD! AND TRIANGLES ARE THE PART OF THE QUAD");
	}
	else {
		Hlog(LOG_WARN, "RENDERER IS UNABLE TO RECOGNIZE THE RENDERING TYPE DEFALT TYPE IS SETED!"); 
		value = 4;
		hint = DEFALT_RENDERER_TYPE;
	}
}

void Renderer::DrawTriangle(glm::vec3 pos, glm::vec4 color)
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

void Renderer::DrawQuad(glm::vec3 pos, glm::vec4 color)
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

void Renderer::DrawTriangleV(glm::vec3 pos, glm::vec2 size, glm::vec2 RotetionAngle, float angle, glm::vec4 color)
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

void Renderer::DrawQuadV(glm::vec3 pos, glm::vec2 size, glm::vec2 RotetionAngle, float angle, glm::vec4 color)
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

void Renderer::load_PVM()
{
	glUniformMatrix4fv(glGetUniformLocation(shader.GetID(), "P"), 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(shader.GetID(), "V"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(shader.GetID(), "M"), 1, GL_FALSE, glm::value_ptr(model));
}

void Renderer::ClearBackground(glm::vec4 color) 
{
	if(isdrawablity){
		glClearColor(color.x/255.f, color.y / 255.f, color.z / 255.f, color.w / 255.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
}

void Renderer::beginDrawing()
{
	isdrawablity = true;
	glfwPollEvents();

	if (h.GetApiClint() == API_GL) {
		glDisable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);

		// ✅ Initialize ImGui Frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	else if (h.GetApiClint() == API_DIRECTX) {
		if (!h.pContext || !h.pSwap) return; // ✅ Prevents crash if DX is not initialized

		// ✅ Initialize ImGui Frame for DirectX
		//ImGui_ImplDX11_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}
}

void Renderer::endDrawing() {
	if (h.GetApiClint() == API_GL) {
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(h.GetHandel());
	}
	else if (h.GetApiClint() == API_DIRECTX) {
		if (!h.pContext || !h.pSwap || glfwWindowShouldClose(h.GetHandel())) return;  // ✅ Prevent access after shutdown

		// ✅ Ensure ImGui rendering for DirectX
		ImGui::Render();
		//ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

		h.pSwap->Present(1, 0);
	}
}

void Renderer::DrawTextHex(const char* s, glm::vec2 pos, glm::vec4 color)
{
	

	//gltSetText(text,  s);
	//// Draw any amount of text between begin and end
	//gltColor(color.x/255.f, color.y / 255.f, color.z / 255.f, color.w / 255.f);
	//gltDrawText2D(text, pos.x, pos.y, 2.f);


	
}

void Renderer::PrintProjection()
{
	Hlog(LOG_INFO, ("Projection: " + glm::to_string(projection)).c_str());
}
