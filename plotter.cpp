#include <iostream>

using namespace std;

#include "plotter.h"

Plotter::Plotter()
{
       coordScreen.X = 0;
       coordScreen.Y = 0;
       
       hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
       SetConsoleTextAttribute(hConsoleOutput, green);

}
void Plotter::move(int x, int y)
{
       coordScreen.X = x;
       coordScreen.Y = y;
       //SetConsoleTextAttribute(hConsoleOutput, c);     
       SetConsoleCursorPosition( hConsoleOutput, coordScreen );
}
void Plotter::plot(int x, int y, char c)
{
       coordScreen.X = x;
       coordScreen.Y = y;
       //SetConsoleTextAttribute(hConsoleOutput, c);     
       SetConsoleCursorPosition( hConsoleOutput, coordScreen );
       cout << c;
       cout.flush();
}
void Plotter::setColor(ink c)
{
   SetConsoleTextAttribute(hConsoleOutput, c);
}
void Plotter::setColorSpecific(ink color)
{
	if(color == cyan)
	{
		SetConsoleTextAttribute(hConsoleOutput, NULL | FOREGROUND_INTENSITY
			| BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
	}
	else if(color == red)
	{
		SetConsoleTextAttribute(hConsoleOutput, NULL | FOREGROUND_INTENSITY |
			BACKGROUND_RED | BACKGROUND_INTENSITY);
	}
	else if(color == black)
	{
		SetConsoleTextAttribute(hConsoleOutput, 0 | FOREGROUND_INTENSITY
			| BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
	}
}
void Plotter::clear()
{
  cls( hConsoleOutput );
}
void Plotter::cls( HANDLE hConsole )
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
