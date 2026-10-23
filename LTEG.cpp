#include "LTEG.h"
#include <vector>
#include <iostream>
void LTEG::chunk() {
	bool plView = false;
	struct NewChunk {
		int newX;
		int newY;
		int newZ;
	};
	struct Chunk {
		bool limitChunk;
		bool chunkGenerate;
		bool chunkDelete;
		int X;
		int Y;
		int Z;
	};
	Chunk chunk;
	if (plView) {
		chunk.chunkGenerate = true;
	}
	if (plView != true) {
		chunk.chunkDelete = true;
	}
}
void LTEG::generateChunk() {
	static constexpr int SIZE = 10;
	bool blocks[SIZE][SIZE];
	int chunkX;
	int chunkZ;
	blocks[0][0] = true;
	blocks[5][5] = true;
	blocks[10][10] = true;
	for (int frcyc = 0; frcyc < SIZE; frcyc) {
		for (int frcyct = 0; frcyct < SIZE; frcyct++) {
			blocks[frcyc][frcyct] = true;
			if (blocks[chunkX][chunkZ])
			{
				std::cout << "*";
			}
		}
	}
}