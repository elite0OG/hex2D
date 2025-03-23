#pragma once
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include"logger.h"
#include"InputHandel.h"

namespace phy
{
	bool CheckCollisionRec(glm::vec2 posA, glm::vec2 sizeA, glm::vec2 posB, glm::vec2 sizeB);
	void BasicMovement(glm::vec3& pos, float speed, float deltaT ,GLFWwindow* handel );
	int CheckScreenTopBottomCollsions(glm::vec3 pos, glm::vec2 size, glm::vec2 screenSize);
}
