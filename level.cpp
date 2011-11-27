#include "level.h"

using namespace std;

Level::Level(int levelNumber)
{
	levelNum = levelNumber;
}

Level::Level(Puck puck1, Paddle paddle1, Block block1, int levelNumber)
{
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

//setLevel is used to read in our level file.
void Level::setLevel(istream &levelFile)
{
	//
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
void Level::drawLevel()
{
	
}

void Level::runLevel()
{

}

//We can either use startLevel to display the splash screen
//and keep the game running until endLevel is called.
void Level::startLevel(istream &splashFile)
{
	//
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
