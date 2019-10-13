#include "Functions.h"

void RandomFillingLog(int **field)
{
	srand(time(0));
	
	int ships[10] = { 4,3,3,2,2,2,1,1,1,1};
	int currentShip = 4;
	int count = 0;
	int randY , randX;
	bool put = true;  // Put current Ship to current cordinates;
	bool randomPosPlus = false; // Y == True , X == False ;
	
	while (count != 10)
	{
		put = true;
		
		////RandCordination
		randY = rand() % 10;
		randX = rand() % 10;
			
		if (field[randY][randX] == 0 )
		{
			randomPosPlus = rand() % 2;
	
			if (randomPosPlus == false)
			{
				if (randX + ships[count]  > 9)
					put = false;
				else 
					for (int y = randY - 1; y < randY + 2; y++)
						for (int x = randX - 1; x < randX + ships[count] + 1; x++)
							if (x >= 0 && x <= 9 && y >= 0 && y <= 9 && field[y][x] != 0)
								put = false;
			}
			else
			{
				if (randY + ships[count]  > 9)
					put = false;
				else 
					for (int y = randY - 1; y < randY + ships[count] + 1; y++)
						for (int x = randX - 1; x < randX + 2; x++)
							if (x >= 0 && x <= 9 && y >= 0 && y <= 9 && field[y][x] != 0)
								put = false;
			}
		}
		else
			put = false;
		
		//Put Current Ship to current Cordinates;
		if (put)
		{
			if (randomPosPlus)
				for (size_t i = 0; i < ships[count]; i++)			
					field[randY + i][randX] = currentShip;
	
			else
				for (size_t i = 0; i < ships[count]; i++)
					field[randY][randX + i] = currentShip;
	
			currentShip > ships[++count] ?currentShip = ships[count]:0;
		}
	}
}
void playerMove(int **field , int &key , int &CursorX , int &CursorY , int &turnCounter)
{
	if (key == 224)	//Rows
	{
		key = _getch();
		if (key == 72 && CursorY > 8)	//Up	
			CursorY--;
		
		if (key == 80 && CursorY < 17)	//Down
			CursorY++;
		
		if (key == 75 && CursorX > 6)	//Left
			CursorX-=2;
		
		if (key == 77 && CursorX < 24)	//Right
			CursorX+=2;
	}
	
	if (key == 13 && field[CursorY - 8][(CursorX - 6) / 2] == 0) //Empty
	{
		field[CursorY - 8][(CursorX - 6) / 2] = 5;
		turnCounter++;
	}
	else if (key == 13 && field[CursorY - 8][(CursorX - 6) / 2] < 5)	//Enter
		field[CursorY - 8][(CursorX - 6) / 2] += 5;
}
int winChecker(int **field , int turnCounter)
{
	int sumOfDestroyedShip = 0;
	bool destroyedHorizontalShip = true;
	bool destroyedVerticalShip = true;

	for (int y = 0; y < 10; y++)
		for (int x = 0; x < 10; x++)
		{
			destroyedHorizontalShip = true;
			destroyedVerticalShip = true;

			if (field[y][x] > 5 && field[y][x] < 20) //Destroyed one part of ship
			{
				for (int i = 0; i < field[y][x] - 5; i++) //Cheking does all parts of current ship destroyed.
				{
					if (x + field[y][x] - 5 - 1 > 9 || field[y][x + i] != field[y][x])
						destroyedHorizontalShip = false;

					if (y + field[y][x] - 5 - 1 > 9 || field[y + i][x] != field[y][x])
						destroyedVerticalShip = false;
				}
				if (destroyedHorizontalShip) //Puting 5 around destroyed Horizontal ship
				{
					for (int j = y - 1; j < y + 2; j++)
						for (int i = x - 1; i < x + field[y][x] - 5 + 1; i++)
							if (i <= 9 && i >= 0 && j <= 9 && j >= 0 && field[j][i] == 0)
								field[j][i] = 5;
				}
				if (destroyedVerticalShip) //Puting 5 around destroyed Vertical ship
				{
					for (int j = y - 1; j < y + 1 + field[y][x] - 5; j++)
						for (int i = x - 1; i < x + 2; i++)
							if (i <= 9 && i >= 0 && j <= 9 && j >= 0 && field[j][i] == 0)
									field[j][i] = 5;
				}
				if (destroyedVerticalShip || destroyedHorizontalShip)
					sumOfDestroyedShip++;
			}
		}	
	if (sumOfDestroyedShip == 10 )
	{
		POS(4, 17);
		if (turnCounter % 2 != 0)
			printf("%s", "*** FIRST PLAYER WIN ***");
		else
			printf("%s", "*** SECOND PLAYER WIN ***");
		POS(20, 17);
		exit(0);
	}
	return sumOfDestroyedShip;
}
void gameConsolGraphics()
{
	COLOR(BLUE, RED);
	for (size_t j = 1; j < 20; j++)
		for (size_t i = 2; i < 70; i++)
			if (j == 1 || j == 19 || i == 2 || i == 69 || i == 55)
			{
				POS(j, i);
				cout << char(177);
			}
	COLOR(GREEN, BLACK);
	POS(6, 6); cout << "A B C D E F G H I J";
	POS(7, 5); cout << "====================";
	POS(6, 35); cout << "A B C D E F G H I J";
	POS(7, 34); cout << "====================";
	POS(10, 56); cout << "* Destroyed";
	POS(11, 56); cout << "# Empty";
	POS(14, 56); cout << "1xBattleship";
	POS(15, 56); cout << "2xCruise";
	POS(16, 56); cout << "3xFrigate";
	POS(17, 56); cout << "4xMinesweeper";
}
void printFields( int **fieldPlayer1 ,  int **fieldPlayer2 )
{
	char ships[] = "OMFCB#";
	int tab = 6;
	for (size_t j = 0; j < 10; j++)
	{
		COLOR(GREEN, BLACK);
		POS(j + 8, 4); cout << j << "|";
		POS(j + 8, 33); cout << j << "|";
		for (size_t i = 0; i < 10; i++)
		{
			POS(j + 8, i + tab); //Pc Field or Second Player
			if (fieldPlayer2[j][i] > 5)
			{
				COLOR(RED, BLACK);
				cout << "*";

			}
			else if (fieldPlayer2[j][i] == 5)
			{
				COLOR(CYAN, BLACK);
				cout << "#";
			}
			else
			{
				COLOR(WHITE, BLACK);
				cout << "O";
			}
			POS(j + 8, i + tab + 29); // Player field
			if(fieldPlayer1[j][i] <= 5)
			{
				if (fieldPlayer1[j][i] == 0)
					COLOR(WHITE, BLACK);
				else if (fieldPlayer1[j][i] == 5)
					COLOR(CYAN, BLACK);
				else if (fieldPlayer1[j][i] < 5)
					COLOR(BLUE, BLACK);
				cout << ships[fieldPlayer1[j][i]];
			}
			else
			{
				COLOR(RED, BLACK);
				cout << "*";
			}
			tab++;
		}
		tab = 6;
	}
}
void pcAttackLogic(int **fieldPlayer1, int &turnCounter, bool &horizontalAttack, bool &verticalAttack, int pcDestroySum)
{
	int destroy_Y = -1, destroy_X = -1;
	////Try to destroy hited ship
	for (int y = 0; y < 10; y++)
		for (int x = 0; x < 10; x++)
			if (fieldPlayer1[y][x] > 5)
				for (int j = y - 1; j < y + 2; j++)
					for (int i = x - 1; i < x + 2; i++)
						if (j >= 0 && j <= 9 && i >= 0 && i <= 9 && fieldPlayer1[j][i] < 5)
							if (!(j > y && x < i || j < y && x > i || j < y && x < i || j > y && x > i))
							{
								if (horizontalAttack == true)
								{
									if (y == j)
									{
										destroy_Y = j;
										destroy_X = i;
									}
								}
								else if (verticalAttack == true)
								{
									if (x == i)
									{
										destroy_Y = j;
										destroy_X = i;
									}
								}
								else
								{
									destroy_Y = j;
									destroy_X = i;
									if (fieldPlayer1[destroy_Y][destroy_X] < 5 && fieldPlayer1[destroy_Y][destroy_X] != 0)
									{
										if (destroy_Y == y)
											horizontalAttack = true;
										else if (destroy_X == x)
											verticalAttack = true;
									}
								}
							}
	////Rand Shoot Cordination
	if (destroy_Y == -1 && destroy_X == -1)
		do
		{
			destroy_Y = rand() % 10;
			destroy_X = rand() % 10;
		} while (!(fieldPlayer1[destroy_Y][destroy_X] < 5));
	////Shooting
	if (fieldPlayer1[destroy_Y][destroy_X] == 0)
	{
		fieldPlayer1[destroy_Y][destroy_X] = 5;
		turnCounter++;
	}
	else if (fieldPlayer1[destroy_Y][destroy_X] < 5)
	{
		fieldPlayer1[destroy_Y][destroy_X] += 5;
		if (pcDestroySum < winChecker(fieldPlayer1, 2))
		{
			horizontalAttack = false;
			verticalAttack = false;
		}
	}
}
void gameWithPc(int &key, int &CursorX, int &CursorY , int **fieldPlayer1, int **fieldPlayer2)
{
	int turnCounter = 1;
	int pcDestroySum = NULL;
	bool horizontalAttack = false, verticalAttack = false;

	RandomFillingLog(fieldPlayer1);
	RandomFillingLog(fieldPlayer2);
	
	gameConsolGraphics();
	
	while (true)
	{
		printFields(fieldPlayer1, fieldPlayer2);
		POS(CursorY, CursorX);
		if (turnCounter % 2 != 0)
		{
			key = _getch();
			playerMove(fieldPlayer2, key, CursorX, CursorY , turnCounter);
			winChecker(fieldPlayer2 , turnCounter);
		}
		else
		{
			pcAttackLogic(fieldPlayer1 , turnCounter , horizontalAttack , verticalAttack, pcDestroySum);
			pcDestroySum = winChecker(fieldPlayer1, turnCounter);
		}
	}
}
void gameWithPlayer(int &key, int &CursorX, int &CursorY, int **fieldPlayer1, int **fieldPlayer2)
{
	int turnCounter = 1;
	int pcDestroySum = NULL;
	bool horizontalAttack = false, verticalAttack = false;

	RandomFillingLog(fieldPlayer1);
	RandomFillingLog(fieldPlayer2);

	gameConsolGraphics();

	while (true)
	{
		if (turnCounter % 2 != 0) // First Player
		{
			POS(4, 7); printf("%s", "* First Player * ");
			printFields(fieldPlayer1, fieldPlayer2);
			POS(CursorY, CursorX);

			key = _getch();
			playerMove(fieldPlayer2, key, CursorX, CursorY, turnCounter);
			winChecker(fieldPlayer2, turnCounter);
		}
		else // Second Player
		{
			POS(4, 7); printf("%s", "* Second Player *");
			printFields(fieldPlayer2, fieldPlayer1);
			POS(CursorY, CursorX);
			key = _getch();
			playerMove(fieldPlayer1, key, CursorX, CursorY, turnCounter);
			winChecker(fieldPlayer1, turnCounter);
		}
	}
}
void mainMenu(int &key, int &CursorX, int &CursorY, int **fieldPlayer1, int **fieldPlayer2)
{
	//Frame
	COLOR(GREEN, BLACK);
	POS(5, 6); cout << " ______  ___ _____ _____ _      _____ " << endl;
	POS(6, 6); cout << " | ___ \\/ _ \\_   _|_   _| |    |  ___|" << endl;
	POS(7, 6); cout << " | |_/ / /_\\ \\| |   | | | |    | |__  " << endl;
	POS(8, 6); cout << " | ___ \\  _  || |   | | | |    |  __| " << endl;
	POS(9, 6); cout << " | |_/ / | | || |   | | | |____| |___ " << endl;
	POS(10, 6); cout << " \\____/\\_| |_/\\_/   \\_/ \\_____/\\____/ " << endl;
	POS(11, 6); cout << "       _____ _   _ ___________       " << endl;
	POS(12, 6); cout << "      /  ___| | | |_   _| ___ \\      " << endl;
	POS(13, 6); cout << "      \\ `--.| |_| | | | | |_/ /      " << endl;
	POS(14, 6); cout << "       `--. \\  _  | | | |  __/       " << endl;
	POS(15, 6); cout << "      /\\__/ / | | |_| |_| |          " << endl;
	POS(16, 6); cout << "      \\____/\\_| |_/\\___/\\_|       " << endl;
	
	for (size_t j = 0; j < 20; j++)
		for (size_t i = 0; i < 40; i++)
			if (j == 0 || j == 19 || i == 0 || i == 39)
			{
				POS(j + 2, i + 5);
				cout << char(176);
			}

	int selected = 0;
	char menu[3][17] = {
		"  Player Vs PC  ",
		"   Two Player   ",
		"      Exit      ",
	};
	
	while (key != 13)
	{
		for (size_t i = 0; i < 3; i++)
		{
			POS(i + 18, 17);
			COLOR(DEFAULT, BLACK);
			if (selected == i)
				COLOR(GREEN,RED);
		cout << menu[i];
		}
		key = _getch();
		if (key == 224)
		{
			key = _getch();
			if (key == 72 && selected > 0)
				selected--;
			if (key == 80 && selected < 2)
				selected++;
		}
	}
	system("cls");
	if (selected == 0)
		gameWithPc(key, CursorX, CursorY, fieldPlayer1, fieldPlayer2);
	else if (selected == 1)
		gameWithPlayer(key, CursorX, CursorY, fieldPlayer1, fieldPlayer2);
	else
		exit(0);
}
