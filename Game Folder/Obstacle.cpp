#include "Obstacle.h"

using namespace std;

vector<vector<int>> Obstacle :: grid = {							//we have initialised it outside the constructor otherwise it will contain no info
		{0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0},
		{0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
		{0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
		{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1},
		{1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1},
		{1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1},
};

Obstacle::Obstacle(Vector2 position)
{
	this->position = position;

	
	for (unsigned int row = 0; row < grid.size(); ++row)
	{
		for (unsigned int column = 0; column < grid[0].size(); ++column)
		{
			if (grid[row][column] == 1)
			{
				float pos_x = position.x + column*3;    //it is multiplied by 3 bcoz each block will be 3x3 in dimensions
				float pos_y = position.y + row*3;
				Block block = Block({pos_x,pos_y});
				blocks.push_back(block);			//the blocks that are created are pushed into the blocks vector
			}
		}
	}
}

void Obstacle::Draw()
{
	for (auto& block : blocks)		//ranged for loop
	{
		block.Draw();
	}
}
