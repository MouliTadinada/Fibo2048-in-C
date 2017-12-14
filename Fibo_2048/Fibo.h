#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

#include "BoardUtilities.h"
#include "UserUtilities.h"

int menuPointer = 0;
int leaderboardPointer = 0;
int devPointer = 0;
int sortPointer = 0;

void thanks() {
	system("cls");
	//for (int i = 0; i < 15; i++) {
	//	system("cls");
	//	rect(29 - i, 10 - i / 5, i * 6, i);
	//	Sleep(1);
	//}
	gotoxy(50, 14); 
	char str[100] = "Thanks for playing !!";
	for (int i = 0; str[i] != '\0'; i++) {
		printf("%c", str[i]);
		Sleep(20);
	}
	Sleep(1500);
}

int quit() {
	int ch;
	int ptr = 0;
	do {
		system("cls");
		//rect(40, 4, 40, 9);
		gotoxy(45, 5); printf("Are you sure you want to quit?");
		rect(56, 9, 8, 3);
		gotoxy(59, 10); printf("Yes");
		gotoxy(59, 11); printf("No");
		gotoxy(53, 10 + ptr); printf("=>");
		gotoxy(0, 0);
		ch = _getch();
		switch (ch) {
		case 224:
		case 0:
			ch = _getch();
			switch (ch) {
			case UP_ARROW:
				ptr--;
				if (ptr < 0) ptr = 1;
				break;

			case DOWN_ARROW:
				ptr++;
				if (ptr > 1) ptr = 0;
				break;
			}
			break;

		case ENTER:
			return !ptr;
			break;

		case ESC:
			return 0;
		}
	} while (1);
}

void extras() {
	int flag;
	FILE *fp;
	do {
		system("cls");

		rect(45, 2, 30, 2);
		gotoxy(55, 3); printf("OPTIONS");

		rect(45, 7, 30, 8);
		gotoxy(50, 10); printf("Reset Leaderboard");
		gotoxy(50, 11); printf("Remove all saved files");
		gotoxy(50, 12); printf("%s Night Mode", mode == 0 ? "Enable" : "Disable");
		gotoxy(47, 10 + devPointer); printf("=>");
		gotoxy(0, 0);
		int ch;
		ch = _getch();
		if (ch == 224 || ch == 0) {
			ch = _getch();
			switch (ch) {
			case UP_ARROW:
				devPointer--;
				if (devPointer < 0) devPointer = 2;
				break;

			case DOWN_ARROW:
				devPointer++;
				if (devPointer > 2) devPointer = 0;
				break;
			}
		}
		else if (ch == ENTER) {
			FILE *fp;
			int ptr = 0;
			int ex = 0;
			system("cls");
			switch (devPointer) {
			case 0:
				fp = fopen("data", "rb");
				if (fp != NULL) {
					do {
						system("cls");
						gotoxy(40, 5); printf("Are you sure you want to reset the leaderboard?");
						gotoxy(55, 10); printf("YES");
						gotoxy(65, 10); printf("NO");
						gotoxy(53 + ptr * 10, 10); printf(">>");
						gotoxy(0, 0);
						int op;
						op = _getch();
						switch (op) {
						case 224:
						case 0:
							op = _getch();
							switch (op) {
							case LEFT_ARROW:
								ptr--;
								if (ptr < 0) ptr = 1;
								break;

							case RIGHT_ARROW:
								ptr++;
								if (ptr > 1) ptr = 0;
								break;
							}
							break;

						case ENTER:
							if (fp != NULL) fclose(fp);
							switch (ptr) {
							case 0:
								flag = 0;
								system("cls");
								fp = fopen("data", "rb+");
								for (int i = 0; i < limit; i++) {
									fseek(fp, start + i * step, SEEK_SET);
									fwrite(&flag, sizeof(int), 1, fp);
								}
								fclose(fp);
								initializeFreeBitMap();
								storeFreeBits();
								gotoxy(50, 7);  printf("Reset successful");
								gotoxy(0, 0);
								_getch();
								ex = 1;
								break;

							case 1:
								ex = 1;
								break;
							}
							break;

						case ESC:
							if (fp != NULL) fclose(fp);
							ex = 1;
							break;
						}
					} while (!ex);
				}
				break;

			case 1:
				fp = fopen("data", "rb");
				if (fp != NULL) {
					do {
						system("cls");
						gotoxy(40, 5); printf("Are you sure you want to remove all saved files?");
						gotoxy(55, 10); printf("YES");
						gotoxy(65, 10); printf("NO");
						gotoxy(53 + ptr * 10, 10); printf(">>");
						gotoxy(0, 0);
						int op;
						op = _getch();
						switch (op) {
						case 224:
						case 0:
							op = _getch();
							switch (op) {
							case LEFT_ARROW:
								ptr--;
								if (ptr < 0) ptr = 1;
								break;

							case RIGHT_ARROW:
								ptr++;
								if (ptr > 1) ptr = 0;
								break;
							}
							break;

						case ENTER:
							if (fp != NULL) fclose(fp);
							switch (ptr) {
							case 0:
								flag = 0;
								fp = fopen("data", "rb+");
								for (int i = 0; i < slots; i++) {
									fseek(fp, start2 + i * step, SEEK_SET);
									fwrite(&flag, sizeof(int), 1, fp);
								}
								fclose(fp);
								system("cls");
								initializeMidGameMap();
								storeFreeBits();
								gotoxy(50, 7);  printf("Removed successfully");
								gotoxy(0, 0);
								_getch();
								ex = 1;
								break;

							case 1:
								ex = 1;
								break;
							}
							break;

						case ESC:
							if (fp != NULL) fclose(fp);
							ex = 1;
							break;
						}
					} while (!ex);
				}
				break;

			case 2:
				mode = !mode;
				if (!mode) {
					system("color f0");
				}
				else {
					system("color 0f");
				}
				break;

			case 3:
				return;
				break;
			}
		}
		else if (ch == ESC) {
			return;
		}
	} while (1);
}

void printMenu() {
	system("cls");
	gotoxy(25, 1); printf("%c%c%c%c%c%c  %c%c%c%c%c%c  %c%c%c%c%c%c  %c%c%c%c%c%c          %c%c%c%c%c%c  %c%c%c%c%c%c  %c    %c  %c%c%c%c%c%c", BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX);
	gotoxy(25, 2); printf("%c%c        %c%c    %c%c   %c  %c    %c               %c  %c    %c  %c    %c  %c    %c", BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX);
	gotoxy(25, 3); printf("%c%c%c%c%c%c    %c%c    %c%c  %c   %c    %c  %c%c%c%c    %c%c%c%c%c%c  %c    %c  %c%c%c%c%c%c  %c%c%c%c%c%c", BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX);
	gotoxy(25, 4); printf("%c%c        %c%c    %c%c  %c   %c    %c  %c%c%c%c    %c%c%c%c%c%c  %c    %c  %c%c%c%c%c%c  %c%c%c%c%c%c", BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX);
	gotoxy(25, 5); printf("%c%c        %c%c    %c%c   %c  %c    %c          %c       %c    %c       %c  %c    %c", BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX);
	gotoxy(25, 6); printf("%c%c      %c%c%c%c%c%c  %c%c%c%c%c%c  %c%c%c%c%c%c          %c%c%c%c%c%c  %c%c%c%c%c%c       %c  %c%c%c%c%c%c", BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX, BOX);
	
	rect(45, 10, 24, 12);
	gotoxy(52, 12); printf("Play Game");
	gotoxy(52, 14); printf("Resume Game");
	gotoxy(52, 16); printf("Leaderboard");
	gotoxy(52, 18); printf("Options");
	gotoxy(52, 20); printf("Quit Game");
	gotoxy(48, 12 + menuPointer * 2); printIcon();


	gotoxy(0, 0);
}

int leaderboardTypeMenu() {
	do {
		printMenu();
		rect(69, 15, 15, 7);
		gotoxy(71, 16);  printf("View All");
		gotoxy(71, 18); printf("View Easy");
		gotoxy(71, 20); printf("View Hard");
		gotoxy(67, 16 + leaderboardPointer * 2); printIcon();
		gotoxy(0, 0);
		int ch;
		ch = _getch();
		if (ch == 224 || ch == 0) {
			ch = _getch();
			switch (ch) {
			case UP_ARROW:
				if (leaderboardPointer > 0) leaderboardPointer--;
				break;

			case DOWN_ARROW:
				if (leaderboardPointer < 2) leaderboardPointer++;
				break;
			}
		}
		else if (ch == ENTER) {
			return 1;
		}
		else if (ch == ESC) {
			return 0;
		}
	} while (1);
}

void leaderboardType() {
	switch (leaderboardPointer) {
	case 0:
		printAll();
		break;

	case 1:
		printAllWithDifficulty(1);
		break;

	case 2:
		printAllWithDifficulty(2);
		break;
	}
}

void leaderboard() {
	leaderboardPointer = 0;
	int isDataLoaded = loadData();
	int flag = countFilledBits();
	if (isDataLoaded && flag != 0) {
		if (leaderboardTypeMenu()) {
			do {
				system("cls");
				leaderboardType();
				rect(100, 0, 20, 10);
				rect(100, 0, 20, 2);
				gotoxy(103, 1); printf("SORT BASED ON");
				gotoxy(105, 3); printf("Date");
				gotoxy(105, 4); printf("Moves");
				gotoxy(105, 5); printf("Score");
				gotoxy(105, 6); printf("RETURN");
				gotoxy(102, 3 + sortPointer); printf("=>");//printIcon();
				gotoxy(0, 0);
				int ch;
				ch = _getch();
				if (ch == 224 || ch == 0) {
					ch = _getch();
					switch (ch) {
					case UP_ARROW:
						sortPointer--;
						if (sortPointer < 0) sortPointer = 3;
						break;

					case DOWN_ARROW:
						sortPointer++;
						if (sortPointer > 3) sortPointer = 0;
						break;
					}
				}
				if (ch == ENTER) {
					if (sortPointer == 3) {
						break;
					}
					else sortData(sortPointer);
				}
				if (ch == ESC) {
					return;
				}
			} while (1);
		}
	}
	else {
		rect(69, 15, 40, 2);
		gotoxy(71, 16); printf("NO DATA AVAILABLE !!");
		gotoxy(0, 0); _getch();
	}
}

void play(int isNewGame) {
	instructions = 0;
	int gameOver = 0;
	int saveTheGame = 1;
	if (isNewGame) {
		player();
		if (difficulty() == 0) return;
		setDifficulty();
		initialize();
	}
	do {
		int dir = displayAndGetDir(current.moves);
		if (dir == -3) {
			saveMidGame();
			gameOver = 1;
			saveTheGame = 0;
			break;
		}
		else if (dir == -2) {
			continue;
		}
		else if (dir == -1) {
			saveTheGame = 0;
			break;
		}
		else if (dir == 0) {
			saveMidGame();
			gotoxy(0, 0); printf("GAME SAVED SUCCESSFULLY !!");
			_getch();
		}
		else if(dir >= 1 && dir <= 4) {
			int moved = move(dir);
			if (moved == -1) {
				break;
			}
			else if (moved) {
				insert();
				madeMove();
				display(current.moves);
			}
			gameOver = isGameOver() || gameWon();
		}
	} while (gameOver == 0);
	if (saveTheGame) {
		if (gameOver && gameWon()) {
			gotoxy(40, 15); printf("%s won the game in %d moves !!", current.name, current.moves);
			gotoxy(0, 0);
			assignScoreAndStatus(calcScore(), 1);
			system("pause");
		}
		else {
			gotoxy(40, 15); printf("%s lost the game in %d moves !!", current.name, current.moves);
			gotoxy(0, 0);
			assignScoreAndStatus(calcScore(), 0);
			system("pause");
		}
		saveData();
	}
	
}

void menu() {
	createFile();
	int op;
	do {
		printMenu();
		op = _getch();
		if (op == 224 || op == 0) {
			op = _getch();
			switch (op) {
			case UP_ARROW:
				menuPointer--;
				if (menuPointer < 0) menuPointer = 4;
				break;

			case DOWN_ARROW:
				menuPointer++;
				if (menuPointer > 4)  menuPointer = 0;
				break;
			}
		}
		else if (op == ENTER) {
			switch (menuPointer) {
			case 0:
				play(1);
				break;

			case 1:
				if (resumeGameMenu()) {
					play(0);
				}
				break;

			case 2:
				leaderboard();
				break;

			case 3:
				extras();
				break;

			case 4:
				if (quit()) {
					gotoxy(0, 0);
					thanks();
					return;
				}
				break;
			}
		}
		else if (op == ESC) {
			if (quit()) {
				gotoxy(0, 0);
				thanks();
				return;
			}
		}
	} while (1);
}