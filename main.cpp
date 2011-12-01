#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <stdexcept>
#include <Windows.h>
#include <MMSystem.h>
#include "level.h"

#pragma comment(lib, "Winmm.lib")

using namespace std;

void cls( HANDLE hConsole );
//The total number of levels
const int MAXLEVEL=1;
//The console size
const unsigned width = 80, height = 30;

int main ()
{
	HANDLE hCon;
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

	PlaySound("./launch.wav", NULL, SND_FILENAME | SND_ASYNC);
	char choice;
	ifstream menuFile;
	string str;
	menuFile.open("menu.txt");
	
	do
	{
		cls(hCon);
		while(getline(menuFile, str))
		{
			cout << str << endl;
		}
		choice = _getch();
		if(choice == 's' || choice == 'S')
		{
			for (int levelNum=1; levelNum<=MAXLEVEL; levelNum++)
			{
				//Create a new level and tell it which number it is
				Level level(levelNum);

				level.clearScreen();

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

				//starts level/displays splashscreen
				level.startLevel(splashFile, cout);

				//wait for user to press a button
				_getch();

				//clears splash so we can draw the level
				level.clearScreen();
		
				//gives the level the level file
				level.drawLevel(levelFile);

				//the main game loop
				char c;
				while (level.getLives() > 0)
				{
					//paddle
					if(c = _getch_nolock())
					{
						switch(c)
						{
							case 75: //left
								level.moveLeft();
								break;
							case 77: //right
								level.moveRight();
								break;
						}
					}

				Paddle thePaddle = level.getPaddle();
				/*for (int i = 0; i < 100; i++)
				{
					if( thePaddle.getX() ==  )
					{
					}

				}*/
				}

				_getch();

				level.clearScreen();
			}
		}
		else if(choice == 'a' || choice == 'A')
		{
			cls(hCon); //clears menu
			ifstream aboutFile;
			string Astr;
			aboutFile.open("about.txt");
			while(getline(aboutFile, Astr))
			{
				cout << Astr << endl;
			}
			_getch();
		}
	}while(choice != 'q' && choice != 'Q');

	return 0;
}

void cls( HANDLE hConsole )
{
  COORD coordScreen = { 0, 0 };    // here's where we'll home the cursor

  DWORD cCharsWritten;
  CONSOLE_SCREEN_BUFFER_INFO csbi; // to get buffer info 
  DWORD dwConSize;                 // number of character cells in the current buffer 

  // get the number of character cells in the current buffer 

  GetConsoleScreenBufferInfo( hConsole, &csbi );
  dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

  // fill the entire screen with blanks 

  FillConsoleOutputCharacter( hConsole, (TCHAR) ' ', dwConSize, coordScreen, &cCharsWritten );

  // get the current text attribute 

  GetConsoleScreenBufferInfo( hConsole, &csbi );

  // now set the buffer's attributes accordingly 

  FillConsoleOutputAttribute( hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten );

  // put the cursor at (0, 0) 

  SetConsoleCursorPosition( hConsole, coordScreen );
 
  return;
}
