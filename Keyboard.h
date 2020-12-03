#define KEY_BACKSPACE	0x108
#define KEY_TAB			0x109
#define KEY_SPACE		0x120
#define KEY_ENTER		0x10d
#define KEY_ESC			0x11b

#define KEY_LEFT		0x24b
#define KEY_RIGHT		0x24d
#define KEY_DOWN		0x250
#define KEY_UP			0x248
#define KEY_PGDOWN		0x251
#define KEY_PGUP		0x249
#define KEY_END			0x24f
#define KEY_HOME		0x247
#define KEY_DEL			0x253
#define KEY_INS			0x252

#define KEY_F1			0x33b
#define KEY_F2			0x33c
#define KEY_F3			0x33d
#define KEY_F4			0x33e
#define KEY_F5			0x33f
#define KEY_F6			0x340
#define KEY_F7			0x341
#define KEY_F8			0x342
#define KEY_F9			0x343
#define KEY_F10			0x344

int keypressed();
int getkey();
int isnormchar(int key);
