using namespace std;
#include <iostream>
#include "paddle.h"

//using namespace std;

Paddle::Paddle()
{
}

Paddle::Paddle(int x1, int y1)
{
	x = x1;
	y = y1;
}

Paddle::~Paddle()
{
}

void Paddle::setX(int x1)
{
	x = x1;
}

void Paddle::setY(int y1)
{
	y = y1;
}

void Paddle::setXY(int x1, int y1)
{
	x = x1;
	y = y1;
}

int Paddle::getX()
{
	return x;
}

int Paddle::getY()
{
	return y;
}


