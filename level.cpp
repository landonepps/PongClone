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
	//color bg
	for (int i = 0; i < 80; i++)
	{
		for (int j = 0; j < 30; j++)
		{
			plot.setColor(cyan);
			plot.plot(i, j, SQUARE);
		}
	}

	//draw walls
	for (int i = 0; i < 29; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (levelNum <= 3)
			{
				plot.setColor(darkgreen);
			}
			else
			{
				plot.setColor(red);
			}
			plot.plot(j,i, SQUARE);
		}
	}

	for (int i = 0; i < 29; i++)
	{
		for (int j = 78; j < 80; j++)
		{
			if (levelNum <= 3)
			{
				plot.setColor(darkgreen);
			}
			else
			{
				plot.setColor(red);
			}
			plot.plot(j,i, SQUARE);
		}
	}




	//draw blocks
	Block blocks[9][9];

	char blockFile[9][9];

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			blockFile[i][j] = levelFile.get();
		}
		levelFile.ignore();
	}

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if ( blockFile[j][i] == '1' )
			{
				double blockX = ( 4 + ( i * 8 ) );
				double blockY = ( j * 2 );
				blocks[i][j].setXY(blockX, blockY ) ;

				for (int q = 1; q <= 7; q++)
				{
					plot.setColor(darkred);
					plot.plot((int)blockX + q, (int)blockY, SQUARE);
				}
				
			}
		}
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
