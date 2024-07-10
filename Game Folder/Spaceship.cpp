//This is the implementation file...contains the actual implementation of the class functions and member variables
//Used for better organization of code and abstraction

#include "Spaceship.h"

Spaceship::Spaceship()
{
	img = LoadImage("sp.png");
	image = LoadTextureFromImage(img);
	UnloadImage(img);
	position.x = (GetScreenWidth() - image.width) / 2;
	position.y = GetScreenHeight()-117;
	lastFiredTime = 0.0;
}

Spaceship::~Spaceship()
{
	UnloadTexture(image);
}

void Spaceship::Draw()
{
	DrawTextureV(image, position, WHITE);
}

void Spaceship::MoveLeft()
{
	if (position.x >= 75)
		position.x -= 7;
}

void Spaceship::MoveRight()
{
	if (position.x <= GetScreenWidth() - image.width - 75)
		position.x += 7;
}

void Spaceship::FireLaser()			//this function will be called when user presses Spacebar
{
	if (GetTime() - lastFiredTime > 0.25)
	{
		lasers.push_back(Laser({ position.x + image.width / 2 - 2, position.y - 12 }, -6));
		lastFiredTime = GetTime();
	}
}

Rectangle Spaceship::getRect()
{
	return { position.x,position.y, float(image.width),float(image.height) };
}

void Spaceship::Reset()
{
	position.x = (GetScreenWidth() - image.width) / 2;
	position.y = GetScreenHeight() - 117;
	lasers.clear();
}


