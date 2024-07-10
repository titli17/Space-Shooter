//Implementation file of game header file

#include "Game.h"
#include <iostream>
#include <fstream>

using namespace std;

Game::Game()
{
	InitGame();
}

Game::~Game()
{
	Alien::UnloadImages();
}

void Game::Update()
{
	if (run)
	{
		for (auto& laser : spaceship.lasers)
		{
			laser.Update();
		}

		MoveAliens();
		AlienShootLaser();
		for (auto& laser : alienLasers)
		{
			laser.Update();
		}

		DeleteInactiveLasers();

		double currentTime = GetTime();
		if (currentTime - timeLastSpawn > catAlienSpawnInterval)
		{
			catAlien.Spawn();
			timeLastSpawn = GetTime();
			catAlienSpawnInterval = GetRandomValue(10, 20);
		}

		catAlien.Update();

		CheckForCollisions();

		if (t == false)
		{
			aliens = CreateAliens();
			t = true;
		}

	}
	
}

void Game::Draw()
{
	spaceship.Draw();

	for (auto& laser : spaceship.lasers)
	{
		laser.Draw(BLUE);
	}

	for (auto& obstacle : obstacles)
	{
		obstacle.Draw();
	}

	for (auto& alien : aliens)
	{
		alien.Draw();
	}

	for (auto& laser : alienLasers)
	{
		laser.Draw(GREEN);
	}

	catAlien.Draw();
}

void Game::HandleInput()
{
	if (run)
	{
		if (IsKeyDown(KEY_LEFT))
		{
			spaceship.MoveLeft();
		}
		else if (IsKeyDown(KEY_RIGHT))
		{
			spaceship.MoveRight();
		}
		else if (IsKeyDown(KEY_SPACE))
		{
			spaceship.FireLaser();
		}
	}
	else
	{
		if (IsKeyDown(KEY_ENTER))
		{
			Reset();
			InitGame();
		}

	}
}

void Game::DeleteInactiveLasers()
{
	for (auto it = spaceship.lasers.begin(); it != spaceship.lasers.end(); )			//'it' is the iterator of the vector lasers
	{
		if (!it->active)
		{
			it = spaceship.lasers.erase(it);      //if laser is inactive the it will be erased
		}
		else
		{
			++it;							//if active then 'it' will move to next laser 
		}
	}

	for (auto it = alienLasers.begin(); it != alienLasers.end(); )			//'it' is the iterator of the vector lasers
	{
		if (!it->active)
		{
			it = alienLasers.erase(it);      //if laser is inactive the it will be erased
		}
		else
		{
			++it;							//if active then 'it' will move to next laser 
		}
	}
}

vector<Obstacle> Game::CreateObstacles()
{
	int obstaclewidth = Obstacle::grid[0].size() * 3;
	float gap = (750 - (4 * obstaclewidth))/5;

	for (int i = 0; i < 4; i++)
	{
		float offsetX = ((i + 1) * gap + i * obstaclewidth) + 75;    //this +75 is de to offset of game window
		obstacles.push_back(Obstacle({offsetX,(float)GetScreenHeight()-200}));
	}
	return obstacles;
}

vector<Alien> Game::CreateAliens()
{
	vector<Alien> aliens;
	for (int row = 0; row < 5; row ++ )
	{
		for (int column = 0; column < 11; column++)
		{
			int alienType;
			if (row == 0)
			{
				alienType = 3;
			}
			else if (row == 1 || row == 2)
			{
				alienType = 2;
			}
			else
			{
				alienType = 1;
			}

			float x = 150 + column * 55;
			float y = 160 + row * 45;
			aliens.push_back(Alien(alienType,{x,y}));
		}
	}
	return aliens;
}

void Game::MoveAliens()
{
	for (auto& alien : aliens)
	{
		if (alien.position.x + alien.alienImages[alien.type - 1].width > GetScreenWidth() - 75)
		{
			aliensDirection = -1;
			MoveDownAliens(4);
		}
		else if (alien.position.x < 75)
		{
			aliensDirection = 1;
			MoveDownAliens(4);
		}
		alien.Update(aliensDirection);
	}
}

void Game::MoveDownAliens(int distance)
{
	for (auto& alien : aliens)
	{
		alien.position.y += distance;
	}
}

void Game::AlienShootLaser()
{
	double currentTime = GetTime();
	if (currentTime - timeLastAlienFired >= alienLaserShootInterval && !aliens.empty())
	{
		int randomIndex = GetRandomValue(0, aliens.size() - 1);
		Alien& alien = aliens[randomIndex];
		alienLasers.push_back(Laser({ alien.position.x + alien.alienImages[alien.type - 1].width / 2 ,
									  alien.position.y + alien.alienImages[alien.type - 1].height }, 6));

		timeLastAlienFired = GetTime();
	}
}

void Game::CheckForCollisions()
{
	//Spaceship Lasers :
	for (auto& laser : spaceship.lasers)
	{
		auto it = aliens.begin();
		while (it != aliens.end())
		{
			if (CheckCollisionRecs(it->getRect(), laser.getRect()))
			{
				if (it->type == 1)
				{
					score += 100;
				}
				else if (it->type == 2)
				{
					score += 200;
				}
				else if (it->type == 3)
				{
					score += 300;
				}
				checkForHighscore(score);

				it = aliens.erase(it);
				laser.active = false;
			}
			else
				++it;
			if (aliens.size() == 0)
			{
				t = false;
				level++;
			}
		}

		if (CheckCollisionRecs(laser.getRect(), catAlien.getRect()))
		{
			laser.active = false;
			catAlien.count--;
			if (catAlien.count == 0 )
			{
				catAlien.alive = false;
				score += 500;
				catAlien.count = 5;
			}
			checkForHighscore(score);
		}
	}

	//Alien Lasers:
	for (auto& laser : alienLasers)
	{
		if (CheckCollisionRecs(laser.getRect(), spaceship.getRect()))
		{
			laser.active = false;
			lives--;
			if (lives == 0)
			{
				GameOver();
			}

		}
		for (auto& obstacle : obstacles)
		{
			auto it = obstacle.blocks.begin();
			while (it != obstacle.blocks.end())
			{
				if (CheckCollisionRecs(it->getRect(), laser.getRect()))
				{
					it = obstacle.blocks.erase(it);
					laser.active = false;
				}
				else
					++it;
			}
		}
	}

	//ALiens colliding with obstacles or spaceship or bottom line
	for (auto& alien : aliens)
	{
		for (auto& obstacle : obstacles)
		{
			auto it = obstacle.blocks.begin();
			while (it != obstacle.blocks.end())
			{
				if (CheckCollisionRecs(it->getRect(), alien.getRect()))
				{
					it = obstacle.blocks.erase(it);
				}
				else
					it++;
			}
		}
		if (CheckCollisionRecs(alien.getRect(), spaceship.getRect()))
		{
			GameOver();
		}
		if (CheckCollisionRecs(alien.getRect(), getRect()))
		{
			GameOver();
		}
	}

}

void Game::GameOver()
{
	run = false;
}

void Game::Reset()
{
	spaceship.Reset();
	aliens.clear();
	alienLasers.clear();
	obstacles.clear();
}

void Game::InitGame()
{
	run = true;
	score = 0;
	highscore = loadHighscoreFromFile();
	lives = 3;
	level = 1;

	obstacles = CreateObstacles();

	aliens = CreateAliens();
	aliensDirection = 1;
	timeLastAlienFired = 0.0;

	timeLastSpawn = 0.0;
	catAlienSpawnInterval = GetRandomValue(10, 20);

	t = true;
}

void Game::checkForHighscore( int sc)
{
	if (sc > highscore)
	{
		highscore = sc;
		saveHighscoreToFile(highscore);
	}
}

void Game::saveHighscoreToFile(int highscore)
{
	ofstream highscoreFile("highscore.txt");
	if (highscoreFile.is_open())
	{
		highscoreFile << highscore;
		highscoreFile.close();
	}
	else
	{
		cerr << "Failed to save highscore" << endl;
	}
}

int Game::loadHighscoreFromFile()
{
	int loadedHighscore = 0;
	ifstream highscoreFile("highscore.txt");
	if (highscoreFile.is_open())
	{
		highscoreFile >> loadedHighscore;
		highscoreFile.close();
	}
	else
	{
		cerr << "Failed to load highscore from file" << endl;
	}

	return loadedHighscore;
}

Rectangle Game::getRect()
{
	return { 75,775,750,1 };
}



