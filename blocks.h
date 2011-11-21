#include <iostream>
#include <string>
using namespace std;

class Puck
{
	private:
		double x, y, mx, my;
	public:
		Puck();
		Puck(double, double, double, double);
		~Puck();
		void setX(double);
		void setY(double);
		void setMX(double);
		void setMY(double);
		double getX();
		double getY();
		double getMX();
		double getMY();
		string toString();
};