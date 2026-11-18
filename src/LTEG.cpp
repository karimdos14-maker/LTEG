#include "LTEG.h"
#include <vector>
#include <iostream>
#include <memory>
#include <thread>
#include <chrono>

struct Object
{
	int size_X;
	int size_Y;
	int size_Z;
	int settingsObject[3];
	std::vector<int> collectionObject;
};
struct Chunk
{
	std::size_t X;
	std::size_t Y;
	std::size_t Z;
};
std::vector<int> id;
int nextID = 1;
std::vector<std::unique_ptr<Chunk>> chunks;
std::vector<std::unique_ptr<Object>> objs;

void LTEG::generateChunk()
{
	auto chunkp = std::make_unique<Chunk>();
	std::size_t currC = chunks.size();
	chunkp->X = 0;
	chunkp->Y = 64;
	chunkp->Z = 0;
	std::cout << "Chunks " << chunks.size() << '\n';
	chunkp->X = currC * 16;
	chunkp->Z = currC * 16;
	std::cout << "Chunk Generate" << '\n';
	std::cout << "His Coordinate:" << '\n';
	std::cout << "X =  " << chunkp->X << '\n';
	std::cout << "Y =  " << chunkp->Y << '\n';
	std::cout << "Z =  " << chunkp->Z << '\n';
	chunks.push_back(std::move(chunkp));
	std::cout << "Chunks " << chunks.size() << '\n';
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
}
void LTEG::deleteChunk()
{
	if (chunks.size() > 5)
	{
		chunks.erase(chunks.begin());
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
}
void LTEG::addObject()
{

	auto Obj = std::make_unique<Object>();
	Obj->size_X = 1;
	Obj->size_Y = 1;
	Obj->size_Z = 1;
	Obj->collectionObject.push_back(1);

	std::cout << "object create with ID: " << nextID << "\n";

	objs.push_back(std::move(Obj));
	id.push_back(nextID);

	nextID++;
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
}
bool LTEG::objectposition()
{
	int objposition[3] = {0, 0, 0};
	bool def_position = true;

	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	return true;
}
int LTEG::engineCycle(GLFWwindow *window)
{
	while (!glfwWindowShouldClose(window))
	{

		glfwPollEvents();

		if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
		{
			generateChunk();
		}

		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			addObject();
		}
		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		}
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		{
			deleteChunk();
		}
		glfwSwapBuffers(window);
	}

	return 0;
}
