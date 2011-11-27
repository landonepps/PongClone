#ifndef BLOCK_H
#define BLOCK_H

class Block
{
private:
	double x, y;
public:
	Block();
	Block(double, double);
	~Block();
	void setX(double);
	void setY(double);
	double getX();
	double getY();
};

#endif
