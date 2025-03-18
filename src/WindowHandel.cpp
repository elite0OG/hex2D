#include"renderer.h"

void WindowHandel::setParas()
{

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}
void WindowHandel::init(int width, int height, const char* title)
{
    winsize = glm::vec2((float)width, (float)height);

    log(LOG_INFO, "USING H2R RENDERER BY hex");
    if (!glfwInit())
    {
        log(LOG_ERROR, "GLFW initialization failed!");
         
    }
    else { log(LOG_INFO, "GLFW loaded successfully!"); }
    setParas();
	window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window)
    {
        log(LOG_WARN, "Window creation failed!");
        glfwTerminate();  
    }
    else { log(LOG_INFO, "window created successfully!"); }

    glfwMakeContextCurrent(window);

    glewExperimental = true;

    if (glewInit() != GLEW_OK)
    {
        log(LOG_ERROR, "GLEW initialization failed!");
    }
    else { log(LOG_INFO, "GLEW loaded successfully!"); }

}

void WindowHandel::ShutDown()
{
    log(LOG_INFO, "Window closed successfully");
    glfwDestroyWindow(window);
    glfwTerminate();
}