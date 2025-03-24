#pragma once
//the include GLRenderer.h give the Dx11 renderer same definations and includes that it need to work 
#define WIN32_LEAN_AND_MEAN 
#include"GLRenderer.h"
#include"WindowHandel.h"
#include"logger.h"
 

class DxRenderer
{
public:
    void init(WindowHandel& handle); // Fixed spelling

    void ShutDown();

    void DrawTriangle(glm::vec3 pos, glm::vec4 color);
    void DrawQuad(glm::vec3 pos, glm::vec4 color);
    void DrawTriangleV(glm::vec3 pos, glm::vec2 size, glm::vec2 RotationAngle, float angle, glm::vec4 color);
    void DrawQuadV(glm::vec3 pos, glm::vec2 size, glm::vec2 RotationAngle, float angle, glm::vec4 color);
    void DrawImguiText(const char* text, glm::vec2 pos, float fontS);
    void load_PVM();
    bool v = true;
    void ClearBackground(glm::vec4 color);
    void beginDrawing();
    void endDrawing();
  

private:
    HRESULT hr;
    WindowHandel h; // Ensure WindowHandel is properly defined
    float Color[4] = {0.f,0.f,0.f,0.f};
  
    struct Vertex
    {
        float x;
        float y;

        float r;
        float g;
		float b;
    };
	struct ConstantBuffer
	{
		DirectX::XMMATRIX transform;
        DirectX::XMMATRIX orth;
		DirectX::XMVECTOR uColor;
	};
    ConstantBuffer cb;
    wrl::ComPtr<ID3D11Buffer> pConstantBuffer;
    D3D11_BUFFER_DESC cbd = {};
    D3D11_SUBRESOURCE_DATA csd = {};
   // std::array<Vertex, 3> vertices;
};
