#include <iostream>
#include <string>
#include <fstream>
#include "puck.h"
#include "paddle.h"
#include "block.h"
#include "plotter.h"

using namespace std;

class Level
{
	private:
		bool isRunning;
		int levelNum;
		Puck puck;
		Paddle paddle;
		Block block;
		Plotter plot;
		static int lives;
	public:
		Level(int levelNumber);
		~Level();
		void setPuck(Puck);
		void setPaddle(Paddle);
		void setBlock(Block);
		void setLives(int);

		Puck getPuck();
		double getPuckX();
		Paddle getPaddle();
		Block getBlock();
		int getLives();
		//drawLevel is used to output our level file.
		void drawLevel(istream &levelFile);
		void runLevel();
		void clearScreen();
		//We can either use startLevel to display the splash screen
		//and keep the game running until endLevel is called.
		void startLevel(istream &splashFile, ostream &outStream);
		void endLevel();
		//Or we can do both in nextLevel which will start the next
		//level depending if all blocks are destroyed and end when 
		//all blocks are destroyed.
		void nextLevel();

		//paddle functions
		void moveLeft();
		void moveRight();

};
