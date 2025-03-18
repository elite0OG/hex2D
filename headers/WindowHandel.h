#pragma once

#include"renderer.h"

class WindowHandel
{
public:

	void init(int width, int height, const char* title);
	GLFWwindow* GetHandel() { return window; }
	void ShutDown();
	glm::vec2 GetWindowSize() { return winsize; }
private:
	GLFWwindow* window;
	glm::vec2 winsize;
	void setParas();
};