//Implementation file of laser header file..

#include "Laser.h"


Laser::Laser(Vector2 position, int speed)
{
	this->position = position;
	this->speed = speed;					//this is an object pointer containing the address of the calling object which is local to the function
	active = true;
}

void Laser::Draw(Color color)
{
	if (active)
		DrawRectangle(position.x, position.y, 4, 15, color);				//this will ensure that when laser is active then only drawing will happen
}

Rectangle Laser::getRect()
{
	Rectangle rect;
	rect.x = position.x;
	rect.y = position.y;
	rect.width = 4;
	rect.height = 15;
	return rect;
}

void Laser::Update()
{
	position.y += speed;
	if (active)
	{
		if (position.y<75 || position.y>GetScreenHeight() - 90)
		{
			active = false;
		}
	}
}