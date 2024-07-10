#include "Cat.h"

Cat::Cat()
{
	image = LoadTexture("ALIEN.png");
	alive = false;
	count = 5;
}

Cat::~Cat()
{
	UnloadTexture(image);
}

void Cat::Spawn()
{
	position.y = 85;
	int side = GetRandomValue(0, 1);
	if (side == 0)
	{
		position.x = 75;
		speed = 1;
	}
	else
	{
		position.x = GetScreenWidth() - 75 - image.width;
		speed = -1;
	}
	alive = true;
}

Rectangle Cat::getRect()
{
	if (alive)
	{
		return { position.x, position.y, float(image.width),float(image.height) };
	}
	else
		return { position.x,position.y,0,0 };
}

void Cat::Update()
{
	if (alive) 
	{
		position.x += speed;
		if (position.x > GetScreenWidth() - 75 - image.width || position.x < 75)
		{
			alive = false;
			count = 5;
		}
	}
}

void Cat::Draw()
{
	if (alive)
	{
		DrawTextureV(image, position, WHITE);
	}
}


