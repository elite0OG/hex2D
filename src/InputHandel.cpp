#include<GLFW/glfw3.h>
#include"InputHandel.h"

bool GetKey(GLFWwindow* window, int key, int mode)
{
	return glfwGetKey(window, key) == mode;
}
