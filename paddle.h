#ifndef PADDLE_H
#define PADDLE_H

class Paddle
{
	private:
		double x, y;
	public:
		Paddle();
		Paddle(double, double);
		~Paddle();

		void setX(double);
		void setY(double);
		void setXY(double, double);
		double getX();
		double getY();
};

#endif
