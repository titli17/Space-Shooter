# Space-Shooter

## **Introduction:**

In this project we have created a simple Space Shooting game using C++ language and raylib library. Raylib is a simple and easy-to-use library to enjoy videogames programming and it's especially well suited for prototyping, tooling, graphical applications, embedded systems and education.

**The goal is to protect the spaceship from being destroyed by the alien invaders while shooting them down to earn points. As the game progresses, the aliens descend closer, increasing the challenge. From time to time a mystery ship appears, and the player can hit it to earn more points! The player has only 3 lives.**

Every game structure consists of 2 parts : DEFINITIONS and GAME LOOP.

**DEFINITIONS** is the part where we define our variables and game objects such as the spaceship, aliens, lasers, obstacles and the gaming arena. 
<br>The **GAME LOOP** is responsible for event handling, updating the positions of game objects and checking for collisions. The updates happen so fast that it appears like a continuous movement. The GAME LOOP is run repeatedly until the game is closed. 

We make this game by breaking it down into smaller parts.

## **Step 1: Creating Blank Canvas and Game Loop**

The game window is like a blank canvas where we can draw our game objects.
<br>We need to specify the width and the height of the game window. To create the game window we call the InitWindow() function. This function initialises a window.

Everytime we create a window, at some point we have to destroy it, and we do so with the CloseWindow() function before the return statement. It checks if the Escape key on the keyboard is pressed or if the close icon of the window is pressed, and returns true if that is the case. So, if it returns true, the game loop ends, and the window is destroyed.

**GAME LOOP**
<br>The game loop consists of 3 parts:
<br>**Event handling:** First, we check for any events that occur in the game, such as
quitting the game, a key pressed on the keyboard, etc. 
<br>**Updating positions:** Next, we update the positions of all game objects, such as the spaceship, aliens, lasers, etc. 
<br>**Drawing objects:** Finally, we draw all the game objects in their new positions on the screen. 

In the GAME LOOP, we need BeginDrawing function which creates a blank canvas so we can draw our game objects on and the EndDrawing() function which ends the canvas drawing.

Next we define how fast the game should run by calling the SetTargetFPS() function before the game loop. This function takes an integer as an argument and that integer is the number of frames per second that we want. If we don’t define a frame rate for our game, the computer will try to run the game as fast as it can. So the game speed will depend on the speed of the computer. By defining a frame rate we make sure that the game runs at the same speed on every computer.


## **Step 2: Creating the Spaceship**

We separately create a Spaceship class using a header file and an implementation file. This helps in better organisation and abstraction of the code.
<br>The header file (usually with a .h extension) contains the class declaration, including the class name, member variables, and function prototypes. It serves as an interface for other parts of the program to use the class.
<br>The implementation file (usually with a .cpp extension) contains the actual implementation of the class functions. This is where the member functions defined in the header file are implemented. 

The basic methods in our Spaceship class are Draw(), MoveLeft(), MoveRight(), FireLaser().

We use a Vector2 variable to hold the position of the Spaceship object. Vector2 is a data structure that contains x and y attribute.

To load an image for the Spaceship object, we need to use the LoadImage() function. This function takes a string argument that represents the path to the image file. The loaded image is used to create a texture using the LoadTextureFromImage() function.
The spaceship appears on the screen when the Draw() method is called.
<br>A destructor is also created to unload the texture when the object is destroyed.

Initially the Spaceship object is placed at the bottom centre of the gaming area.


## **Step 3: Creating the Game Class**

To improve code organization and make it easier to manage in the future, we create a Game class separately to hold the spaceship, alien, obstacle objects, as well as various methods. The Game class serves as a container for all the elements of our game such as the spaceship, aliens, game state. It holds methods that manage the game's logic such as updating the position of the game objects, checking for collisions, updating the score, handling input etc. 


## **Step 4: Moving the Spaceship**

To move the spaceship we change its position in the x axis by 7 pixels in the MoveLeft() and MoveRight() functions. This movement is limited within the gaming arena. The player can move the spaceship to the right by pressing "->" key and to move to the left, "<-" key must be pressed.

We add keyboard controls to the game class to control its movement.

![image](https://github.com/user-attachments/assets/30eb1d73-652f-4625-b103-b61292a6b328)


## **Step 5: Creating the Lasers**

Both the spaceship and the aliens have the ability to shoot lasers. The aliens shoot green lasers and the spaceship shoots blue lasers. When the player presses the spacebar key, the spaceship shoots lasers.

We separately create a Laser class. The lasers are represented as a rectangle. So we draw them using the DrawRectangle() function of raylib library in the Draw() method.
<br>The laser objects are initialized in the constructor with a position and speed.
The Update() method is responsible for the movement of the laser objects. The y position is only altered within the gaming arena.
If we want to move the laser up, we provide a negative value to the speed argument and to move the laser down, we provide a positive one. 
<br>To destroy every laser object that moves out of the game window, we add a state to the laser objects, i.e. they can be either active or inactive. If it is inactive, it is destroyed using the DeleteInactiveLasers() method in the Game class. The inactive lasers are erased.


## **Step 6: Adding the Laser Shooting Ability to the Spaceship**

We create a vector which will contain all the lasers that the spaceship shoots. FireLaser() method is called when the player presses the spacebar key on the keyboard. On calling this method, a laser object will be created and added to the vector of lasers. 

This method contains the position of the laser object and speed as it's arguments. The speed will be negative for the spaceship. The position of the lasers will be the center of the spaceship. 

We use a range based for loop to call the Draw() and Update() methods for every laser object.

Next, we add delay so that the player cannot shoot a laser before a certain amount of time has passed. In the Spaceship class, we use a timer to keep track of when the last laser is fired using GetTime() function and storing the time in a variable, i.e. lastFiredTime.


## **Step 7: Creating the Obstacles**

The obstacles are for the aliens. They act as shields for the spaceship. There are 4 protective barriers under which the player's spaceship can hide to avoid alien lasers.
They display damage when hit by the alien's lasers.

We create a Block class separately. Each object is initialised with it's position in the constructor using Vector2 variable. The Draw() method draws a blue block using DrawRectangle() function.

Then we separately create an Obstacle class. The obstacle is representated as a collection of blue blocks carefully arranged to give a desired shape. It is an ivisible grid consisting of 13 rows and 23 columns, totaling 299 cells. This grid is a vector of vectors. Each cell can be either empty or it can contain a blue block of 3x3 pixels. To make a cell blue, we set its value to 1. If we want an empty cell, we assign it a value of 0.

![image](https://github.com/user-attachments/assets/ccb62d17-9fe0-45fa-8f08-b8edd6a6d4a0)

We create a blocks vector which will contain all the blocks created.

We iterate through all the cells in the grid and create a new block only when we find the value 1 in a cell. After creating the blue blocks, we add them to the blocks vector. The Draw() method draws all the blocks inside the blocks vector.

Now, when a laser hits a cell, we only change it's cell value to 0 to simulate damage.

In the Game class, we create a obstacles vector to hold the 4 obstacle objects. The 4 obstacle objects are created using CreateObstacles() method. This method returns the vector of obstacles.

![image](https://github.com/user-attachments/assets/7f884950-53b0-4a10-9ecf-f5ad7f6f5b33)

Finally to draw these 4 obstacles, we use a range based for loop in the Draw() method of the Game class.


## **Step 8: Creating the Aliens**

Our game has 5 rows and 11 columns of aliens. All of the aliens move collectively either to the left or right, occasionally firing lasers. When they reach the edge of the game window, they shift slightly downward, progressively increasing the game's challenge.

We create an Alien class separately. There are 3 different types pf aliens. So each alien has a type that is used to display a different image for each type. Every alien is given a type and position initialised using the constructor. We load the image of the alien depending on the type. 

![image](https://github.com/user-attachments/assets/5ddec423-5c1e-4b11-a01e-bf106c579f0e)

Here, we create a static attribute named alienImages which is an array of 3 elements. It is initialized only once and contains all 3 alien images. So, the first time an Alien object is created, it loads the images in this attribute, and then each new alien object uses these images at once. It won’t load them again. This saves time.

We will use the DrawTextureV() function in the Draw() method to draw the image on the specified position on the screen. 

Next, we create a vector named aliens in the game class that hold all the aliens and CreateAliens() method to create all the aliens returning a vector with all the aliens.

![image](https://github.com/user-attachments/assets/84835449-b52c-4af5-a523-27cebea2f137)

Next we unload the images when the game window is closed using the UnloadImages() method in the Alien class. We call this method in the destructor of the Game class.

To move the aliens, we add or remove some pixels from the current position. In the Game class, we create the MoveALiens() and MoveDownAliens() methods. 
<br>We invoke the Update() method of the alien class and provide it with a direction parameter to move the aliens sideways. The x coordinate is changed in MoveAliens() method.
<br>To move the aliens down, we add some pixels to the y coordinate of the aliens' position. The MoveDownAliens() method is called whenever the aliens hit the end of the screen.
 

## **Step 9: Adding the Laser Shooting Ability to the Aliens**

We create a vector to hold all the alien lasers in the Game class. The AlienShootLaser() method selects a random alien and shoots a laser from it. The GetRandomValue() function is used with a of range 0 to 2 to get a random alien type. Then, we create a laser for that alien and store it in the vector. A positive integer is passed as speed for the laser as it will move downwards.
<br>Finally we call the Update() and the Draw() method for the alien lasers in the Game class.

To make the aliens shoot lasers at a slower rate, we use a timer to keep track of when the last laser is fired using GetTime() function and store the time in a variable, i.e. timeLastAlienFired. If the time interval between current time and last fired time exceeds a certain value, a new laser is fired by the alien. 
<br>The inactive alien lasers are deleted just like the spaceship lasers.


## **Step 10: Creating the Mystery Cat Ship**

The mystery cat ship is another alien ship that appears at the top of the screen from time to time and moves horizontally, either to the left or to the right. Unlike the regular alien ships, this unique alien ship doesn't shoot lasers. However, players have the opportunity to earn extra points by killing it. This mystery ship can be killed using 5 lasers.

We create a Cat class separately. A single object of this class is created and displayed from time to time. Multiple objects are not created. This is implemented using the Spawn() method. In the constructor, we load the image of the cat and set the alive attribute to false. Using the Draw() method we draw the image when the alive attribute is true. To spawn the ship at random intervals of time, we call the Spawn() method in the Game class's Update() method using the GetTime() and GenerateRandomValue() functions.
<br>The ship can spawn from either side of the screen. So the random starting point is generated using GetRandomValue() function with a range of 0 to 1. 0 represents the left side and 1 represents the right side. 

![image](https://github.com/user-attachments/assets/b93c79c5-f930-4c6e-95b0-486996435f89)

To move the ship, we use the Update() method. The x coordinate of it's position is added with the speed.


## **Step 11: Checking for Collisions**

Raylib provides the CheckCollisionRecs() function, which determines if two rectangles collide.
Since all our game elements are not rectangle, getRect() method is used which returns a rectangle object. This rectangle is matched to the dimensions of the object's image and positioned accordingly. The x and y position of the object along with the image width and height are passed as arguments to the getRect() method.

The collision checking is done in the Game class.
<br>First, we check every laser beam the spaceship shoots. If it collides with any of the 3 aliens, we erase that alien. If 5 lasers hit the cat ship, the alive attribute of the cat is set to false. After the lasers collide, their active attribute is set to false. If all the aliens are hit, we call the CreateAliens() method again.

Next, we check every laser beam the aliens shoot. If it collides with the spaceship for 3 times, then GameOver! If it collides with the blocks of the obstacles, the blocks are erased. After the lasers collide, their active attribute is set to false.

Finally, we check if the aliens collide with the obstacles or the spaceship or the bottom line of the gaming area. If the aliens collide with the blocks of the obstacles, the respective blocks are erased. If the aliens collide with the spaceship or the bottom line of the gaming arena, then again GameOver!


## **Step 12: Game Over**

This method is called when 3 lives of the spaceship are over or the aliens collide with the spaceship or the bottom line of the gaming arena. We add a new attribute named run in the Game class. This attribute has value True if the game is running and False if the game is over. So in the GameOver() method the run attribute is set to false.


## **Step 13: Reset and Initialise the Game again**

These 2 methods of the Game class are called when the player presses the ENTER key of the keybard. 
All the aliens, the alien lasers and the obstacles are cleared in the Reset() method.
A Reset() method is added in the Spaceship class where the spaceship object is set to its original position and all it's lasers are cleared. This method is called in the Reset() method of the Game class.

We create InitGame() method to initialise all the variables of the game elements to their initial values. So in the constructor of the Game class we only call the InitGame() method.

![image](https://github.com/user-attachments/assets/894a52cc-1b2b-430d-9858-37bc436efdad)


## **Step 14: Adding Score and High Score**

The next step is to add scoring to the game and display it on the screen. The player gets 100 points when he hits an alien of type 1, 200 points when he hits an alien of type 2, 300 points when he hits an alien of type 3 and 500 points when he hits the mystery cat ship.

We add a score attribute to the Game class and initialize it to 0. We update the score value whenever there is a collision between the spaceship's laser and an alien or mystery cat ship.

Finally in the Shooter Game.cpp file, we display the score text and the score value.

![image](https://github.com/user-attachments/assets/8e411ad2-ca13-45ab-b885-b05d8bd783b9)

Next, we add a highscore attribute to the Game class and initialize this attribute in the InitGame() method. Whenever the score of the player increases, we check if it is a new highscore. If it is, we copy the score value to the highscore value and save it in a text file. For this we create 3 methods in the Game class: checkForHighscore(), saveHighscoreToFile() and loadHighscoreFromFile().

The saveHighscoreToFile() takes an integer as an argument and saves it to a text file.

![image](https://github.com/user-attachments/assets/92a15292-5b24-4be8-837e-eea6be11be1f)

The ofstream line creates an instance of the output file stream class named highscoreFile and associates it with the file named "highscore.txt." This stream is intended for writing data to the file. If the file already exists, its contents will be cleared, and if it doesn't exist, a new file will be created. 

<br>The loadHighscoreFromFile() reads the text file and returns the score it is saved in it.

![image](https://github.com/user-attachments/assets/a957b2fa-b63f-48ac-92ef-3838eaa50d4c)

The ifstream line of code in C++ initializes an input file stream object named highscoreFile to read from the file named "highscore.txt."

Finally in the Shooter Game.cpp file, we display the highscore text and the highscore value and our game is complete.

![image](https://github.com/user-attachments/assets/6f0440f0-ced0-4fb2-95fe-2eeaf6cfa195)



