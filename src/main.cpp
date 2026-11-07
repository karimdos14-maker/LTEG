#include "LTEG.h"
#include <iostream>

int main()
{
	if (!glfwInit())
	{
		std::cout << "Failed init GLFW" << std::endl;
		return -1;
	}

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	GLFWwindow *window = glfwCreateWindow(800, 600, "LTEG", nullptr, nullptr);
	if (!window)
	{
		const char *description;
		int code = glfwGetError(&description);
		std::cout << "Failed to create window. GLFW Error (" << code << "): " << description << std::endl;
		glfwTerminate();
		return -1;
	}

	std::cout << "Window created successfully" << std::endl;

	LTEG lteg;
	lteg.engineCycle(window);

	glfwTerminate();
	return 0;
}
