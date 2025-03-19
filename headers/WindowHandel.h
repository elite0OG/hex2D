#pragma once

#include"renderer.h"
#define API_GL 0
#define API_DIRECTX 1

#include<Windows.h>
#include<d3d11.h>
#include <dxgi.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
static bool brak = false;
static bool glfwInitialized = false;
class WindowHandel
{
public:

	void init(int width, int height, const char* title,uint32_t clint);
	GLFWwindow* GetHandel() { return window; }
	void ShutDown();
	glm::vec2 GetWindowSize() { return winsize; }
	void UpdatehandelDelta();
	float GetDeltaT();
	int GetFPS();
	glm::vec2 GetScreenSize();
	uint32_t GetApiClint();

	// DirectX Objects
	IDXGISwapChain* pSwap = nullptr;
	ID3D11Device* pDevice = nullptr;
	ID3D11DeviceContext* pContext = nullptr;
private:
	GLFWwindow* window;
	glm::ivec2 winsize;
	HWND hwnd;

	GLFWimage im = { 0 };
	int x, y, n;
	void setParas();
	void initDX(GLFWwindow* window);
	
	float lastFrameTime = (float)glfwGetTime();
	float deltaTime = 0.0f;
	float currentTime = 0.f;


	// DX stuff
	
	uint32_t api;
};