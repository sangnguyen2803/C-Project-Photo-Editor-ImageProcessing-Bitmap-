#include <conio.h>
#include "Keyboard.h"

int keypressed()
{
	return kbhit();
}

int getkey()
{
	int c = getch();
	if(c == 0xE0)
	{
		int code = getch();
		switch(code)
		{
			case 0x4b: return KEY_LEFT;
			case 0x4d: return KEY_RIGHT;
			case 0x50: return KEY_DOWN;
			case 0x48: return KEY_UP;
			case 0x51: return KEY_PGDOWN;
			case 0x49: return KEY_PGUP;
			case 0x4f: return KEY_END;
			case 0x47: return KEY_HOME;
			case 0x53: return KEY_DEL;
			case 0x52: return KEY_INS;
		}
	}
	else if(c == 0)
	{
		int code = getch();
		switch(code)
		{
			case 0x3b: return KEY_F1;
			case 0x3c: return KEY_F2;
			case 0x3d: return KEY_F3;
			case 0x3e: return KEY_F4;
			case 0x3f: return KEY_F5;
			case 0x40: return KEY_F6;
			case 0x41: return KEY_F7;
			case 0x42: return KEY_F8;
			case 0x43: return KEY_F9;
			case 0x44: return KEY_F10;
		}
	}
	else
	{
		switch(c)
		{
			case 0x8: return KEY_BACKSPACE;
			case 0x9: return KEY_TAB;
			case 0x20: return KEY_SPACE;
			case 0xd: return KEY_ENTER;
			case 0x1b: return KEY_ESC;
		}
		return c;	// ki tu ASCII binh thuong
	}

	return 0;
}

int isnormchar(int key)
{
	return 0 < key && key < 256;
}
