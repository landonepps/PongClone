#include "paddle.h"

//using namespace std;

Paddle::Paddle()
{
}

Paddle::Paddle(double x1, double y1)
{
	x = x1;
	y = y1;
}

Paddle::~Paddle()
{
}

void Paddle::setX(double x1)
{
	x = x1;
}

void Paddle::setY(double y1)
{
	y = y1;
}

void Paddle::setXY(double x1, double y1)
{
	x = x1;
	y = y1;
}

double Paddle::getX()
{
	return x;
}

double Paddle::getY()
{
	return y;
}
