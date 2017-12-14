#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>
#include <string.h>

#include "cursor.h"

int difficultyPointer = 0;
int board[10][10] = { 0 };
int r = 4, c = 4;
int changesMade = 0;
int winValue = 0;

int nthFibo(int n) {
	int a = 1, b = 1;
	if (n == 1 || n == 2) {
		return 1;
	}
	else {
		a = 1;
		b = 2;
		int i = 3;
		while (i < n) {
			int temp = b;
			b = a + b;
			a = temp;
			i++;
		}
		return a;
	}
}

void calcWinVal() {
	winValue = nthFibo(2 * r * c);
}

int difficulty() {
	int executed = 0; 
	do {	
		system("cls");
		gotoxy(48, 2); printf("CHOOSE A DIFFICULTY");
		gotoxy(55, 10); printf("Easy");
		gotoxy(55, 12); printf("Hard");
		gotoxy(52, 10 + difficultyPointer * 2); printIcon();

		rect(42, 8, 30, 7);

		gotoxy(0, 0);
		int ch;
		ch = _getch();
		if (ch == 224 || ch == 0) {
			ch = _getch();
			switch (ch) {
			case UP_ARROW:
				difficultyPointer--;
				if (difficultyPointer < 0) difficultyPointer = 1;
				break;

			case DOWN_ARROW:
				difficultyPointer++;
				if (difficultyPointer > 1) difficultyPointer = 0;
				break;
			}
		}
		else if (ch == ENTER) {
			executed = 1;
			if (difficultyPointer == 0) {
				r = c = 2;
				calcWinVal();
			}
			else if (difficultyPointer == 1) {
				r = c = 4;
				calcWinVal();
			}
			//else if (difficultyPointer == 2) {
				
			//}
		}
		else if (ch == ESC) {
			return 0;
		}
	} while (!executed);
	return 1;
}

void gameInstructions() {
	gotoxy(90, 1); printf("INSTRUCTIONS");
	rect(89, 2, 30, 5);
	//gotoxy(90, 2); printf("________________________");
	gotoxy(90, 3); printf("1)	USE ARROWS TO MOVE");
	gotoxy(90, 4); printf("2)	PRESS Ctrl+S TO SAVE");
	gotoxy(90, 5); printf("3)	PRESS ESC TO EXIT");
	//gotoxy(90, 6); printf("_________________________");
}

void display(int moves) {
	system("cls");
	int startX, startY, tempX;
	if (r == 4 && c == 4) {
		startX = 40;
		tempX = startX;
		startY = 4;
	}
	else if (r == 2 && c == 2) {
		startX = 43;
		tempX = startX;
		startY = 6;
	}
	int i, j;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			rect(startX + j * 5 - 2, startY + i * 2 - 1, 6, 2);
			gotoxy(startX + j * 5, startY + i * 2); if(board[i][j]) printf("%d", board[i][j]);
		}
	}
	if (moves) {
		gotoxy(45, 15); printf("Moves made: %d", moves);
	}
	if (instructions) {
		gameInstructions();
	}
	else {
		gotoxy(88, 0); printf("Press F11 to open instructions");
	}
}

void display1(int moves) {
	system("cls");
	int startX, startY, tempX;
	if (r == 4 && c == 4) {
		startX = 40;
		tempX = startX;
		startY = 4;
	}
	else if (r == 2 && c == 2) {
		startX = 43;
		tempX = startX;
		startY = 6;
	}
	int i, j;
	for (i = 0; i < r; i++) {
		startX = tempX;
		gotoxy(startX, startY++);
		if (r == 4 && c == 4) { 
			if (i == 0) printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", TOP_LEFT, HORIZONTAL_LINE, HORIZONTAL_LINE, HORIZONTAL_LINE, HORIZONTAL_LINE, HORIZONTAL_LINE, HORIZONTAL_LINE, TT, HORIZONTAL_LINE, HORIZONTAL_LINE, HORIZONTAL_LINE, HORIZONTAL_LINE, HORIZONTAL_LINE, HORIZONTAL_LINE, TT, HORIZONTAL_LINE, HORIZONTAL_LINE, HORIZONTAL_LINE, HORIZONTAL_LINE, HORIZONTAL_LINE, HORIZONTAL_LINE, TT, HORIZONTAL_LINE, HORIZONTAL_LINE, HORIZONTAL_LINE, HORIZONTAL_LINE, HORIZONTAL_LINE, HORIZONTAL_LINE, TOP_RIGHT);
			else printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", LT, HORIZONTAL_LINE, HORIZONTAL_LINE, HORIZONTAL_LINE, HORIZONTAL_LINE, HORIZONTAL_LINE, HORIZONTAL_LINE, PLUS, HORIZONTAL_LINE, HORIZONTAL_LINE, HORIZONTAL_LINE, HORIZONTAL_LINE, HORIZONTAL_LINE, HORIZONTAL_LINE, PLUS, HORIZONTAL_LINE, HORIZONTAL_LINE, HORIZONTAL_LINE, HORIZONTAL_LINE, HORIZONTAL_LINE, HORIZONTAL_LINE, PLUS, HORIZONTAL_LINE, HORIZONTAL_LINE, HORIZONTAL_LINE, HORIZONTAL_LINE, HORIZONTAL_LINE, HORIZONTAL_LINE, RT);
		}
		if (r == 2 && c == 2) { 
			if(i == 0) printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", TOP_LEFT, HORIZONTAL_LINE, HORIZONTAL_LINE, HORIZONTAL_LINE, HORIZONTAL_LINE, HORIZONTAL_LINE, HORIZONTAL_LINE, TT, HORIZONTAL_LINE, HORIZONTAL_LINE, HORIZONTAL_LINE, HORIZONTAL_LINE, HORIZONTAL_LINE, HORIZONTAL_LINE, TOP_RIGHT);
			else printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", LT, HORIZONTAL_LINE, HORIZONTAL_LINE, HORIZONTAL_LINE, HORIZONTAL_LINE, HORIZONTAL_LINE, HORIZONTAL_LINE, PLUS, HORIZONTAL_LINE, HORIZONTAL_LINE, HORIZONTAL_LINE, HORIZONTAL_LINE, HORIZONTAL_LINE, HORIZONTAL_LINE, RT);
		}
		for (j = 0; j < c; j++) {
			gotoxy(startX, startY);
			printf("%c", VERTICAL_LINE);
			if (board[i][j] != 0) {
				printf("%6d", board[i][j]);
			}
			else {
				printf("      ");
			}
			startX += 7;
		}
		printf("%c", VERTICAL_LINE);
		startY += 1;
	}
	startX = tempX;
	gotoxy(startX, startY++); 
	if (r == 4 && c == 4) { 
		printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", BOTTOM_LEFT, HORIZONTAL_LINE, HORIZONTAL_LINE, HORIZONTAL_LINE, HORIZONTAL_LINE, HORIZONTAL_LINE, HORIZONTAL_LINE, BT, HORIZONTAL_LINE, HORIZONTAL_LINE, HORIZONTAL_LINE, HORIZONTAL_LINE, HORIZONTAL_LINE, HORIZONTAL_LINE, BT, HORIZONTAL_LINE, HORIZONTAL_LINE, HORIZONTAL_LINE, HORIZONTAL_LINE, HORIZONTAL_LINE, HORIZONTAL_LINE, BT, HORIZONTAL_LINE, HORIZONTAL_LINE, HORIZONTAL_LINE, HORIZONTAL_LINE, HORIZONTAL_LINE, HORIZONTAL_LINE, BOTTOM_RIGHT);
	}
	if (r == 2 && c == 2) { 
		printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", BOTTOM_LEFT, HORIZONTAL_LINE, HORIZONTAL_LINE, HORIZONTAL_LINE, HORIZONTAL_LINE, HORIZONTAL_LINE, HORIZONTAL_LINE, BT, HORIZONTAL_LINE, HORIZONTAL_LINE, HORIZONTAL_LINE, HORIZONTAL_LINE, HORIZONTAL_LINE, HORIZONTAL_LINE, BOTTOM_RIGHT);
	};
	if (moves) {
		gotoxy(45, 15); printf("Moves made: %d", moves);
	}
	gameInstructions();
}

void insert() {
	srand(time(NULL));
	int x, y;
	do {
		x = rand() % r;
		y = rand() % c;
	} while (board[x][y] != 0);
	board[x][y] = 1;
}

void initialize() {
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			board[i][j] = 0;
		}
	}
	insert();
	insert();
}

void moveLeft() {
	for (int i = 0; i < r; i++) {
		int j = 0, k = 0;
		while (j < c) {
			if (board[i][j] == 0) {
				k = j + 1;
				int found = 0;
				while (k < c) {
					if (board[i][k] != 0) {
						found = 1;
						break;
					}
					k++;
				}
				if (found) {
					changesMade = 1;
					board[i][j] = board[i][k];
					board[i][k] = 0;
				}
			}
			j++;
		}
	}
}

void moveRight() {
	for (int i = 0; i < r; i++) {
		int j = c - 1, k = c - 1;
		while (j >= 0) {
			if (board[i][j] == 0) {
				k = j - 1;
				int found = 0;
				while (k >= 0) {
					if (board[i][k] != 0) {
						found = 1;
						break;
					}
					k--;
				}
				if (found) {
					changesMade = 1;
					board[i][j] = board[i][k];
					board[i][k] = 0;
				}
			}
			j--;
		}
	}
}

void moveUp() {
	for (int j = 0; j < c; j++) {
		int i = 0, k = 0;
		while (i < r) {
			if (board[i][j] == 0) {
				int found = 0;
				k = i + 1;
				while (k < r) {
					if (board[k][j] != 0) {
						found = 1;
						break;
					}
					k++;
				}
				if (found) {
					changesMade = 1;
					board[i][j] = board[k][j];
					board[k][j] = 0;
				}
			}
			i++;
		}
	}
}

void moveDown() {
	for (int j = 0; j < c; j++) {
		int i = r - 1, k = r - 1;
		while (i >= 0) {
			if (board[i][j] == 0) {
				int found = 0;
				k = i - 1;
				while (k >= 0) {
					if (board[k][j] != 0) {
						found = 1;
						break;
					}
					k--;
				}
				if (found) {
					changesMade = 1;
					board[i][j] = board[k][j];
					board[k][j] = 0;
				}
			}
			i--;
		}
	}
}

int isFiboPair(int n1, int n2) {
	if (n1 > n2) {
		int temp = n1;
		n1 = n2;
		n2 = temp;
	}
	int a = 1, b = 1, found = 0;
	do {
		if (a == n1 && b == n2) {
			found = 1;
			break;
		}
		else if (a > n1) {
			break;
		}
		int temp = b;
		b = a + b;
		a = temp;
	} while (1);
	if (found) {
		changesMade = 1;
	}
	return found;
}

void mergeLeft() {
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c - 1; j++) {
			if (isFiboPair(board[i][j], board[i][j + 1])) {
				board[i][j] += board[i][j + 1];
				board[i][j + 1] = 0;
				j++;
			}
		}
	}
}

void mergeRight() {
	for (int i = 0; i < r; i++) {
		for (int j = c - 1; j >= 1; j--) {
			if (isFiboPair(board[i][j], board[i][j - 1])) {
				board[i][j] += board[i][j - 1];
				board[i][j - 1] = 0;
				j--;
			}
		}
	}
}

void mergeUp() {
	for (int j = 0; j < c; j++) {
		for (int i = 0; i < r - 1; i++) {
			if (isFiboPair(board[i][j], board[i + 1][j])) {
				board[i][j] += board[i + 1][j];
				board[i + 1][j] = 0;
				i++;
			}
		}
	}
}

void mergeDown() {
	for (int j = 0; j < c; j++) {
		for (int i = r - 1; i >= 1; i--) {
			if (isFiboPair(board[i][j], board[i - 1][j])) {
				board[i][j] += board[i - 1][j];
				board[i - 1][j] = 0;
				i--;
			}
		}
	}
}

int move(int dir) {
	changesMade = 0;
	switch (dir) {
	case -1:
		return -1;
		break;

	case 1:
		moveUp();
		mergeUp();
		moveUp();
		break;

	case 2:
		moveRight();
		mergeRight();
		moveRight();
		break;

	case 3:
		moveDown();
		mergeDown();
		moveDown();
		break;

	case 4:
		moveLeft();
		mergeLeft();
		moveLeft();
		break;
	}
	return changesMade;
}

int exitGame() {
	int ptr = 0, c;
	do {
		system("cls");
		display(0);
		gotoxy(80, 13); printf("ARE YOU SURE YOU WANT TO QUIT");
		gotoxy(80, 14);  printf("WITHOUT SAVING ? ");
		rect(79, 16, 20, 4);
		gotoxy(80, 17); printf("SAVE AND QUIT");
		gotoxy(80, 18); printf("QUIT");
		gotoxy(80, 19); printf("CANCEL");
		gotoxy(78, 17 + ptr); printf(">");
		gotoxy(0, 0);
		c = _getch();
		if (c == 224 || c == 0) {
			c = _getch();
			switch (c) {
			case UP_ARROW:
				ptr--;
				if (ptr < 0) ptr = 2;
				break;

			case DOWN_ARROW:
				ptr++;
				if (ptr > 2) ptr = 0;
				break;
			}
		}
		else if (c == ENTER) {
			switch (ptr) {
			case 0:
				return -1;
				break;

			case 1:
				return 1;
				break;

			case 2:
				return 0;
				break;
			}
		}
		else if (c == ESC) {
			return 0;
		}
	} while (1);
}

int displayAndGetDir(int moves) {
	display(moves);
	gotoxy(0, 0);
	int ch;
	ch = _getch();
	if (ch == 224 || ch == 0) {
		ch = _getch();
		switch (ch) {
		case UP_ARROW:
			return 1;
			break;

		case RIGHT_ARROW:
			return 2;
			break;

		case DOWN_ARROW:
			return 3;
			break;

		case LEFT_ARROW:
			return 4;
			break;
		case F11:
			instructions = !instructions;
			return 5;
			break;
		}
	}
	else if (ch == ESC) {
		int c = exitGame();
		switch (c) {
		case 1:
			return -1;
			break;

		case 0:
			return -2;
			break;

		case -1:
			return -3;
			break;
		}
	}
	else if (ch == CTRL_S) {
		return 0;
	}
	else {
		return displayAndGetDir(moves);
	}
}

int isGameOver() {
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c - 1; j++) {
			if (isFiboPair(board[i][j], board[i][j + 1]) || board[i][j] == 0 || board[i][j + 1] == 0) {
				return 0;
			}
		}
	}
	for (int j = 0; j < c; j++) {
		for (int i = 0; i < r - 1; i++) {
			if (isFiboPair(board[i][j], board[i + 1][j])) {
				return 0;
			}
		}
	}
	return 1;
}

int gameWon() {
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (board[i][j] == winValue || board[i][j + 1] == winValue) {
				return 1;
			}
		}
	}
	return 0;
}

int calcScore() {
	int score = 0;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			score += board[i][j];
		}
	}
	return score;
}
