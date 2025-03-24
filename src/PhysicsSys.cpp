#include<GLFW/glfw3.h>
#include"PhysicsSys.h"

bool phy::CheckCollisionRec(glm::vec2 posA, glm::vec2 sizeA, glm::vec2 posB, glm::vec2 sizeB)
{
    glm::vec2 halfSizeA = sizeA * 0.5f;
    glm::vec2 halfSizeB = sizeB * 0.5f;

    return (std::abs(posA.x - posB.x) < (halfSizeA.x + halfSizeB.x) &&
        std::abs(posA.y - posB.y) < (halfSizeA.y + halfSizeB.y));
}

void phy::BasicMovement(glm::vec3& pos, float speed, float deltaT , GLFWwindow* handel)
{
    if (glfwGetKey(handel, GLFW_KEY_W) == GLFW_PRESS) pos.y -= speed*deltaT ;
    else if (glfwGetKey(handel, GLFW_KEY_S) == GLFW_PRESS) pos.y += speed*deltaT ;
    else if (glfwGetKey(handel, GLFW_KEY_A) == GLFW_PRESS) pos.x -= speed*deltaT ;
    else if (glfwGetKey(handel, GLFW_KEY_D) == GLFW_PRESS) pos.x += speed*deltaT ;
}

int phy::CheckScreenTopBottomCollsions(glm::vec3 pos, glm::vec2 size, glm::vec2 screenSize)
{
    if (pos.y - size.y /2.f<= 0 )
    {
        return 1;
    }
    else if (pos.y+ size.y/2.f >= screenSize.y)
    {
        return 2;
    }
    return 0;
}
