#include "Block.h"

Block::Block(Vector2 position)
{
	this->position = position;
}

void Block::Draw()
{
	DrawRectangle(position.x, position.y, 3, 3, BLUE);			//each block of the obstacle will be 3x3 in dimension
}

Rectangle Block::getRect()
{
	Rectangle rect;
	rect.x = position.x;
	rect.y = position.y;
	rect.width = 3;
	rect.height = 3;
	return rect;
}
