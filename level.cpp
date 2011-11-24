#include "level.h"

using namespace std;

Level::Level()
{
}

Level::Level(Puck, Paddle, Block)
{
}

Level::~Level()
{
}

void Level::setPuck(Puck)
{
}
	
void Level::setPaddle(Paddle)
{
}
void Level::setBlock(Block)
{
}

//setLevel is used to read in our level file.
void Level::setLevel(istream)
{
}

Puck Level::getPuck()
{
}

Paddle Level::getPaddle()
{
}

Block Level::getBlock()
{
}

//drawLevel is used to output our level file.
string drawLevel()
{
}

void runLevel()
{
}

//We can either use startLevel to display the splash screen
//and keep the game running until endLevel is called.
string startLevel()
{
}

string endLevel()
{
}

//Or we can do both in nextLevel which will start the next
//level depending if all blocks are destroyed and end when 
//all blocks are destroyed.
string Level::nextLevel()
{
}
