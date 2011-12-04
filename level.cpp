#include "level.h"

using namespace std;

const int SCREENLENGTH = 60;

Level::Level(int levelNumber)
{
	isRunning = false;
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
void Level::setLives(int newLives)
{
	lives = newLives;
}
Puck Level::getPuck()
{
	return puck;
}
double Level::getPuckX()
{
	return puck.getX();
}
double Level::getPuckY()
{
	return puck.getY();
}
Paddle Level::getPaddle()
{
	return paddle;
}
double Level::getPaddleX()
{
	return paddle.getX();
}
double Level::getPaddleY()
{
	return paddle.getY();
}
void Level::setPuck(int x, int y)
{
	puck.setXY(x , y);
}
void Level::setPaddle(int x, int y)
{
	paddle.setXY(x , y);
}
int Level::getBlockX(int a, int b)
{
	return blocks[a][b].getX();
}
int Level::getBlockY(int a, int b)
{
	return blocks[a][b].getY();
}
void Level::setBlockX(int a, int b, int newBlockX)
{
	blocks[a][b].setX( newBlockX );
}
void Level::setBlockY(int a, int b, int newBlockY)
{
	blocks[a][b].setY( newBlockY );
}
int Level::getLives()
{
	return lives;
}

//We can either use startLevel to display the splash screen
//and keep the game running until endLevel is called.
void Level::startLevel(istream &splashFile, ostream &outStream)
{	
	system("color 07");

	paddle.setXY(37, 28);

	puck.setXY(40, 25);

	isRunning = true;
	string tempString;
	while (getline(splashFile, tempString))
	{
		outStream << tempString << endl;
	}
}

//drawLevel is used to output our level file.
void Level::drawLevel(istream &levelFile)
{
	if(levelNum <= 3)
	{
		system("color ba");
	}
	else
	{
		system("color ca");
	}

	//draw left wall
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
				plot.setColor(yellow);
			}
			plot.plot(j,i, SQUARE);
		}
	}

	//draw right wall
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
				plot.setColor(yellow);
			}
			plot.plot(j,i, SQUARE);
		}
	}

	//draw blocks
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

	//draw paddle
	int x = paddle.getX();
	int y = paddle.getY();

	plot.setColor(yellow);
	for (int i = 0; i < 6; i++)
	{
		plot.plot(x+i, y, SQUARE);
	}	

	//draw puck
	plot.setColor(lightgrey);

	x = puck.getX();
	y = puck.getY();

	plot.plot(x, y, SQUARE);

}

void Level::pauseGame()
{
	printText("Press Space to Continue");
	while (_getch() != ' ')
	{
	}
	clearText();
}

void Level::moveLeft()
{
		int x = paddle.getX();
		int y = paddle.getY();

		if (x > 3)
		{
			x -= 1;
			plot.setColor(yellow);
			for (int i = 0; i < 7; i++)
			{
				plot.plot(x+i, y, SQUARE);
			}
			if (levelNum <= 3)
			{
				plot.setColorSpecific(cyan);
			}
			else
			{
				plot.setColorSpecific(red);
			}
			plot.plot(x+7,y,SPACE); //Draws behind paddle
			paddle.setXY(x,y);
		}
}

void Level::moveRight()
{
		int x = paddle.getX();
		int y = paddle.getY();

		if (x < 71)
		{
			x += 1;
			plot.setColor(yellow);
			for (int i = 0; i < 7; i++)
			{
				plot.plot(x+i, y, SQUARE);
			}
			if (levelNum <= 3)
			{
				plot.setColorSpecific(cyan);
			}
			else
			{
				plot.setColorSpecific(red);
			}
			plot.plot(x-1,y,SPACE); //Draws behind paddle
			paddle.setXY(x,y);
	}
}

void Level::updatePuck()
{
	if(levelNum <= 3)
	{
		plot.setColorSpecific(cyan);
	}
	else
	{
		plot.setColorSpecific(red);
	}

	plot.plot(puck.getX(), puck.getY(), SPACE);
	puck.movePuck();
	plot.setColor(black);
	plot.plot(puck.getX(), puck.getY(), BALL);
}

void Level::reversePuck(bool x, bool y)
{
	if (x)
	{
		puck.setMX( puck.getMX() * -1 );
	}
	if (y)
	{
		puck.setMY( puck.getMY() * -1 );
	}
}

void Level::removeBlock(int blockX, int blockY)
{
	blockX = ( 4 + ( blockX * 8 ) );
	blockY = ( blockY * 2 );
	plot.setColorSpecific(cyan);
	for (int q = 1; q <= 7; q++)
	{
		plot.plot((int)blockX + q, (int)blockY, SPACE);
	}
}

void Level::removePaddlePuck()
{
	plot.setColorSpecific(cyan);
	for (int q = 0; q < 7; q++)
	{
		plot.plot((int)paddle.getX() + q, (int)paddle.getY(), SPACE);
	}
	plot.plot((int)puck.getX(), (int)puck.getY(), SPACE);
}

void Level::clearScreen()
{
	plot.clear();
}

void Level::printText(string text)
{
	plot.setColorSpecific(cyan);
	plot.move(1, 29);
	cout << text;
}

void Level::clearText()
{
	for(int i = 1; i < 79; i++)
	{
		plot.setColorSpecific(cyan);
		plot.plot(i, 29, SPACE);
	}
}

int Level::lives = 3;