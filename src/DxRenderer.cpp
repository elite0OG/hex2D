#include<GLFW/glfw3.h>
#include"DxRenderer.h"
#include<stb_image.h>
#include <imgui.h>                // Core ImGui functions
#include<imgui_impl_dx11.h>
#include<imgui_impl_glfw.h>
namespace wrl = Microsoft::WRL;
namespace dx = DirectX;
void DxRenderer::init(WindowHandel& handel) {
    h = handel;

    // Creating vertex array
    //0.5f, 0.5f, 0.0f,  // top right
    //    0.5f, -0.5f, 0.0f,  // bottom right
    //    -0.5f, -0.5f, 0.0f,  // bottom left
    //    -0.5f, 0.5f, 0.0f   // top left 
    Vertex vertices[] = {
        {0.5f, 0.5f  ,1.f , 0.f, 0.f},
        {0.5f, -0.5f  ,0.f , 1.f, 0.f},
        {-0.5f, -0.5f ,0.f , 0.f, 1.f},
        { -0.5f, 0.5f ,0.f , 0.f, 1.f }
    };
	unsigned int indices[] = { 1, 2, 3,0, 1, 3 };
    // Buffer description
    D3D11_BUFFER_DESC bd = {};
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(vertices);
    bd.StructureByteStride = sizeof(Vertex);

    wrl::ComPtr<ID3D11Buffer> pVertexBuffer;

    // Subresource data
    D3D11_SUBRESOURCE_DATA sd = {};
    sd.pSysMem = vertices;

    // Create vertex buffer
    HRESULT hr = h.pDevice->CreateBuffer(&bd, &sd, &pVertexBuffer);
    if (FAILED(hr)) {
        Hlog(LOG_ERROR, "Failed to create vertex buffer. HRESULT: 0x%08X");
        return;
    }

    // Bind vertex buffer
    const UINT stride = sizeof(Vertex);
    const UINT offset = 0u;
    h.pContext->IASetVertexBuffers(0u, 1u, pVertexBuffer.GetAddressOf(), &stride, &offset);
    // index buffer
	D3D11_BUFFER_DESC ibd = {};
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.Usage = D3D11_USAGE_DEFAULT;
	ibd.ByteWidth = sizeof(indices);
	ibd.StructureByteStride = sizeof(unsigned int);

	wrl::ComPtr<ID3D11Buffer> pIndexBuffer;
	D3D11_SUBRESOURCE_DATA isd = {};
	isd.pSysMem = indices;
	hr = h.pDevice->CreateBuffer(&ibd, &isd, &pIndexBuffer);
	if (FAILED(hr)) {
		Hlog(LOG_ERROR, "Failed to create index buffer. HRESULT: 0x%08X");
		return;
	}
	h.pContext->IASetIndexBuffer(pIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0u);
    // 
    // constant buffer
    // 
    cb = {
    dx::XMMatrixTranspose(dx::XMMatrixIdentity()),
    dx::XMMatrixTranspose(
        dx::XMMatrixOrthographicOffCenterLH(0.f, h.GetScreenSize().x, h.GetScreenSize().y, 0.f, -1.f, 1.f)
    )// (left, right, bottom, top, near, far)
    };

	
	
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.Usage = D3D11_USAGE_DYNAMIC;
	cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbd.ByteWidth = sizeof(cb);
	cbd.StructureByteStride = 0u;
	
	csd.pSysMem = &cb;
	hr = h.pDevice->CreateBuffer(&cbd, &csd, &pConstantBuffer);
	if (FAILED(hr)) {
		Hlog(LOG_ERROR, "Failed to create constant buffer. HRESULT: 0x%08X");
		return;
	}
	h.pContext->VSSetConstantBuffers(0u, 1u, pConstantBuffer.GetAddressOf());
   
    wrl::ComPtr<ID3D11VertexShader> pVertexShader;
    wrl::ComPtr<ID3DBlob> pBlob;
    // Create and bind pixel shader
    wrl::ComPtr<ID3D11PixelShader> pPixelShader;
    hr = D3DReadFileToBlob(L"def_frag.cso", &pBlob);
    if (FAILED(hr)) {
        Hlog(LOG_ERROR, "Failed to read pixel shader file. HRESULT: 0x%08X");
        return;
    }

    hr = h.pDevice->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPixelShader);
    if (FAILED(hr)) {
        Hlog(LOG_ERROR, "Failed to create pixel shader. HRESULT: 0x%08X");
        return;
    }

    h.pContext->PSSetShader(pPixelShader.Get(), nullptr, 0u);
    // Reset pBlob before loading pixel shader
    pBlob.Reset();
    // Create and bind vertex shader
    hr = D3DReadFileToBlob(L"def_vert.cso", &pBlob);
    if (FAILED(hr)) {
        Hlog(LOG_ERROR, "Failed to read vertex shader file. HRESULT: 0x%08X");
        return;
    }

    hr = h.pDevice->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pVertexShader);
    if (FAILED(hr)) {
        Hlog(LOG_ERROR, "Failed to create vertex shader. HRESULT: 0x%08X");
        return;
    }

    h.pContext->VSSetShader(pVertexShader.Get(), nullptr, 0u);

    //input layout
    wrl::ComPtr<ID3D11InputLayout> pInputLayout;
    const D3D11_INPUT_ELEMENT_DESC ied[] = {
        {"Position", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "Color", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 8u, D3D11_INPUT_PER_VERTEX_DATA, 0 }
    };
    hr = h.pDevice->CreateInputLayout(ied, (UINT)std::size(ied), pBlob->GetBufferPointer(), pBlob->GetBufferSize(), &pInputLayout);
	if (FAILED(hr)) {
		Hlog(LOG_ERROR, "Failed to create input layout. HRESULT: 0x%08X");
		return;
    }
    else {
        Hlog(LOG_INFO, "Input layout created successfully. That means-");
        Hlog(LOG_INFO,"vertex and fragment shaders are loaded successfuly form 'Resourece/Shader/*.hlsl'"); }
	h.pContext->IASetInputLayout(pInputLayout.Get());

 
    // Bind the render target
    
    h.pContext->OMSetRenderTargets(1, h.pTarget.GetAddressOf(), nullptr);
	// set primitive topology
	h.pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//configuring the viewport
	D3D11_VIEWPORT vp;
	vp.Width = h.GetScreenSize().x;
	vp.Height = h.GetScreenSize().y;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	h.pContext->RSSetViewports(1u, &vp);

 
    //IMGUI
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls

    // Setup ImGui for DirectX 11 and Win32
   
    // Setup ImGui for DirectX 11 and GLFW
    ImGui_ImplGlfw_InitForOther(h.GetHandel(), true);
    ImGui_ImplDX11_Init(h.pDevice.Get(), h.pContext.Get());

    if (!ImGui::GetCurrentContext()) {
        Hlog(LOG_ERROR, "ImGui context is null! Initialization failed.");
        return;
    }

}

void DxRenderer::ShutDown()
{
}

void DxRenderer::DrawTriangle(glm::vec3 pos, glm::vec4 color)
{
	DxRenderer::cb.transform = dx::XMMatrixTranspose(
		dx::XMMatrixScaling(100.f, -100.f, 1.f) // Flip Y-axis scale
		* dx::XMMatrixTranslation(pos.x, pos.y, pos.z)
	);
    DxRenderer::cb.uColor = dx::XMVectorSet(color.x, color.y, color.z, color.w);
	load_PVM();
    h.pContext->DrawIndexed(3,0,0);
}

void DxRenderer::DrawQuad(glm::vec3 pos, glm::vec4 color)
{
    
	
    DxRenderer::cb.transform = dx::XMMatrixTranspose(
        dx::XMMatrixScaling(100.f, -100.f, 1.f) // Flip Y-axis scale
        *dx::XMMatrixTranslation(pos.x, pos.y, pos.z)
    );
	DxRenderer::cb.uColor = dx::XMVectorSet(color.x, color.y, color.z, color.w);

	DxRenderer::load_PVM();
    h.pContext->DrawIndexed(6, 0, 0);
}

void DxRenderer::DrawTriangleV(glm::vec3 pos, glm::vec2 size, glm::vec2 RotationAngle, float angle, glm::vec4 color)
{
    if(angle == 0.0  ){
        DxRenderer::cb.transform = dx::XMMatrixTranspose(
            dx::XMMatrixScaling(size.x, -size.y, 1.f) // Flip Y-axis scale      
 * dx::XMMatrixTranslation(pos.x, pos.y, pos.z)
        );
	}
	else { Hlog(LOG_WARN, "RotationAngle and angle must be 0.0f for DrawTriangleV()"); }
    DxRenderer::cb.uColor = dx::XMVectorSet(color.x, color.y, color.z, color.w);

    load_PVM();
    h.pContext->DrawIndexed(3, 0, 0);
}

void DxRenderer::DrawQuadV(glm::vec3 pos, glm::vec2 size, glm::vec2 RotationAngle, float angle, glm::vec4 color)
{
    if (angle == 0.0) {
        DxRenderer::cb.transform = dx::XMMatrixTranspose(
            dx::XMMatrixScaling(size.x, -size.y, 1.f) // Flip Y-axis scale      
            * dx::XMMatrixTranslation(pos.x, pos.y, pos.z)
        );
    }
    else { Hlog(LOG_WARN, "RotationAngle and angle must be 0.0f for DrawTriangleV()"); }
    DxRenderer::cb.uColor = dx::XMVectorSet(color.x, color.y, color.z, color.w);

    load_PVM();
    h.pContext->DrawIndexed(6, 0, 0);
}

void DxRenderer::DrawImguiText(const char* text, glm::vec2 pos, float fontS)
{
    ImGui::SetNextWindowPos(ImVec2(pos.x, pos.y), ImGuiCond_Always);  // Top-left corner
    //ImGui::SetWindowFontScale(fontS);
    ImGui::SetNextWindowBgAlpha(0.f);
    ImGui::Begin(text, nullptr,
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_AlwaysAutoResize |
        ImGuiWindowFlags_NoFocusOnAppearing |
        ImGuiWindowFlags_NoBackground |
        ImGuiWindowFlags_NoNav);
    ImGui::Text(text);
    ImGui::End();
}

void DxRenderer::load_PVM()
{
    
    h.pDevice->CreateBuffer(&cbd, &csd, &pConstantBuffer);
    h.pContext->VSSetConstantBuffers(0u, 1u, pConstantBuffer.GetAddressOf());
}

void DxRenderer::ClearBackground(glm::vec4 color)
{
    Color[0] = color.x / 255.f;
    Color[1] = color.y / 255.f;
    Color[2] = color.z / 255.f;
    Color[3] = color.w / 255.f;
    h.pContext->ClearRenderTargetView(h.pTarget.Get(), Color);
    //h.pContext->ClearDepthStencilView(h.pDepthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void DxRenderer::beginDrawing()
{
	glfwPollEvents();
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplGlfw_NewFrame();   
    ImGui::NewFrame();

}

void DxRenderer::endDrawing()
{
    h.pContext->OMSetBlendState(nullptr, nullptr, 0xFFFFFFFF);

    ImGui::Render();
    h.pContext->OMSetRenderTargets(1, h.pTarget.GetAddressOf(), nullptr);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    
       
        if(v)
        {
             hr = h.pSwap->Present(1u, 0u);
            if (FAILED(hr)) {
                Hlog(LOG_ERROR, "Swap chain Present() failed!");
            }
        }
        else
        {
            hr = h.pSwap->Present(0u, 0u);
            if (FAILED(hr)) {
                Hlog(LOG_ERROR, "Swap chain Present() failed!");
            }
        }
    
}
