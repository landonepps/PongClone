#include "block.h"

Block::Block()
{

}

Block::Block(double x1, double y1)
{
	x = x1;
	y = y1;
}

Block::~Block()
{
	//
}

void Block::setX(double num)
{
	x = num;
}

void Block::setY(double num)
{
	y = num;
}

double Block::getX()
{
	return x;
}

double Block::getY()
{
	return y;
}