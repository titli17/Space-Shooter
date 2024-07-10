#include <raylib.h>
#include "Game.h"
#include <string>

using namespace std;


int main()
{
	Color grey = { 29,29,27,255 };

	int WindowWidth = 750;
	int WindowHeight = 700;

	float offset = 75;

	InitWindow(2 * offset + WindowWidth, 2 * offset + WindowHeight, "Shooting Game");

	SetTargetFPS(60);    //takes integer as an argument...60 frames per second....game runs at the same speed on every computer

	Texture2D spaceshipImage = LoadTexture("sp1.png");

	Game game;

	while (WindowShouldClose() == false)			//WindowShouldClose checks if esc button or x button of the gaming window is pressed or not
	{
		BeginDrawing();			//creates a blank canvas on which we can draw our objects

		game.HandleInput();
		game.Update();

		ClearBackground(grey);    //window's bg is cleared with this grey color
		game.Draw();

		DrawRectangleRoundedLines({ offset - 5 , offset - 5 , (float)WindowWidth + 10, (float)WindowHeight + 10 }, 0.08f, 20, 5, YELLOW);
		DrawText("Space Shooting Game ", offset - 5, offset - 50, 30, YELLOW);


		DrawText("Lives Remaining : ", offset - 5, GetScreenHeight() - 45, 22, YELLOW);
		float x = 260;
		for (int i = 0; i < game.lives; i++)
		{
			DrawTextureV(spaceshipImage, { x,(float)GetScreenHeight() - 49 }, WHITE);
			x += 60;
		}

		if (!game.run)
		{
			DrawText("GAME OVER !", offset + 280, offset + 80, 30, YELLOW);
		}

		DrawText("Level : ", offset + 628, offset - 47, 25, YELLOW);
		DrawText(TextFormat("%i", game.level), offset + 720, offset - 47, 25, YELLOW);

		DrawText("Score : ", offset + 600, GetScreenHeight() - 55, 22, YELLOW);
		DrawText(TextFormat("%i", game.score), offset + 700, GetScreenHeight() - 55, 22, YELLOW);

		DrawText("High Score : ", offset + 547, GetScreenHeight() - 30, 22, YELLOW);
		DrawText(TextFormat("%i", game.highscore), offset + 700, GetScreenHeight() - 30, 22, YELLOW);

		EndDrawing();			//ends the canvas drawing
	}

	CloseWindow();
}