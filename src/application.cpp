#define DEBUG_INFO
#include"renderer.h"

WindowHandel handel;
Renderer renderer;
bool CheckCollision(glm::vec2 posA, glm::vec2 sizeA, glm::vec2 posB, glm::vec2 sizeB) {
    return (posA.x < posB.x + sizeB.x &&
        posA.x + sizeA.x > posB.x &&
        posA.y < posB.y + sizeB.y &&
        posA.y + sizeA.y > posB.y);
}
int main()
{

    handel.init(800, 600, "h2r hex");
    renderer.init(handel.GetWindowSize());
    renderer.RendererHint(DEFALT_RENDERER_TYPE, 4);
    glm::vec3 pos = glm::vec3{ 400.f,300.f,0.f };

    glm::vec2 size = glm::vec2{ 100.f,100.f };

    glm::vec3 pos2 = glm::vec3{ 500.f,300.f,0.f };

    glm::vec2 size2 = glm::vec2{ 100.f,100.f };
    float lastFrameTime = (float)glfwGetTime();
    float deltaTime = 0.0f;
    float currentTime = 0.f;
    // renderer.PrintProjection();
    while (!glfwWindowShouldClose(handel.GetHandel()))
    {
        currentTime = (float)glfwGetTime();
        deltaTime = currentTime - lastFrameTime;
        lastFrameTime = currentTime;
        if (CheckCollision(glm::vec2(pos2.x, pos2.y), size2, glm::vec2(pos.x, pos.y), size)) log(LOG_INFO, "collisions");

        if (glfwGetKey(handel.GetHandel(), GLFW_KEY_D) == GLFW_PRESS) pos.x += 400.f * deltaTime;
        else if (glfwGetKey(handel.GetHandel(), GLFW_KEY_A) == GLFW_PRESS) pos.x -= 400.f * deltaTime;
        else if (glfwGetKey(handel.GetHandel(), GLFW_KEY_W) == GLFW_PRESS) pos.y -= 400.f * deltaTime;
        else if (glfwGetKey(handel.GetHandel(), GLFW_KEY_S) == GLFW_PRESS) pos.y += 400.f * deltaTime;
       

        renderer.beginDrawing();

        renderer.ClearBackground(glm::vec4{ 100.f, 149.f, 237.f, 255.f });
        renderer.DrawQuadV(pos, size, vec2Zero, 0.f, RED);
        renderer.DrawQuadV(pos2, size2, vec2Zero, 0.f, BLUE);
        renderer.endDrawing(handel.GetHandel());
    }
    renderer.ShutDown();
    handel.ShutDown();

}
