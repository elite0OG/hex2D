#pragma once

#include"GLRenderer.h"
#define API_GL 0
#define API_DIRECTX 1

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <d3d11.h>
#include <dxgi.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <wrl.h>
#include <iostream>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "D3DCompiler.lib")	

static bool brak = false;
static bool glfwInitialized = false;
namespace wrl = Microsoft::WRL;
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
	DXGI_SWAP_CHAIN_DESC sd = {0};
	D3D_FEATURE_LEVEL featureLevel;
	Microsoft::WRL::ComPtr <ID3D11Device> pDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> pContext;
	IDXGISwapChain* pSwap = nullptr;
	//ID3D11RenderTargetView* pTarget;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pTarget;

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


	
	
	uint32_t api;
};