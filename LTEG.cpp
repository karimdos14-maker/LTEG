#include "LTEG.h"
#include <vector>
#include <iostream>
struct NewChunk {
		int newX;
		int newY;
		int newZ;
	};
	struct Chunk {
		bool limitChunk;
		bool chunkGenerate;
		bool chunkDelete;
		std::vector<std::vector<int>> chunkVec;
		int X;
		int Y;
		int Z;
	};
void LTEG::viewChecker() {
	bool plView = false;
	Chunk chunk;
	if (plView) {
		chunk.chunkGenerate = true;
	}
	if (plView != true) {
		chunk.chunkDelete = true;
	}
}
void LTEG::generateChunk() {
		Chunk chunk;
		for (int fcyc = 0; fcyc < 11; fcyc++)
		{
 			for (int fcycc = 0; fcycc < 11; fcycc++)
			{
                  chunk.chunkVec.push_back({0,0});
			}
		};
		for (int X = 0; X < chunk.chunkVec.size(); X++){
			for (int x = 0; x < chunk.chunkVec[X].size(); x++){
				std::cout << chunk.chunkVec[X][x] << ' ';
			}
			std::cout << '\n';
		}
}
void LTEG::gameCycle(){
	char Exit;
	do {
		LTEG::viewChecker();
		LTEG::generateChunk();
        std::cin >> Exit;
	}
	while (Exit != 'q' && Exit != 'Q');
}