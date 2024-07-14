# Space-Shooter

## **Introduction:**

In this project we have created a simple Space Shooting game using C++ language and raylib library. raylib is a simple and easy-to-use library to enjoy videogames programming and it's especially well suited for prototyping, tooling, graphical applications, embedded systems and education.

**The goal is to protect the spaceship from being destroyed by the alien invaders while shooting them down to earn points. As the game progresses, the aliens descend closer, increasing the challenge. From time to time a mystery ship appears, and the player can hit it to earn more points! The player has 3 lives.**

Every game structure consists of 2 parts : DEFINITIONS and GAME LOOP.

**DEFINITIONS** is the part where we define our variables and game objects such as the spaceship, aliens, lasers, shields and the gaming arena. 
<br>The **GAME LOOP** is responsible for event handling, updating the positions of game objects and checking for collisions. The updates happen so fast that it appears like a continuous movement. The GAME LOOP is run repeatedly until the game is closed. 

We will make this game by breaking it down into smaller parts.

## **Step 1: Creating Blank Canvas and Game Loop**

The game window is like a blank canvas where we can draw our game objects.
<br>We need to specify the width and the height of the game window. To create the game window we have to call the InitWindow() function. This function initialises a window.

Everytime we create a window, at some point we have to destroy it, and we do so with the CloseWindow() function before the return statement. It checks if the Escape key on the keyboard is pressed or if the close icon of the window is pressed, and returns true if that is the case. So, if it returns true, the game loop ends, and the window is destroyed.

**GAME LOOP**
<br>The game loop consists of 3 parts. 
<br>**Event handling:** First, we need to check for any events that occur in the game, such as
quitting the game, a key pressed on the keyboard, etc. 
<br>**Updating positions:** Next, we update the positions of all game objects, such as the spaceship, aliens, lasers, etc. 
<br>**Drawing objects:** Finally, we draw all the game objects in their new positions on the screen. 

In the GAME LOOP, we need BeginDrawing function which creates a blank canvas so we can draw our game objects on and the EndDrawing() function which ends the canvas drawing.

Next we define how fast the game should run by calling the SetTargetFPS function before the game loop. The SetTargetFPS() function takes an integer as an argument and that integer is the number of frames per second that we want. If we don’t define a frame rate for our game, the computer will try to run the game as fast as it can. So the game speed will depend on the speed of the computer. By defining a frame rate we make sure that the game runs at the same speed on every computer.


## **Step 2: Creating the Spaceship**

We have separately created a Spaceship class using a header file and an implementation file.
<br>The header file ((usually with a .h extension) contains the class declaration, including the class name, member variables, and function prototypes. It serves as an interface for other parts of the program to use the class.
<br>The implementation file (usually with a .cpp extension) contains the actual implementation of the class functions. This is where the member functions defined in the header file are implemented. 


