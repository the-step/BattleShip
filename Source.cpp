#include "Functions.h"

int key;
int CursorX = 16, CursorY = 10;

void main()
{
	int** fieldPlayer1 = new int*[10];
	int**fieldPlayer2 = new int*[10];
	for (int i = 0; i < 10; ++i)
	{
		fieldPlayer1[i] = new int[10]{};
		fieldPlayer2[i] = new int[10]{};
	}
	mainMenu(key, CursorX, CursorY, fieldPlayer1, fieldPlayer2);
}
