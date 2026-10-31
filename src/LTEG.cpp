#include "LTEG.h"
#include <vector>
#include <iostream>
#include <memory>

#include <conio.h>
struct NewChunk
{
	int newX;
	int newY;
	int newZ;
};
struct Chunk
{
	bool limitChunk;
	bool chunkGenerate;
	bool chunkDelete;
	int X;
	int Y;
	int Z;
};
std::vector<std::unique_ptr<NewChunk>> chunks;
void LTEG::generateChunk()
{
	auto newChunk = std::make_unique<NewChunk>();
	newChunk->newX = 0;
	newChunk->newY = 0;
	newChunk->newZ = 0;
	if (!chunks.empty())
	{
		newChunk->newX++;
		newChunk->newY++;
		newChunk->newZ++;
		std::cout << "His Coordinate: X =  " << newChunk->newX << "Y =  " << newChunk->newY << "Z =  " << newChunk->newZ << '\n';
	}
	std::cout << "Chunk Generate" << '\n';
	std::cout << "His Coordinate: X =  " << newChunk->newX << "Y =  " << newChunk->newY << "Z =  " << newChunk->newZ << '\n';
	chunks.push_back(std::move(newChunk));
	std::cout << "Chunks" << chunks.size() << '\n';
}
void LTEG::deleteChunk()
{

	if (!chunks.empty())
	{
		chunks.pop_back();
	}
}

void LTEG::viewChecker()
{
	bool plview = true;
	if (plview == true)
	{
		LTEG::generateChunk();
	}
}
void LTEG::gameCycle()
{
	char exit = 'q';
	bool isEngine = true;
	while (isEngine)
	{
		if (_kbhit())
		{
			LTEG::generateChunk();
			LTEG::viewChecker();
			char key = _getch();
			if (key == exit)
			{
				isEngine = false;
			}
		}
	}
}