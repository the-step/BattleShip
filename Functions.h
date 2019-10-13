#pragma once
#include <iostream>
#include <conio.h>
#include <time.h>
#include <windows.h>
using namespace std;

#define POS(rows,cols) SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),{short(cols),short(rows)})
#define COLOR(fg, bg) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), bg * 16 + fg)

enum Color
{
	BLACK,
	DARKBLUE,
	DARKGREEN,
	DARKCYAN,
	DARKRED,
	DARKMAGENTA,
	BROWN,
	LIGHTGREY,
	DARKGREY,
	BLUE,
	GREEN,
	CYAN,
	RED,
	MAGENTA,
	YELLOW,
	WHITE,
	DEFAULT = 7
};

void mainMenu(int &key, int &CursorX, int &CursorY, int **fieldPlayer1, int **fieldPlayer2);
void RandomFillingLog(int **field);
void playerMove(int **field, int &key, int &CursorX, int &CursorY, int &turnCounter);
int winChecker(int **field, int turnCounter);
void pcAttackLogic(int **fieldPlayer1, int &turnCounter, bool &horizontalAttack, bool &verticalAttack, int pcDestroySum);
void gameWithPc(int &key, int &CursorX, int &CursorY, int **fieldPlayer1, int **fieldPlayer2);
void gameWithPlayer(int &key, int &CursorX, int &CursorY, int **fieldPlayer1, int **fieldPlayer2);
void gameConsolGraphics();
void printFields(int **fieldPlayer1, int **fieldPlayer2);