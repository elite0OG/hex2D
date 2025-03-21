#include"PhysicsSys.h"

bool phy::CheckCollisionRec(glm::vec2 posA, glm::vec2 sizeA, glm::vec2 posB, glm::vec2 sizeB)
{
    return (posA.x < posB.x + sizeB.x &&
        posA.x + sizeA.x > posB.x &&
        posA.y < posB.y + sizeB.y &&
        posA.y + sizeA.y > posB.y);
}
