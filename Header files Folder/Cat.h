#pragma once
#include <raylib.h>

class Cat
{
public:
	Cat();
	~Cat();
	void Update();
	void Draw();
	void Spawn();
	bool alive;
	int count;
	Rectangle getRect();

private:
	Vector2 position;
	Texture2D image;
	int speed;
};

