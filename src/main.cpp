#include <iostream>
#include "LTEG.h"
#include <GLFW/glfw3.h>

int main()
{
	LTEG lteg;
	if (!glfwInit())
	{
		return -1;
	}
	GLFWwindow *window =
		glfwCreateWindow(1920, 1080, "LTEG", nullptr, nullptr);

	if (!window)
		return -1;

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		lteg.engineCycle(window);
	}
	glfwDestroyWindow(window);
	glfwTerminate();
}