#pragma once

#include"GLRenderer.h"
#define API_GL 0
#define API_DIRECTX 1


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
 
namespace wrl = Microsoft::WRL;
struct GLFWwindow; // Forward declaration

class WindowHandel
{
public:
	 
	void init(int width, int height, const char* title,uint32_t clint);
	GLFWwindow* GetHandel();
	void ShutDown();
	glm::vec2 GetWindowSize() const { return winsize; }
	void UpdatehandelDelta();
	float GetDeltaT();
	int GetFPS();
	glm::vec2 GetScreenSize();
	uint32_t GetApiClint();
	bool WindowShouldClose();
	// DirectX Objects
	DXGI_SWAP_CHAIN_DESC sd = {0};
	D3D_FEATURE_LEVEL featureLevel;
	Microsoft::WRL::ComPtr <ID3D11Device> pDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> pContext;
	IDXGISwapChain* pSwap = nullptr;
	//ID3D11RenderTargetView* pTarget;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pTarget;

private:
	// Window
	GLFWwindow* window;
	glm::ivec2 winsize;
	HWND hwnd;
	int x, y, n;
	void setParas();
	void initDX(GLFWwindow* window);
	// Time
	float lastFrameTime =  0.f;
	float deltaTime = 0.0f;
	float currentTime = 0.f;
	//api stuff
	uint32_t api;
};