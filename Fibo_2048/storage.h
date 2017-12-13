#include <stdio.h>
#include <stdlib.h>

int limit = 250;
int freeBitMap[5000];
int start = 22000;
int step = 1000;
int start2 = 300000;
int slots = 10;
int midGameBitMap[10];
int midGameBitsLocation = 400000;

void initializeFreeBitMap() {
	int flag = 0;
	FILE *fp = fopen("data", "rb+");
	for (int i = 0; i < limit; i++) {
		freeBitMap[i] = 1;
		fseek(fp, start2 + i * step, SEEK_SET);
		fwrite(&flag, sizeof(int), 1, fp);
	}
	fclose(fp);
}

void storeFreeBits() {
	FILE *fp = fopen("data", "rb+");
	fseek(fp, 0, SEEK_SET);
	fwrite(freeBitMap, sizeof(freeBitMap), 1, fp);
	fclose(fp);
}

void loadFreeBits() {
	FILE *fp = fopen("data", "rb+");
	fseek(fp, 0, SEEK_SET);
	fread(freeBitMap, sizeof(freeBitMap), 1, fp);
	fclose(fp);
}

void setFreeBits() {
	int flag;
	FILE *fp = fopen("data", "rb+");
	for (int i = 0; i < limit; i++) {
		fseek(fp, start + i * step, SEEK_SET);
		fread(&flag, sizeof(int), 1, fp);
		freeBitMap[i] = !flag;
	}
	fclose(fp);
}

int findFreeBit() {
	setFreeBits();
	for (int i = 0; i < limit; i++) {
		if (freeBitMap[i]) return start + i * step;
	}
	return start;
}

int countFilledBits() {
	int c = 0;
	for (int i = 0; i < limit; i++) {
		if (!freeBitMap[i]) c++;
	}
	return c;
}

void initializeMidGameMap() {
	int flag = 0;
	FILE *fp = fopen("data", "rb+");
	for (int i = 0; i < slots; i++) {
		midGameBitMap[i] = 0; 
		fseek(fp, start2 + i * step, SEEK_SET);
		fwrite(&flag, sizeof(int), 1, fp);
	}
	fclose(fp);
}

void storeMidGameBits() {
	FILE *fp = fopen("data", "rb+");
	fseek(fp, midGameBitsLocation, SEEK_SET);
	fwrite(midGameBitMap, sizeof(midGameBitMap), 1, fp);
	fclose(fp);
}

void loadMidGameBits() {
	FILE *fp = fopen("data", "rb+");
	fseek(fp, midGameBitsLocation, SEEK_SET);
	fread(midGameBitMap, sizeof(midGameBitMap), 1, fp);
	fclose(fp);
}

void setMidGameBits() {
	int flag;
	FILE *fp = fopen("data", "rb+");
	for (int i = 0; i < slots; i++) {
		fseek(fp, start2 + i * step, SEEK_SET);
		fread(&flag, sizeof(int), 1, fp);
		midGameBitMap[i] = flag;
	}
	fclose(fp);
}

int findMidGameBit() {
	setMidGameBits();
	for (int i = 0; i < slots; i++) {
		if (midGameBitMap[i] == 0) return start2 + i * step;
	}
	return start2;
}
