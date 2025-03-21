#pragma once

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include"logger.h"


namespace phy
{
	bool CheckCollisionRec(glm::vec2 posA, glm::vec2 sizeA, glm::vec2 posB, glm::vec2 sizeB);
}
