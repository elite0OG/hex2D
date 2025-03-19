#pragma once
//the include GLRenderer.h give the Dx11 renderer same definations and includes that it need to work 
#include"GLRenderer.h"
#include"WindowHandel.h"
class DxGLRenderer
{
public:
    void init(WindowHandel& handle); // Fixed spelling

    void ShutDown();

    void DrawTriangle(glm::vec3 pos, glm::vec4 color);
    void DrawQuad(glm::vec3 pos, glm::vec4 color);
    void DrawTriangleV(glm::vec3 pos, glm::vec2 size, glm::vec2 RotationAngle, float angle, glm::vec4 color);
    void DrawQuadV(glm::vec3 pos, glm::vec2 size, glm::vec2 RotationAngle, float angle, glm::vec4 color);

    void load_PVM();

    void ClearBackground(glm::vec4 color);
    void beginDrawing();
    void endDrawing();

private:
    WindowHandel h; // Ensure WindowHandel is properly defined
    float Color[4];
};
