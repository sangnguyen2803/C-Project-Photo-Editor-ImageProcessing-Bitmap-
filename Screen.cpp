#include <iostream>
#include <Windows.h>
#include <string.h>
#include "Screen.h"
using namespace std;

static HANDLE _hscr;

void textcolor(int x) // this functions is used for filling color
{
	HANDLE hConsoleColor;
	hConsoleColor = GetStdHandle ( STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsoleColor,x);
}
void initscr()
{
	_hscr = GetStdHandle(STD_OUTPUT_HANDLE);
}

void gotoxy(int x , int y) // this function move dicrectly the console cursor to the position based on two parametres "row" and "col"
{
	HANDLE hConsoleOutput;
	COORD Cursor_an_Pos = {x-1,y-1};
	hConsoleOutput = GetStdHandle (STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput , Cursor_an_Pos);
}
void hidecursor() 
{
	HANDLE hOut;
	CONSOLE_CURSOR_INFO ConCurInf;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	ConCurInf.dwSize = 10;
	ConCurInf.bVisible = FALSE;
	SetConsoleCursorInfo(hOut, &ConCurInf);
}
void clearscreen() // the responsibility of this function is clearing the screen - essential function to make the object's movement.
{
	HANDLE hOut;
	COORD Position;
	hOut = GetStdHandle (STD_OUTPUT_HANDLE);
	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);
}
void resizeScreen(int width, int height) // this function is created to change the screen resolution - it's different to size of matrix (2D Array)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left,r.top, width, height, TRUE);
}
