#include "level.h"

using namespace std;

const int SCREENLENGTH = 60;

Level::Level(int levelNumber)
{
	isRunning = false;
	levelNum = levelNumber;
}

Level::Level(Puck puck1, Paddle paddle1, Block block1, int levelNumber)
{
	isRunning = false;
	puck = puck1;
	paddle = paddle1;
	block = block1;
	levelNum = levelNumber;
}

Level::~Level()
{
}

void Level::setPuck(Puck puck1)
{
	puck = puck1;
}
	
void Level::setPaddle(Paddle paddle1)
{
	paddle = paddle1;
}

void Level::setBlock(Block block1)
{
	block = block1;
}

Puck Level::getPuck()
{
	return puck;
}

Paddle Level::getPaddle()
{
	return paddle;
}

Block Level::getBlock()
{
	return block;
}

//drawLevel is used to output our level file.
void Level::drawLevel(istream &levelFile)
{
	int ifBlock;
	while(levelFile >> ifBlock)
	{

	}
}

void Level::runLevel()
{

}

void Level::clearScreen()
{
	plot.clear();
}

//We can either use startLevel to display the splash screen
//and keep the game running until endLevel is called.
void Level::startLevel(istream &splashFile, ostream &outStream)
{
	isRunning = true;
	string tempString;
	while (getline(splashFile, tempString))
	{
		outStream << tempString << endl;
	}
}

void Level::endLevel()
{

}

//Or we can do both in nextLevel which will start the next
//level depending if all blocks are destroyed and end when 
//all blocks are destroyed.
void Level::nextLevel()
{

}
