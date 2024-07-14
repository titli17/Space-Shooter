//This is the header file...contains the class declaration including class name, member variables and function prototypes
//It serves as an interface for other parts of the program to use the class

#pragma once               //this line is written so that this header file is included only once in a compilational unit to avoid duplication definitions
#include <raylib.h>
#include "laser.h"
#include <vector>

using namespace std;

class Spaceship
{
public:
	Spaceship();
	~Spaceship();
	void Draw();
	void MoveLeft();
	void MoveRight();
	void FireLaser();
	Rectangle getRect();			//for checking collisions
	vector<Laser> lasers;   //vector is just like array....lasers is a vector of type Laser which will contain the laser 

	void Reset();

private:
	Image img;
	Texture2D image;
	Vector2 position;      //Vector2 is a datatype representing a 2D point or vector with x and y components

	double lastFiredTime;
};

