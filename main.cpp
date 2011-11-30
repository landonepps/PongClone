#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <stdexcept>
#include <Windows.h>
#include <MMSystem.h>
#include "level.h"

#pragma comment(lib,"Winmm.lib")

using namespace std;

//The total number of levels
const int MAXLEVEL=1;
const unsigned width = 79, height = 30;

struct console
  {
	console( unsigned width, unsigned height )
    {	
		HANDLE hCon;
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		SMALL_RECT rect;
		COORD      c;
		hCon = GetStdHandle( STD_OUTPUT_HANDLE );

		rect.Left   = 0;
		rect.Top    = 0;
		rect.Right  = width -1;
		rect.Bottom = height -1;
		SetConsoleWindowInfo( hCon, TRUE, &rect );

		c.X = width;
		c.Y = height;
		SetConsoleScreenBufferSize( hCon, c );
	}

	~console()
	{
    }
  };

console con(80, 30);

int main ()
{
	PlaySound("./launch.wav", NULL, SND_FILENAME | SND_ASYNC);
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
		level.startLevel(splashFile, cout);

		_getch();
		level.clearScreen();
		//gives the level the level file
		level.drawLevel(levelFile);

		_getch();

		level.clearScreen();
	}
	return 0;
}
