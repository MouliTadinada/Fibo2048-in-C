#include <Windows.h>

#define UP_ARROW 72
#define DOWN_ARROW 80
#define LEFT_ARROW 75
#define RIGHT_ARROW 77
#define ENTER 13
#define ESC 27

#define HORIZONTAL_LINE 196
#define VERTICAL_LINE 179
#define TOP_RIGHT 191
#define TOP_LEFT 218
#define BOTTOM_RIGHT 217
#define BOTTOM_LEFT 192
#define LT 195
#define RT 180
#define TT 194
#define BT 193
#define PLUS 197


#define BULLET 254
#define BOX 219

#ifndef CONSOLE_H
#define CONSOLE_H

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

void gotoxy(int x, int y) {
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}

void printIcon() {
	printf("%c%c", 180, BULLET);
}

void rect(int x, int y, int l, int b) {
	gotoxy(x, y); printf("%c", TOP_LEFT); for (int i = 0; i < l - 2; i++) { printf("%c", HORIZONTAL_LINE); } printf("%c", TOP_RIGHT);
	for (int i = y + 1; i < y + b; i++) { gotoxy(x, i); printf("%c", VERTICAL_LINE); gotoxy(x + l - 1, i); printf("%c", VERTICAL_LINE); }
	gotoxy(x, y + b); printf("%c", BOTTOM_LEFT); for (int i = 0; i < l - 2; i++) { printf("%c", HORIZONTAL_LINE); } printf("%c", BOTTOM_RIGHT);
}

#endif /* CONSOLE_H */