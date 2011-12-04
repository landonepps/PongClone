#include <iostream>
#include <string>
#include <sstream>
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

		Block blocks[9][9];
		Plotter plot;
		static int lives;
		int blockNumber;
	public:
		Level(int levelNumber);
		~Level();
		void setPuck(Puck);
		void setPaddle(Paddle);
		void setBlock(Block);
		void setLives(int);

		int getBlockNum();
		Puck getPuck();
		double getPuckX();
		double getPuckY();
		Paddle getPaddle();
		double getPaddleX();
		double getPaddleY();
		int getBlockX(int a, int b);
		int getBlockY(int a, int b);
		void setPuck(int x, int y);
		void setPuckMXY(double x, double y);
		void setPaddle(int x, int y);
		void setBlockX(int a, int b, int x);
		void setBlockY(int a, int b, int y);
		int getLives();
		//drawLevel is used to output our level file.
		void drawLevel(istream &levelFile);
		void clearScreen();
		//We can either use startLevel to display the splash screen
		//and keep the game running until endLevel is called.
		void startLevel(istream &splashFile, ostream &outStream);
		void pauseGame( int );

		//paddle functions
		void moveLeft();
		void moveRight();

		//puck functions
		void updatePuck();
		void reversePuck( bool, bool );

		//plotter control
		void removeBlock(int blockX, int blockY);
		void removePaddlePuck();
		void printText(string text);
		void clearText();
};