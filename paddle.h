#ifndef PADDLE_H
#define PADDLE_H
#include <iostream>
using namespace std;

class Paddle
{
	private:
		int x, y;
	public:
		Paddle();
		Paddle(int, int);
		~Paddle();

		void setX(int);
		void setY(int);
		void setXY(int, int);
		int getX();
		int getY();

};

#endif
