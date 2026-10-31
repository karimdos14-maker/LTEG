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
	chunks.push_back(std::move(newChunk));
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
	bool plview;
	if (plview)
	{
		LTEG::generateChunk();
	}
	if (!plview)
	{
		LTEG::deleteChunk();
	}
}
void LTEG::gameCycle()
{
	char exit = 'q';
	bool isGame = true;
	while (isGame)
	{
		if (_kbhit())
		{
			char key = _getch();
			if (key == exit)
			{
				isGame = false;
			}
		}
	}
}