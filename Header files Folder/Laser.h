#pragma once
#include <raylib.h>

class Laser
{
public:
	Laser(Vector2 position, int speed);
	void Update();
	void Draw(Color color);
	bool active;	//to check if laser has gone beyond our gaming screen 

	Rectangle getRect();

private:
	Vector2 position;
	int speed;
};

