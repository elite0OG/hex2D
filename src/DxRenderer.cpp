#include"DxRenderer.h"

void DxGLRenderer::init(WindowHandel& handel)
{
	h = handel;
}

void DxGLRenderer::ShutDown()
{
}

void DxGLRenderer::ClearBackground(glm::vec4 color)
{
    Color[0] = color.x / 255.f;
    Color[1] = color.y / 255.f;
    Color[2] = color.z / 255.f;
    Color[3] = color.w / 255.f;
    h.pContext->ClearRenderTargetView(h.pTarget, Color);
}

void DxGLRenderer::beginDrawing()
{
	glfwPollEvents();
}

void DxGLRenderer::endDrawing()
{
    if ( h.pSwap)
    {
        HRESULT hr = h.pSwap->Present(1u, 0u);
        if (FAILED(hr)) {
            Hlog(LOG_ERROR, "Swap chain Present() failed!");
        }
    }
    else
    {
        Hlog(LOG_ERROR, "Error: pSwap is nullptr. DirectX swap chain is not initialized!");
    }
}
