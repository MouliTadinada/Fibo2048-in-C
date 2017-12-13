#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "cursor.h"
#include "storage.h"

#define DEFAULT_NAME "NO_NAME"

struct User {
	int date;
	char month[10];
	int year;
	char name[100];
	int difficulty;
	int moves;
	int score;
	int status;
}current, *players, *mid, extra;

void setTime() {
	SYSTEMTIME t;
	GetSystemTime(&t);
	current.date = t.wDay;
	current.year = t.wYear;
	switch (t.wMonth) {
	case 1:
		strcpy(current.month, "Jan");
		break;

	case 2:
		strcpy(current.month, "Feb");
		break;

	case 3:
		strcpy(current.month, "Mar");
		break;

	case 4:
		strcpy(current.month, "Apr");
		break;

	case 5:
		strcpy(current.month, "May");
		break;

	case 6:
		strcpy(current.month, "Jun");
		break;

	case 7:
		strcpy(current.month, "Jul");
		break;

	case 8:
		strcpy(current.month, "Aug");
		break;

	case 9:
		strcpy(current.month, "Sep");
		break;

	case 10:
		strcpy(current.month, "Oct");
		break;

	case 11:
		strcpy(current.month, "Nov");
		break;

	case 12:
		strcpy(current.month, "Dec");
		break;
	}
}

void createFile() {
	int flag = 0;
	FILE *fp = fopen("data", "rb+");
	if (fp == NULL) {
		system("fsutil file createnew data 10000000");
		initializeFreeBitMap();
		storeFreeBits();
		setFreeBits();
		initializeMidGameMap();
		storeMidGameBits();
		setMidGameBits();
		system("cls");
	}
	else {
		loadFreeBits();
		loadMidGameBits();
		fclose(fp);
	}
}

void player() {
	system("cls");
	gotoxy(20, 15); printf("Enter your Name: ");
	rect(42, 14, 44, 2);
	gotoxy(44, 15); gets(current.name);
	if (current.name[0] == '\0') strcpy(current.name, DEFAULT_NAME);
	current.moves = 0;
}

void madeMove() {
	current.moves++;
}

void setDifficulty() {
	if (r == 2 && c == 2) {
		current.difficulty = 1;
	}
	else if (r == 4 && c == 4) {
		current.difficulty = 2;
	}
}

void printAll() {
	int len = countFilledBits();
	rect(7, 0, 92, 2);
	gotoxy(10, 1); printf("SNO.");
	gotoxy(20, 1); printf("DATE");
	gotoxy(40, 1); printf("NAME");
	gotoxy(58, 1); printf("DIFFICULTY");
	gotoxy(70, 1); printf("MOVES");
	gotoxy(80, 1); printf("SCORE");
	gotoxy(90, 1); printf("STATUS");
	for (int i = 0; i < len; i++) {
		rect(7, 2 + (i + 1) * 2 - 1, 92, 2);
		gotoxy(10, 2 + (i + 1) * 2 ); printf("%3d", i + 1);
		gotoxy(20, 2 + (i + 1) * 2); printf("%d %s %d", players[i].date, players[i].month, players[i].year);
		gotoxy(40, 2 + (i + 1) * 2); printf("%s", players[i].name);
		gotoxy(58, 2 + (i + 1) * 2); printf("%s", players[i].difficulty == 1 ? "2x2" : "4x4");
		gotoxy(70, 2 + (i + 1) * 2); printf("%4d", players[i].moves);
		gotoxy(80, 2 + (i + 1) * 2); printf("%4d", players[i].score);
		gotoxy(90, 2 + (i + 1) * 2); printf("%s", players[i].status == 1 ? "WON" : "LOST");
	}
	gotoxy(0, 0);
}

void printAllWithDifficulty(int difficulty) {
	int count = 0;
	int len = countFilledBits();
	rect(7, 0, 83, 2);
	gotoxy(10, 1); printf("SNO.");
	gotoxy(20, 1); printf("DATE");
	gotoxy(35, 1); printf("NAME");
	gotoxy(55, 1); printf("MOVES");
	gotoxy(65, 1); printf("SCORE");
	gotoxy(80, 1); printf("STATUS");
	for (int i = 0; i < len; i++) {
		if (players[i].difficulty == difficulty) {
			rect(7, 2 + (count + 1) * 2 - 1, 83, 2);
			gotoxy(10, 2 + (count + 1) * 2); printf("%3d", count + 1);
			gotoxy(20, 2 + (count + 1) * 2); printf("%d %s %d", players[i].date, players[i].month, players[i].year);
			gotoxy(35, 2 + (count + 1) * 2); printf("%s", players[i].name);
			gotoxy(55, 2 + (count + 1) * 2); printf("%4d", players[i].moves);
			gotoxy(65, 2 + (count + 1) * 2); printf("%4d", players[i].score);
			gotoxy(80, 2 + (count + 1) * 2); printf("%s", players[i].status == 1 ? "WON" : "LOST");
			count++;
		}
	}
	gotoxy(0, 0);
}

void assignScoreAndStatus (int score, int status) {
	current.score = score;
	current.status = status;
}

void saveMidGame() {
	int addr = findMidGameBit();
	int flag = 1;
	FILE *fp = fopen("data", "rb+");
	setTime();
	fseek(fp, addr, SEEK_SET);
	fwrite(&flag, sizeof(int), 1, fp);
	fwrite(&current, sizeof(struct User), 1, fp);
	fwrite(board, sizeof(board), 1, fp);
	fclose(fp);
}

int loadMidGame(int index) {
	if (midGameBitMap[index]) {
		int flag;
		int addr = start2 + index * step;
		FILE *fp = fopen("data", "rb+");
		fseek(fp, addr, SEEK_SET);
		fread(&flag, sizeof(int), 1, fp);
		if (flag) {
			fread(&current, sizeof(struct User), 1, fp);
			fread(&board, sizeof(board), 1, fp);
			fclose(fp);
			if (current.difficulty == 1) r = c = 2;
			else if (current.difficulty == 2) r = c = 4;
			calcWinVal();
			return 1;
		}
		else {
			fclose(fp);
			return 0;
		}
	}
	else {
		printf("EMPTY SLOT");
	}
}

void resumeGameList() {
	system("cls");
	for (int i = 0; i < slots; i++) {
		//rect(6, 1 + i * 3, 60, 2);
		if (midGameBitMap[i]) {
			int flag;
			FILE *fp = fopen("data", "rb+");
			fseek(fp, start2 + i * step, SEEK_SET);
			fread(&flag, sizeof(int), 1, fp);
			fread(&extra, sizeof(struct User), 1, fp);
			fclose(fp);
			gotoxy(45, 1 + i * 3);  printf("%d %s %d", extra.date, extra.month, extra.year);
			gotoxy(60, 1 + i * 3);  printf("%s", extra.name);
			gotoxy(75, 1 + i * 3);  printf("%s", extra.difficulty == 1 ? "2x2" : "4x4");
		}
		else {
			gotoxy(55, 1 + i * 3);  printf("EMPTY SLOT");
		}
	}
}

int resumeGameMenu() {
	setMidGameBits();
	int ptr = 0;
	do {
		resumeGameList();
		rect(40, ptr * 3, 45, 2);
		gotoxy(0, 0);
		int ch = _getch();
		switch (ch) {
		case 0:
		case 224:
			ch = _getch();
			switch (ch) {
			case UP_ARROW:
				ptr--;
				if (ptr < 0) ptr = slots - 1;
				break;

			case DOWN_ARROW:
				ptr++;
				if (ptr >= slots) ptr = 0;
				break;
			}
			break;

		case ENTER:
			if (midGameBitMap[ptr]) {
				loadMidGame(ptr);
				return 1;
			}
			break;

		case ESC:
			return 0;
			break;
		}
	} while (1);
}

void saveData() {
	int flag = 1;
	int addr = findFreeBit();
	setTime();
	FILE *fp = fopen("data", "rb+");
	fseek(fp, addr, SEEK_SET);
	fwrite(&flag, sizeof(int), 1, fp);
	fwrite(&current, sizeof(struct User), 1, fp);
	fclose(fp);
	setFreeBits();
	storeFreeBits();
}

int loadData() {
	FILE *fp = fopen("data", "rb+");
	int len = countFilledBits();
	if (len) {
		int flag;
		players = (struct User *)calloc(len, sizeof(struct User));
		for (int i = 0; i < limit; i++) {
			fseek(fp, start + i * step, SEEK_SET);
			fread(&flag, sizeof(int), 1, fp);
			if (flag) fread(&players[i], sizeof(struct User), 1, fp);
		}
		fclose(fp);
		return 1;
	}
	else {
		fclose(fp);
		return 0;
	}
}

void swapPlayers(struct User *player1, struct User *player2) {
	struct User temp = *player1;
	*player1 = *player2;
	*player2 = temp;
}

int compareBasedOnScore(struct User *player1, struct User *player2) {
	int score1 = player1->score;
	int score2 = player2->score;
	if (score1 > score2) {
		return 1;
	}
	else if (score1 < score2) {
		return 2;
	}
	else return 0;
}

int compareBasedOnMoves(struct User *player1, struct User *player2)  {
	int moves1 = player1->moves;
	int moves2 = player2->moves;
	if (moves1 > moves2) {
		return 1;
	}
	else if (moves1 < moves2) {
		return 2;
	}
	else return 0;
}

int compareBasedOnDate(struct User *player1, struct User *player2) {
	int cmp;
	if (player1->year > player2->year) {
		cmp = 1;
	}
	else if (player1->year < player2->year) {
		cmp = 2;
	}
	else {
		if (player1->month > player2->month) {
			cmp = 1;
		}
		else if (player1->month < player2->month) {
			cmp = 2;
		}
		else {
			if (player1->date > player2->date) {
				cmp = 1;
			}
			else if (player1->date < player2->date) {
				cmp = 2;
			}
			else {
				cmp = 0;
			}
		}
	}
	return cmp;
}

void quickSort(struct User *players, int start, int end, int compare(struct User *, struct User *)) {
	if (start <= end) {
		int i, lt, gt;
		i = lt = start;
		gt = end;
		while (i <= gt) {
			int cmp = compare(&players[i], &players[lt]);
			if (cmp == 1) {
				swapPlayers(&players[i++], &players[lt++]);
			}
			else if (cmp == 2) {
				swapPlayers(&players[i], &players[gt--]);
			}
			else if (cmp == 0){
				i++;
			}
		}
		quickSort(players, start, lt - 1, compare);
		quickSort(players, gt + 1, end, compare);
	}
}

void sortData(int ch) {
	switch (ch) {
	case 0:
		quickSort(players, 0, countFilledBits() - 1, &compareBasedOnDate);
		break;

	case 1:
		quickSort(players, 0, countFilledBits() - 1, &compareBasedOnMoves);
		break;

	case 2:
		quickSort(players, 0, countFilledBits() - 1, &compareBasedOnScore);
		break;
	}
}
