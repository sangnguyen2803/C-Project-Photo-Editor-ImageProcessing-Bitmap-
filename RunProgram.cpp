#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <iostream>

#include "RunProgram.h"
#include "Keyboard.h"
#include "Screen.h"


using namespace std;

struct BACKGROUND
{
	char matrix1[500][500];
	int height;
	int width;
};
static BACKGROUND bg;



static void print_background();
static void print_tittle();
static void draw_border();
static void draw_border1();
static void draw_button(int a, int b, int c, int d, int e);

void run_program(int bg_height, int bg_width, int &code_processing)
{
	restart:
	//code for editing photo
	resizeScreen(970,780);
	bg.height = bg_height;
	bg.width = bg_width;
	print_background();
	draw_button(125,125,125,125,125);
	textcolor(125);
	while(1)
	{
		if(keypressed())
		{
			int key = getkey();
			if (key == KEY_F8)
			{
				clearscreen();
				print_background();
				draw_button(125,125,125,125,125);
			}
			if(key == KEY_F1)
			{
				clearscreen();
				print_background();
				draw_button(125,121,125,125,125);
				gotoxy(53,11);
				textcolor(125);
				cout<<"CODE: ";
				gotoxy(37,12);
				cout<<"01 - REDUCING SIZE OF PHOTO";
				gotoxy(37,13);
				cout<<"02 - ENLARGING SIZE OF PHOTO";
				gotoxy(37,14);
				cout<<"03 - CROPPING PHOTO";
				gotoxy(37,15);
				cout<<"04 - MIRROR MODE 1 - HORIZONTALITY";
				gotoxy(37,16);
				cout<<"05 - MIRROR MODE 2 - VERTICALITY";
				gotoxy(37,17);
				cout<<"06 - FLIPPING PHOTO - HORIZONTALITY";
				gotoxy(37,18);
				cout<<"07 - ELIPPING PHOTO - VERTICALITY";
				gotoxy(37,19);
				cout<<"08 - BLACK-WHITE MODE";
				gotoxy(37,20);
				cout<<"09 - COLOR FILTERS ( 11 AVAILABLE MODES )";
				gotoxy(39,21);
				cout<<"09->1 RED - 09->2 GREEN - 09->3 BLUE - 09->4 PINK";
				gotoxy(39,22);
				cout<<"09->5 ORANGE - 09->6 YELLOW - 09->7 CYAN - 09->8 VIOLET";
				gotoxy(39,23);
				cout<<"09->9 GY-BLENDED (DENSITY: 0->127 YELLOW | 128 -> 255 GREEN)";
				gotoxy(39,24);
				cout<<"09->10 VINTAGE MODE - 09->11 REVERSED COLOUR";
				gotoxy(37,25);
				cout<<"10 - NEGATIVE PROOF MODE";
				gotoxy(37,26);
				cout<<"11 - ADJUSTING BRIGHTNESS LEVEL";
				gotoxy(37,27);
				cout<<"12 - ADJUSTING CONTRAST LEVEL";
				gotoxy(37,28);
				cout<<"13 - ROTATING PHOTO - (90 - 180 - 270 - 360 DEGREES)";
				gotoxy(37,29);
				cout<<"14 - CMYK COLOUR MODE (CYAN-MAGENTA-YELLOW-KEY)";
				gotoxy(37,30);
				cout<<"15 - GRAIN";
				gotoxy(37,31);
				cout<<"16 - INSERTING PHOTO";
				gotoxy(37,32);
				cout<<"17 - INSERTING TEXTURE";
				gotoxy(72,33);
				cout<<"[NEXT PAGE]-> PRESS F10";
				textcolor(7);
				
			}
			if(key == KEY_F2)
			{
				clearscreen();
				print_background();
				draw_button(125,125,121,125,125);
				
				textcolor(125);
				gotoxy(60,11);
				cout<<"INSTRUCTION";
				gotoxy(37,13);
				cout<<"BEFORE USING THIS PHOTO EDITOR, PLEASE PRESS F1 TO READ THE ";
				gotoxy(37,14);
				cout<<"FUNCTIONAL TOOL LIST TO KNOW THE TOOL YOU WOULD LIKE TO USE.";
				gotoxy(37,15);
				cout<<"THEN PRESS F3 TO ENTER THE CODE THAT YOU TOOK FROM F1.";
				gotoxy(37,16);
				cout<<"YOU CAN ALSO EDIT THE PHOTO BY ENTERING PARAMETERS";
				gotoxy(37,15);
				cout<<"BEFORE YOU START TO EDIT YOUR IMAGE, YOU HAVE TO REMEMBER THE CODES LIKED TO THE FUNCTIONAL TOOL, EACH NUMBE";
				gotoxy(37,16);
				cout<<"";
				gotoxy(37,17);
				cout<<"";
				gotoxy(37,18);
				cout<<"";
				gotoxy(37,19);
				cout<<"";
				textcolor(7);
			}
			if(key == KEY_F3)
			{
				clearscreen();
				print_background();
				draw_button(125,125,125,121,125);
				textcolor(125);
				gotoxy(37,13);
				cout<<"ENTER THE CODE CORRESPONDING TO THE FUNCTIONAL TOOLS WHICH YOU ";//If you don't remember the code, you can press F2 to open the list of functional tools.
				gotoxy(39,14);
				cout<<"WANT YOUR IMAGE TO BE PROCESSED OR EDITED BY \"PHOTO EDITOR\".";
				gotoxy(37,16);
				cout<<"IF YOU DO NOT REMEMBER THE CODE, YOU CAN PRESS F1 TO OPEN";
				gotoxy(50,17); 
				cout<<"THE LIST OF FUNCTIONAL TOOLS";
				gotoxy(60,19);
				cout<<"ENTER YOUR CODE : ";
				cin>>code_processing;
				gotoxy(49,23);
				textcolor(125);
				cout<<"DO YOU REALLY WANT TO EDIT THIS PHOTO?";
				gotoxy(55,24);
				cout<<"<<YES(F6)>> - <<NO(F7)>>";
				textcolor(7);
			}
			if(key == KEY_F4)
			{
				clearscreen();
				print_background();
				draw_button(125,125,125,125,121);
				textcolor(125);
				gotoxy(54,22);
				cout<<"DO YOU REALLY WANT TO EXIT ?";
				gotoxy(55,24);
				cout<<"<<YES(F9)>> - <<NO(F8)>>";
			}
			if(key == KEY_F6)
			{
				clearscreen();
				print_tittle();
				draw_border1();
				return;
			}	
			if(key == KEY_F9)
				exit(0);
			if(key == KEY_F7)
			{
				clearscreen();
				goto restart;
			}
			if(key == KEY_F10)
			{
				clearscreen();
				print_background();
				draw_button(125,121,125,125,125);
				gotoxy(53,11);
				textcolor(125);
				cout<<"CODE: ";
				gotoxy(37,12);
				cout<<"18 - PIXEL-ART MODE";
				gotoxy(37,13);
				cout<<"19 - GREY-WHITE MODE";
				gotoxy(72,33);
				cout<<"[PREVIOUS PAGE]-> PRESS F1";
				textcolor(7);								
			}
		}
	}
}
void print_background()
{
	print_tittle();
	draw_border();
}
void print_tittle()
{
	textcolor(125);
	cout<<"\xdd";for(int i = 1; i < 100; i++) cout<<"\xdf";cout<<"\xde"<<endl;
	cout<<"\xdd\t\xb2\xdb\xdb\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb1\xb1\xb0\xb0\t    \xb2\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xb2\xb2\xb2\xb1\xb1\t        *HEREAFTER IS SOFTWARE'S INFORMATION        \xde"<<endl;
	cout<<"\xdd\t\xb2\xdb\xdb\xb2      \xb2\xb2\xb1\xb1\t    \xb2\xdb\xb2               \t\t*NAME: PHOTO EDITOR 2019 - VERSION 1.0.0    \xde"<<endl;
	cout<<"\xdd\t\xb2\xdb\xdb\xb2      \xb2\xb2\xb1\xb1\t    \xb2\xdb\xb2               \t\t*THIS SOFTWARE IS MAINLY MADE BY TEAM MEMBER\xde"<<endl;
	cout<<"\xdd\t\xb2\xdb\xdb\xb2\xb2\xb2\xb2\xb2\xb2\xb2\xb2 HOTO    \xb2\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xb2\xb2\xb2\xb1\xb1 DITOR        + NGUYEN SANG - LEADER - 18126029           \xde"<<endl;
	cout<<"\xdd\t\xb2\xdb\xdb\xb2           \t    \xb2\xdb\xb2                         + NGUYEN THI NGOC HAN - 18126015            \xde"<<endl;
	cout<<"\xdd\t\xb2\xdb\xdb\xb2           \t    \xb2\xdb\xb2                         + NGUYEN HOANG ANH - 1652002                \xde"<<endl;
	cout<<"\xdd\t\xb2\xdb\xdb\xb2                \xb2\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xb2\xb2\xb2\xb1\xb1\t\t\t\t\t   APRIL-4 2019     \xde"<<endl;
	cout<<"\xdd";for(int i = 1; i < 100; i++) cout<<"\xdc";cout<<"\xde"<<endl;
}
void draw_border()
{
	for(int i = 0; i <= bg.height/2; i++)
	{
		for(int j = 0; j <= bg.width; j++)
		{
			textcolor(117);
			if( i == 0 || i == bg.height/2)
				cout<<"\xdb";
			else
			{
				if( j == 0 || j == (bg.width/3) || j == bg.width)
					cout<<"\xdb";
				else
					cout<<" ";
			}
		}
		cout<<""<<endl;
	}
	textcolor(7);
}
void draw_button(int a, int b , int c, int d, int e) 
{
	textcolor(125);
	gotoxy(13,13);
	cout<<"PHOTO EDITOR";
	gotoxy(5,14);
	cout<<"MAKE YOUR LIFE SPECTACULAR";
	gotoxy(13,15);
	cout<<"--[MENU]--";
	textcolor(b);
	gotoxy(3,19);
		cout<<"-[FUNCTIONAL TOOL]- PRESS F1";
	textcolor(7);
	textcolor(c);
	gotoxy(3,21);
		cout<<"-[TUTORIAL]- PRESS F2";
	textcolor(7);
	textcolor(d);
	gotoxy(3,23);
		cout<<"-[ENTER CODE]- PRESS F3";
	textcolor(7);
	textcolor(e);
	gotoxy(3,25);
		cout<<"-[EXIT PROGRAM]- PRESS F4";
	textcolor(7);
	
}
void draw_border1()
{
	for(int i = 0; i <= bg.height/2; i++)
	{
		for(int j = 0; j <= bg.width; j++)
		{
			textcolor(113);
			if( i == 0 || i == bg.height/2)
				cout<<"\xdb";
			else
			{
				if( j == 0 || j == bg.width)
					cout<<"\xdb";
				else
					cout<<" ";
			}
		}
		cout<<""<<endl;
	}
	textcolor(7);
}
