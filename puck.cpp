#include <string>
#include <sstream>
#include "puck.h"

using namespace std;

Puck::Puck()
{
	x = 10;
	y = 10;
	mx = 1;
	my = -1;
}
Puck::Puck(double x1, double y1, double mx1, double my1)
{
	x = x1;
	y = y1;
	mx = mx1;
	my = my1;
}
Puck::~Puck()
{
}
void Puck::setX(double x1)
{
	x = x1;
}
void Puck::setY(double y1)
{
	y = y1;
}
void Puck::setMX(double mx1)
{
	mx = mx1;
}
void Puck::setMY(double my1)
{
	my = my1;
}
void Puck::setXY(double x1, double y1)
{
	x = x1;
	y = y1;
}
double Puck::getX()
{
	return x;
}
double Puck::getY()
{
	return y;
}
double Puck::getMX()
{
	return mx;
}
double Puck::getMY()
{
	return my;
}
string Puck::toString()
{
		ostringstream result;
		result << "x: " << x << endl;
		result << "y: " << y << endl;
		result << "mx: " << mx << endl;
		result << "my: " << my << endl;
  
		return result.str();
}

void Puck::movePuck()
{	
	x += mx;
	y += my;
}

