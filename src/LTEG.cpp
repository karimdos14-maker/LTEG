#include "LTEG.h"
#include <vector>
#include <iostream>
#include <memory>
#include <conio.h>

struct NewChunk
{
	std::size_t newX;
	std::size_t newY;
	std::size_t newZ;
};
std::vector<std::unique_ptr<NewChunk>> chunks;
void LTEG::generateChunk()
{
	auto newChunk = std::make_unique<NewChunk>();
	std::size_t currC = chunks.size();
	newChunk->newX = 0;
	newChunk->newY = 64;
	newChunk->newZ = 0;
	char keyBindChunk = 'F';
	if (_kbhit())
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
void LTEG::deleteChunk()
{
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
			char key = _getch();
			if (key == exit)
			{
				isEngine = false;
			}
		}
	}
	return -1;
}