#include"renderer.h"


void WindowHandel::setParas()
{

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
}
void WindowHandel::initDX(GLFWwindow* window) {
    hwnd = glfwGetWin32Window(window);
    if (!hwnd) {
        Hlog(LOG_ERROR, "Failed to get HWND from GLFW!");
        return;
    }

    DXGI_SWAP_CHAIN_DESC sd = {};
    sd.BufferCount = 1;
    sd.BufferDesc.Width = 800;
    sd.BufferDesc.Height = 600;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hwnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    sd.Flags = 0;

    Hlog(LOG_INFO, "DX SDK VERSION: " + std::to_string(D3D11_SDK_VERSION));

    HRESULT hr = D3D11CreateDeviceAndSwapChain(
        nullptr,                      // Default adapter
        D3D_DRIVER_TYPE_HARDWARE,     // Use GPU
        nullptr,                      // No software rasterizer
        D3D11_CREATE_DEVICE_DEBUG,    // Debugging mode
        nullptr,                      // Default feature levels
        0,                            // Feature level count
        D3D11_SDK_VERSION,
        &sd,
        &pSwap,
        &pDevice,
        nullptr,
        &pContext
    );

    if (FAILED(hr)) {
        Hlog(LOG_ERROR, "Failed to create Direct3D 11 Device and SwapChain! HRESULT: " + std::to_string(hr));
        pSwap = nullptr;
        pDevice = nullptr;
        pContext = nullptr;
        return;
    }
    if (!pDevice || !pContext || !pSwap) {
        Hlog(LOG_ERROR, "Direct3D objects are NULL after creation. Something went wrong!");
        return;
    }

    Hlog(LOG_INFO, "DirectX 11 initialized successfully.");
}

void WindowHandel::init(int width, int height, const char* title,uint32_t clint)
{
    winsize = glm::ivec2(width, height);
    api = clint;
    Hlog(LOG_INFO, "USING H2R RENDERER BY hex");
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
        }
    }

   else if(clint == API_DIRECTX) 
   { 
       Hlog(LOG_WARN, "Dirextx is not unavable on renderer side use GL instad!!"); 
       initDX(window);
   }
   glfwSwapInterval(1);
}

void WindowHandel::ShutDown() {
    Hlog(LOG_INFO, "Shutting down...");

    if (pContext) {
        Hlog(LOG_INFO, "Releasing pContext...");
        pContext->ClearState();
        pContext->Release();
        pContext = nullptr;
    }

    if (pSwap) {
        Hlog(LOG_INFO, "Releasing pSwap...");
        pSwap->Release();
        pSwap = nullptr;
    }

    if (pDevice) {
        Hlog(LOG_INFO, "Releasing pDevice...");
        pDevice->Release();
        pDevice = nullptr;
    }

    if (window) {
        Hlog(LOG_INFO, "Destroying GLFW window...");
        glfwDestroyWindow(window);
        window = nullptr;
    }

    Hlog(LOG_INFO, "Terminating GLFW...");
    glfwTerminate();

    Hlog(LOG_INFO, "Shutdown complete.");
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
