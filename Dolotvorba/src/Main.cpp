#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Utils/Logger.h"

int width = 1280;
int height = 720;

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, height, "This fucking shitty window", NULL, NULL);

	if (window == 0)
	{
		Logger::log(ERROR, "HA! YOu don't have the fucking window, stupid.");

		glfwTerminate();

		return -1;
	}

	glfwMakeContextCurrent(window);

	if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == 0)
	{
		Logger::log(ERROR, "I'm not GLAD, bcs you couldn't load GLAD.");

		glfwTerminate();

		return -1;
	}

	glViewport(0, 0, width, height);

	while (glfwWindowShouldClose(window) == 0)
	{
		glClearColor(0, 0.875f, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
}