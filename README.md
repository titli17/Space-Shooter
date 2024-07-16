# Space-Shooter

## **Introduction:**

In this project we have created a simple Space Shooting game using C++ language and raylib library. raylib is a simple and easy-to-use library to enjoy videogames programming and it's especially well suited for prototyping, tooling, graphical applications, embedded systems and education.

**The goal is to protect the spaceship from being destroyed by the alien invaders while shooting them down to earn points. As the game progresses, the aliens descend closer, increasing the challenge. From time to time a mystery ship appears, and the player can hit it to earn more points! The player has only 3 lives.**

Every game structure consists of 2 parts : DEFINITIONS and GAME LOOP.

**DEFINITIONS** is the part where we define our variables and game objects such as the spaceship, aliens, lasers, obstacles and the gaming arena. 
<br>The **GAME LOOP** is responsible for event handling, updating the positions of game objects and checking for collisions. The updates happen so fast that it appears like a continuous movement. The GAME LOOP is run repeatedly until the game is closed. 

We made this game by breaking it down into smaller parts.

## **Step 1: Creating Blank Canvas and Game Loop**

The game window is like a blank canvas where we can draw our game objects.
<br>We need to specify the width and the height of the game window. To create the game window we have to call the InitWindow() function. This function initialises a window.

Everytime we create a window, at some point we have to destroy it, and we do so with the CloseWindow() function before the return statement. It checks if the Escape key on the keyboard is pressed or if the close icon of the window is pressed, and returns true if that is the case. So, if it returns true, the game loop ends, and the window is destroyed.

**GAME LOOP**
<br>The game loop consists of 3 parts. 
<br>**Event handling:** First, we check for any events that occur in the game, such as
quitting the game, a key pressed on the keyboard, etc. 
<br>**Updating positions:** Next, we update the positions of all game objects, such as the spaceship, aliens, lasers, etc. 
<br>**Drawing objects:** Finally, we draw all the game objects in their new positions on the screen. 

In the GAME LOOP, we need BeginDrawing function which creates a blank canvas so we can draw our game objects on and the EndDrawing() function which ends the canvas drawing.

Next we define how fast the game should run by calling the SetTargetFPS function before the game loop. The SetTargetFPS() function takes an integer as an argument and that integer is the number of frames per second that we want. If we don’t define a frame rate for our game, the computer will try to run the game as fast as it can. So the game speed will depend on the speed of the computer. By defining a frame rate we make sure that the game runs at the same speed on every computer.


## **Step 2: Creating the Spaceship**

We separately create a Spaceship class using a header file and an implementation file. This will help in better organisation and abstraction of the code.
<br>The header file (usually with a .h extension) contains the class declaration, including the class name, member variables, and function prototypes. It serves as an interface for other parts of the program to use the class.
<br>The implementation file (usually with a .cpp extension) contains the actual implementation of the class functions. This is where the member functions defined in the header file are implemented. 

The basic methods in our Sapceship class are Draw(), MoveLeft(), MoveRight(), FireLaser().

We use a Vector2 variable to hold the position of the Sapceship object. Vector2 is a data structure that contains x and y attribute.

To load an image for the spaceship object, we need to use the LoadImage() function. This function takes a string argument that represents the path to the image file. The loaded image is used to create a texture using the LoadTextureFromImage() function.
The spaceship appears on the screen when the Draw() method is called.
<br>A destructor is also created to unload the texture when the object is destroyed.

Initially the spaceship object is placed at the bottom centre of the gaming window.


## **Step 3: Creating the Game Class**

To improve code organization and make it easier to manage in the future, we create a Game class separately to hold the spaceship, alien, obstacle objects, as well as various methods. The Game class serves as a container for all the elements of our game such as the spaceship, aliens, game state. It holds methods that manage the game's logic such as updating the position of the game objects, checking for collisions, updating the score, handling input etc. 


## **Step 4: Moving the Spaceship**

To move the spaceship we change its position in the x axis by 7 pixels in the MoveLeft () and MoveRight () functions. This movement is limited within the gaming arena. The player can move the spaceship to the right by pressing "->" key and to move to the left, "<-" key must be pressed.

We add keyboard controls to the game class to control its movement.

![image](https://github.com/user-attachments/assets/30eb1d73-652f-4625-b103-b61292a6b328)


## **Step 5: Creating the Lasers**

Both the spaceship and the aliens have the ability to shoot lasers. The aliens shoot green lasers and the spaceship shoots blue lasers. When the player presses spacebar key, the spaceship will shoot lasers.

We separately create a Laser class. The lasers are represented as a rectangle. So we draw them using the DrawRectangle() function of raylib library in the Draw() method.
<br>The laser objects are initialized in the constructor with a position and speed.
The Update() method is responsible for the movement of the laser objects. The y position are only altered within the gaming arena.
If we want to move the laser up, we provide a negative value to the speed argument. If we want to move the laser down, we provide a positive one. 
<br>To destroy every laser object that moves out of the game window, we add a state to the laser objects, i.e. they can be either active or inactive. If it is inactive, it is destroyed using the DeleteInactiveLasers() method in the Game class. The inactive lasers are erased.


## **Step 6: Adding the Laser shooting Ability to the Spaceship**

We create a vector which will contain all the lasers that the spaceship shoots. FireLaser() method is called when the player presses the spacebar key on the keyboard. On calling this method, a laser object will be created and added to the vector of lasers. 

This method contains the position of the laser object and speed as it's arguments. The speed will be negative for the spaceship. The position of the lasers will be the center of the spaceship. 

We use a range based for loop to call the Draw() and Update() methods for every laser object.

Next, we add delay so that the player cannot shoot a laser before a certain amount of time has passed. In the Spaceship class, we use a timer to keep track of when the last laser is fired using GetTime() function and storing the time in a variable, i.e. lastFiredTime.


## **Step 7: Creating the Obstacles**

The obstacles are for the aliens. They act as shields for the spaceship. There are four protective barriers under which the player's spaceship can hide to avoid alien lasers.
They display damge when hit by the alien's lasers.

We create a Block class separately. Each object is initialised with it's position in the constructor using Vector2 variable. The Draw() method draws the blue block using DrawRectangle() function.

Then we separately create an Obstacle class. The obstacle is representated as collection of blue blocks carefully arranged to give a desired shape. It is anvisible grid consisting of 13 rows and 23 columns, totaling 299 cells. This grid is a vector of vectors. Each cell can be either empty or it can contain a blue block of 3x3 pixels. To make a cell blue, we set its value to 1. If we want an empty cell, we assign it a value of 0.

![image](https://github.com/user-attachments/assets/ccb62d17-9fe0-45fa-8f08-b8edd6a6d4a0)

We create a blocks vector which will contain all the blocks created.

We iterate through all the cells in the grid and create a new block only when we find the value 1 in a cell. After creating the blue blocks, we add them to the blocks vector. The Draw() method draws all the blocks inside the blocks vector.

Now, when a laser hits a cell, we only change it's cell value to 0 to simulate damage.

In the Game class, we create a obstacles vector to hold the 4 obstacle objects. The 4 obstacle objects are created using CreateObstacles() method. This method returns the vector of obstacles.

![image](https://github.com/user-attachments/assets/7f884950-53b0-4a10-9ecf-f5ad7f6f5b33)

Finally to draw these 4 obstacles, we use a range based for loop in the Draw() method of the Game class.


## **Step 8: Creating the Aliens**












