#include <iostream>
#include <fstream>
#include <sstream>
#include "level.h"

using namespace std;

//The total number of levels
const int MAXLEVEL=1;

int main ()
{
	for (int levelNum=1; levelNum<=MAXLEVEL; levelNum++)
	{
		//Create a new level and tell it which number it is
		Level level(levelNum);

		//opens the level file
		//naming convention is level<levelNumber>.txt
		ifstream levelFile;
		stringstream levelFileName;
		levelFileName << "level" << levelNum << ".txt";
		levelFile.open( levelFileName.str().c_str() );
		if (!levelFile)
		{
			cout << "Error opening splash screen file\n";
			return 1;
		}

		//gives the level the level file
		level.setLevel(levelFile);

		//opens the splashscreen file
		//naming convention is splash<levelNumber>.txt
		ifstream splashFile;
		stringstream splashFileName;
		splashFileName << "splash" << levelNum << ".txt";
		splashFile.open( splashFileName.str().c_str() );
		if (!splashFile)
		{
			cout << "Error opening splash screen file\n";
			return 1;
		}

		//starts level
		level.startLevel(splashFile);
	}
	return 0;
}
