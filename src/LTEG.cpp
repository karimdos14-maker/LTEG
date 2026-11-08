#include "LTEG.h"
#include <vector>
#include <iostream>
#include <memory>
#include <GLFW/glfw3.h>
#include <thread>
#include <chrono>
struct NewObject
{
	int size_X;
	int size_Y;
	int size_Z;
	int settingsObject[3];
	std::vector<int> collectionObject;
};
struct NewChunk
{
	std::size_t newX;
	std::size_t newY;
	std::size_t newZ;
};
std::vector<std::unique_ptr<NewChunk>> chunks;
std::vector<std::unique_ptr<NewObject>> newObject;
void LTEG::generateChunk()
{

	auto newChunk = std::make_unique<NewChunk>();
	std::size_t currC = chunks.size();
	newChunk->newX = 0;
	newChunk->newY = 64;
	newChunk->newZ = 0;
	std::cout << "Chunks " << chunks.size() << '\n';
	newChunk->newX = currC * 16;
	newChunk->newZ = currC * 16;
	std::cout << "Chunk Generate" << '\n';
	std::cout << "His Coordinate:" << '\n';
	std::cout << "X =  " << newChunk->newX << '\n';
	std::cout << "Y =  " << newChunk->newY << '\n';
	std::cout << "Z =  " << newChunk->newZ << '\n';
	chunks.push_back(std::move(newChunk));
	std::cout << "Chunks " << chunks.size() << '\n';
}
void LTEG::deleteChunk()
{
	if (chunks.size() > 5)
	{
		chunks.erase(chunks.begin());
	}
}
void LTEG::addObject()
{
	auto Obj = std::make_unique<NewObject>();
	Obj->size_X = 1;
	Obj->size_Y = 1;
	Obj->size_Z = 1;
	Obj->collectionObject.push_back(1);
	std::cout << "object create\n";
	newObject.push_back(std::move(Obj));
}
int LTEG::engineCycle(GLFWwindow *window)
{
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
		{
			generateChunk();
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			addObject();
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
		return 0;
	};
	return 0;
}