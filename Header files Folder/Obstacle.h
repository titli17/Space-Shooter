#pragma once
#include <vector>
#include "block.h"

using namespace std;

class Obstacle
{
public:
	Obstacle(Vector2 position);
	void Draw();
	Vector2 position;
	vector<Block> blocks;			//vector of Blocks is created
	static vector<vector<int>> grid;		//this will create a 2D grid...vector of vectors...just like array of arrays to make a 2D matrix
										//to access the grid in the game.cpp file without having to create an object of the obstacle class
											// we have declared it static

private:

};

