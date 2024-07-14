#pragma once
#include <raylib.h>

class Alien
{
public:
	Alien(int type, Vector2 position);
	void Update(int direction);
	void Draw();
	int GetType();
	static Texture2D alienImages[3];    //an array of 3 texture2D elements created so that we dont have to load image from disk eveytime  
												//we create an alien
	static void UnloadImages();
	int type;
	Vector2 position;

	Rectangle getRect();
private:

};

