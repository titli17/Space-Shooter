//It will serve as a container for all the elements of our game (spaceship, obstacles, aliens, game state)
//Code will be easier to unserstand, maintain and expand. Reduced risk of bugs.

#pragma once
#include "Spaceship.h"
#include "Obstacle.h"
#include "Alien.h"
#include "Cat.h"

using namespace std;

class Game
{
public:
	Game();
	~Game();
	void Draw();
	void Update();
	void HandleInput();			//it will contain all the inputs that user will give from keyboard like moving left or right and shooting lasers
	bool run;		// to check if game is running or not
	int lives;		//for spaceship

	int score;
	int highscore;

	int level;

private:
	Spaceship spaceship;

	void DeleteInactiveLasers();

	vector<Obstacle> obstacles;
	vector<Obstacle> CreateObstacles();
	vector<Alien> aliens;

	vector<Alien> CreateAliens();
	void MoveAliens();
	int aliensDirection;
	void MoveDownAliens(int distance);
	vector<Laser> alienLasers;
	void AlienShootLaser(); 
	constexpr static float alienLaserShootInterval = 0.35;   //constant expression is used so that the variable can be initialised in the header
	float timeLastAlienFired;								//file ...it will initialised at compilation time;	

	Cat catAlien;
	float catAlienSpawnInterval;
	float timeLastSpawn;

	void CheckForCollisions();

	void GameOver();
	void Reset();
	void InitGame();

	void checkForHighscore(int sc);
	void saveHighscoreToFile(int highscore);
	int loadHighscoreFromFile();

	bool t;			// for respawning of aliens

	Rectangle getRect();		//for getting the bottom collision with aliens


};

