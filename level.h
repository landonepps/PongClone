#include <iostream>
#include <string>
#include "puck.h"
#include "paddle.h"
#include "block.h"
#include "plotter.h"

using namespace std;

class Level
{
	private:
		Puck puck;
		Paddle paddle;
		Block block;
		Plotter plot;
	public:
		Level();
		Level(Puck, Paddle, Block);
		~Level();

		void setPuck(Puck);
		void setPaddle(Paddle);
		void setBlock(Block);
		//setLevel is used to read in our level file.
		void setLevel(istream);

		Puck getPuck();
		Paddle getPaddle();
		Block getBlock();
		//drawLevel is used to output our level file.
		string drawLevel();
		void runLevel();
		//We can either use startLevel to display the splash screen
		//and keep the game running until endLevel is called.
		string startLevel();
		string endLevel();
		//Or we can do both in nextLevel which will start the next
		//level depending if all blocks are destroyed and end when 
		//all blocks are destroyed.
		string nextLevel();
}
