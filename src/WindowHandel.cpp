#include"GLRenderer.h"


void WindowHandel::setParas()
{

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
}
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <d3d11.h>
#include <dxgi.h>
#include <iostream>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")

void WindowHandel::initDX(GLFWwindow* window) {
    hwnd = glfwGetWin32Window(window);
    if (!hwnd) {
        Hlog(LOG_ERROR, "Failed to get HWND from GLFW!");
        return;
    }

    ZeroMemory(&sd, sizeof(sd));
    sd.BufferDesc.Width = 800;
    sd.BufferDesc.Height = 600;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.BufferCount = 1;
    sd.OutputWindow = hwnd;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    // Define supported feature levels
    D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0 };

    Hlog(LOG_INFO, ("DX SDK VERSION: " + std::to_string(D3D11_SDK_VERSION)).c_str());

    HRESULT hr = D3D11CreateDeviceAndSwapChain(
        nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0,
        featureLevels, _countof(featureLevels), D3D11_SDK_VERSION, &sd,
        &pSwap, &pDevice, &featureLevel, &pContext);

    if (FAILED(hr)) {
        Hlog(LOG_ERROR, "Failed to create D3D11 device and swap chain");
        return;
    }

    Hlog(LOG_INFO, "DirectX 11 initialized successfully.");
    if (!pDevice || !pContext || !pSwap) {
        Hlog(LOG_ERROR, "Direct3D objects are NULL after creation. Something went wrong!");
        return;
    }

    ID3D11Resource* pBackBuffer = NULL;
     
     hr = pSwap->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer);
    if (FAILED(hr)) {
        Hlog(LOG_ERROR, "Failed to get back buffer from swap chain.");
        return; // Exit to prevent using nullptr
    }

    // Create the render target view
    hr = pDevice->CreateRenderTargetView(pBackBuffer, NULL, &pTarget);
    if (FAILED(hr)) {
        Hlog(LOG_ERROR, "Failed to create render target view.");
    }

    // Release the back buffer reference (no longer needed)
    pBackBuffer->Release();
}


void WindowHandel::init(int width, int height, const char* title,uint32_t clint)
{
    winsize = glm::ivec2(width, height);
    api = clint;
    Hlog(LOG_INFO, "USING HEX_2D");
    if (!glfwInitialized) {
        if (!glfwInit()) {
            Hlog(LOG_ERROR, "GLFW initialization failed!");
            return;
        }
        glfwInitialized = true;
    }
    else { Hlog(LOG_INFO, "GLFW loaded successfully!"); }

    if (clint == API_GL) {
        setParas();
    }
    else if (clint == API_DIRECTX) {
       glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    }
	window = glfwCreateWindow(width, height, title, NULL, NULL);
   
    im.pixels = stbi_load("Resources/assets/logo2.png", &x, &y, &n,0);
    if(im.pixels){
        im.width = x;
        im.height = y;
        glfwSetWindowIcon(window, 1, &im);
    }else { Hlog(LOG_WARN, "unable to load logo texture"); }

    if (!window)
    {
        Hlog(LOG_WARN, "Window creation failed!");
        glfwTerminate();  
    }
    else { Hlog(LOG_INFO, "window created successfully!"); }

    
    if (clint == API_GL) {
        glfwMakeContextCurrent(window);
        glewExperimental = true;
        if (glewInit() != GLEW_OK) {
            Hlog(LOG_ERROR, "GLEW initialization failed!");
        }
        else {
            Hlog(LOG_INFO, "GLEW loaded successfully!");
            Hlog(LOG_INFO, "OPENGL INFO -");
            Hlog(LOG_INFO,"OPENGL VERTION: " + std::string(reinterpret_cast<const char*>(glGetString(GL_VERSION))));
            Hlog(LOG_INFO, "OPENGL VENDAL: " + std::string(reinterpret_cast<const char*>(glGetString(GL_RENDERER))));
            
        }
    }

   else if(clint == API_DIRECTX) 
   { 
       Hlog(LOG_INFO, "use DxRenderer for directx rendering instad of GLRenderer"); 
       initDX(window);
   }
   glfwSwapInterval(1);
}

void WindowHandel::ShutDown() {
    if (pTarget != NULL)pTarget->Release();
    if (pSwap != NULL) pSwap->Release();
    if (pDevice) pDevice->Release();
    if (pContext != NULL) pContext->Release();
    glfwDestroyWindow(window);
    glfwTerminate();
}

void WindowHandel::UpdatehandelDelta()
{
    currentTime = (float)glfwGetTime();
    deltaTime = currentTime - lastFrameTime;
    lastFrameTime = currentTime;

    glfwGetWindowSize(window, &winsize.x, &winsize.y);
    glViewport(0, 0, (GLsizei)winsize.x, (GLsizei)winsize.y);
   // Hlog(LOG_INFO, std::to_string(winsize.x) + " " + std::to_string(winsize.y));
}

float WindowHandel::GetDeltaT()
{
    return deltaTime;
}

int WindowHandel::GetFPS()
{
    return (int)(1.f / deltaTime);
}

glm::vec2 WindowHandel::GetScreenSize()
{
    return glm::vec2((float)winsize.x,(float)winsize.y);
}

uint32_t WindowHandel::GetApiClint()
{
    return api;
}
