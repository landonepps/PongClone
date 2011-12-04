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
const int MAXLEVEL = 6;
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

	//self explanitory
	PlaySound("./launch.wav", NULL, SND_FILENAME | SND_ASYNC);
	

	//define variables
	char choice = ' ';
	int levelNum = 0;
	int blockNum = 1;
	int score = 0;
	ifstream menuFile;
	string str;
	menuFile.open("menu.txt");
	stringstream stringythingy;
	bool collided =  false;

	while(getline(menuFile, str))
	{
		stringythingy << str << endl;
	}

	do
	{
		SetConsoleTextAttribute(hCon, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cls(hCon);
		cout << stringythingy.str();
		choice = _getch();
		if(choice == 's' || choice == 'S')
		{
			for ( levelNum=1; levelNum<=MAXLEVEL; levelNum++)
			{
				score = 0;
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
					level.printText("Error opening level file");
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
					level.printText("Error opening splash screen file");
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
				if(levelNum == 1)
				{
					PlaySound(NULL, NULL, NULL);
					PlaySound("./DasPeaceful.wav", NULL, SND_FILENAME | SND_ASYNC);
				}
				else if(levelNum == 4)
				{
					PlaySound(NULL, NULL, NULL);
					PlaySound("./DasEpic.wav", NULL, SND_FILENAME | SND_ASYNC);
				}
				_getch();

				char c;
				level.setLives(3);
				blockNum = level.getBlockNum();

				//begin level loop
				while (level.getLives() > 0 && blockNum > 0)
				{
					
					level.updatePuck();
					bool continueLoopingSoYouDontHaveToUseABreak = true;
					for (int i = 0; i < 9 && continueLoopingSoYouDontHaveToUseABreak; i++ )
					{
						Sleep(10);

						//paddle
						if(_kbhit())
						{
							c = _getch();
							switch(c)
							{
								case 'A':
								case 'a':
								case 75: //left
									level.moveLeft();
									break;
								case 'D':
								case 'd':
								case 77: //right
									level.moveRight();
									break;
							}
						}

						int blockLocX = -1;
						int blockLocY = -1;
						collided = false;

						//loop for paddle collision detection
						for (int i = 0; i < 9; i++)
						{
							if (
									( 
										level.getPaddleX() + i - 1 == level.getPuckX()
									)
									&&
									(
										level.getPaddleY() - 1 == level.getPuckY()
									)
							   )
							{
								level.reversePuck( false, true );
								collided = true;
							}
						}

						//for sides collision detection--but not bottom
						if (level.getPuckX() > 76 || level.getPuckX() < 4)
						{
							level.reversePuck( true, false );
							collided = true;
						}
						if ( level.getPuckY() < 1 )
						{
							level.reversePuck( false, true );
							collided = true;
						}

						//bottom detection
						if ( level.getPuckY() > 27 )
						{
							level.setLives( level.getLives() - 1 );

							if( level.getLives() > 0  )
							{
								level.pauseGame( score );

								level.reversePuck( false, true );
							
								level.removePaddlePuck();
								level.setPaddle(37, 28);
								level.setPuck(40, 26);
								level.updatePuck();
								level.moveLeft();
								level.moveRight();

								level.pauseGame( score );

								continueLoopingSoYouDontHaveToUseABreak = false;
							}
						}

						//loop for blocks collision detection
						for (int k = 0; k < 9; k++)
						{
							for (int j = 0; j < 9; j++)
							{
								if(level.getBlockX(k, j) != -1)
								{
									bool blockHit = false;
									bool reverseX = false;
									bool reverseY = false;
									
									for (int i = 0; i < 7; i++)
									{
										if ( ( level.getBlockX(k, j) + i == level.getPuckX() ) &&
											( level.getBlockY(k, j) + 1 == level.getPuckY() ) )
										{
											reverseX = false;
											reverseY = true;
											blockLocX = k;
											blockLocY = j;
											collided = true;
											blockHit = true;
										}
										if ( ( level.getBlockX(k, j) + i == level.getPuckX() ) &&
											( level.getBlockY(k, j) - 1 == level.getPuckY() ) )
										{
											reverseX = false;
											reverseY = true;
											blockLocX = k;
											blockLocY = j;
											collided = true;
											blockHit = true;
										}
									}

									for (int i = 0; i < 9; i++)
									{
										if ( ( level.getBlockX(k, j) + i - 1 == level.getPuckX() ) &&
											( level.getBlockY(k, j) == level.getPuckY() ) )
										{
											reverseX = true;
											reverseY = false;
											blockLocX = k;
											blockLocY = j;
											collided = true;
											blockHit = true;
										}
									}

									if ( blockHit )
									{
										Beep(200,20); //makes beep when block is hit.
										level.reversePuck( reverseX, reverseY );
										level.removeBlock(k, j);
										score = score + 100;
										stringstream scoreStream;
										scoreStream << "Score: " << score << "            ";
										level.printText( scoreStream.str() );
										blockNum--;
									}
								}
							}
						}

						if(blockLocX != -1)
						{
							level.setBlockX(blockLocX, blockLocY, -1);
						}

						if(blockLocY != -1)
						{
							level.setBlockY(blockLocX, blockLocY, -1);
						}

						if( collided )
						{
							level.updatePuck();
						}
					}
				} //end level loop



				if(blockNum != 0)
				{
					if(levelNum < 3)
					{
						levelNum = 3;
					}
					else
					{
						level.clearScreen();
						SetConsoleTextAttribute(hCon, NULL | FOREGROUND_INTENSITY);
						ifstream loseFile;
						loseFile.open("youlose.txt");
						if (!loseFile)
						{
							level.printText("Error opening lose screen file");
							return 1;
						}

						string tempString;
						while (getline(loseFile, tempString))
						{
							cout << tempString << endl;
						}
						PlaySound(NULL, NULL, NULL);
						PlaySound("./youlose.wav", NULL, SND_FILENAME | SND_ASYNC);
					}
				}

				level.pauseGame( score );

				level.clearScreen();

			}
			//macbook air gift
			levelNum = 1;
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
