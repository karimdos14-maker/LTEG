#include "LTEG.h"
#include <vector>
#include <iostream>
#include <memory>
#include <conio.h>
char keyBindChunk = 'F';
char keyBindObject = 'S';
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
	char keyNow = _getch();
	auto newChunk = std::make_unique<NewChunk>();
	std::size_t currC = chunks.size();
	newChunk->newX = 0;
	newChunk->newY = 64;
	newChunk->newZ = 0;
	if (_kbhit())
	{
		if (keyNow == keyBindObject)
		{
			char keyNow = _getch();
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
	}
}
void LTEG::deleteChunk()
{
	if (chunks.size() > 5)
	{
		chunks.erase(chunks.begin());
	}
}
int LTEG::newObject()
{
	auto newObject = std::make_unique<NewObject>();
	if (_kbhit())
	{
		char keyNow = _getch();
		if (keyNow == keyBindObject)
		{
			newObject->size_X = 1;
			newObject->size_Y = 1;
			newObject->size_Z = 1;
			newObject->collectionObject.push_back(1);
			std::cout << "object create";
		}
	};
	return 0;
}
int LTEG::engineCycle()
{
	char exit = 'q';
	bool isEngine = true;
	while (isEngine)
	{
		if (_kbhit())
		{
			LTEG::generateChunk();
			LTEG::deleteChunk();
			LTEG::newObject();
			char key = _getch();
			if (key == exit)
			{
				isEngine = false;
			}
		}
	}
	return -1;
}