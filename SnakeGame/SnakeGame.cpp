// SnakeGame.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "iostream"
#include "iomanip"
#include "stdlib.h"
#include "ctime"
#include "windows.h"
#include "conio.h"
#pragma comment(lib, "Winmm.lib")






using namespace std;

int const w = 70;
int const h = 20;
int stopgame, fruitX, fruitY, score, x, y, dir, speed, speed2;
char a[h][w], otvet;
int tailX[100], tailY[100];
int tailSize;



enum knopki {STOP = 0, LEFT, RIGHT, UP, DOWN};

enum ConsoleColor
{
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};

//int color = system("color 00");






void setup() {
	stopgame = false;
	dir = STOP;
	x = w / 2;
	y = h / 2;
	srand(unsigned(time(NULL)));
	fruitX = rand() % 65 + 2;
	fruitY = rand() % 15 + 2;
	speed = 70;
	speed2 = 80;

	PlaySound(L"qwer.wav", NULL, SND_ASYNC);
	
}

void matrix() {

	
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			
			if (i == 0 || i == h - 1)
			{
				

				a[i][j] = char(219);
				
			}
			
			else
				if (j == 0 || j == w - 1) {
					a[i][j] = char(219);
				}
				else a[i][j] = ' ';


		}
	}
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			if (i == y && j == x) {
				
				a[i][j] = char(219);
				
				
			}
			
			
			
			if (i == fruitY && j == fruitX) {
			
				a[i][j] = char(254);
				
			}
			else
				for (int k = 0; k < tailSize; k++) {
					if (tailX[k] == j && tailY[k] == i) {
					
						a[i][j] = char(219);
					}
				}
			
			/*if (score == 1000) {
				a[15][15] = '#';
				}*/
			
			
			
			}
		}

	
	}

	



void show() {
	
	HANDLE hCon;
	COORD coord;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	coord.X = 0;
	coord.Y = 0;
	SetConsoleCursorPosition(hCon, coord);

	CONSOLE_CURSOR_INFO I;
	GetConsoleCursorInfo(hCon, &I);
	I.bVisible = FALSE;
	SetConsoleCursorInfo(hCon, &I);
	SetConsoleTextAttribute(hCon, FOREGROUND_GREEN);
	
	
	
	
	for (int i = 0; i < h; i++) {
		std::cout << setw(28);
		
		for (int j = 0; j < w; j++) {
			
			
		
			std::cout << a[i][j];
		

			}
			
		std::cout << endl;
		}

	
		
	
	
	std::cout << setw(34) << "Score: " << score << endl;
	
	std::cout << endl;
}

void input() {
	Sleep(speed);
	
	if (_kbhit()) {

		switch (_getch()) {

		case 'a': dir = LEFT;
			break;
		case 'd': dir = RIGHT;
			break;
		case 's': dir = DOWN;
			
			break;
		case 'w': dir = UP;
			
			break;
		case 'e': exit(0);
			break;
		case 'p': 
			
			cout << setw(64) << "P A U S E" << endl;
			PlaySound(NULL, NULL, SND_FILENAME);
			system("pause");
			system("cls");
		}


	}
	
	
			
	
}

void logic() {
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < tailSize; i++) {
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir) {
	case LEFT: x--;
		break;
	case RIGHT: x++;
		break;
	case DOWN: y++;
		Sleep(speed2);
		break;
	case UP: y--;
		Sleep(speed2);
		break;


	}

	if (x == fruitX && y == fruitY) {
		/*PlaySound(L"Monetki.wav", NULL, SND_ASYNC);*/
	
		score += 100;
		srand(unsigned(time(NULL)));
		fruitX = rand() % 65 + 2;
		fruitY = rand() % 15 + 2;
		tailSize++;
		if (speed != 10) {
			speed -= 10;
			speed2 -= 10;
		}
		

	}
	
	

	
}





int main()
{
	
		
	
	score = 0;
	system("cls");
    setup();
	tailX[100] = NULL;
	tailY[100] = NULL;
	while (!stopgame) {

		matrix();
		show();
		input();
		logic();

		if (x >= w - 1 || x <= 0 || y >= h - 1 || y <= 0) {
			PlaySound(L"Gameover", NULL, SND_SYNC);
			
			stopgame = true;
		m:	speed = 150;
			cout << setw(69) << "G A M E  O V E R" << endl;
			cout << endl;
			cout << setw(80) << "Do you want to play again? ( y / n ) ";
			cin >> otvet;
			switch (otvet) {
			case 'y':
				return main();

			case 'n':
				return 0;
			
			}


		}
		for (int k = 0; k < tailSize; k++) {
			
			if ( x == tailX[k] && y == tailY[k]) {
				PlaySound(L"Gameover", NULL, SND_SYNC);
			
				stopgame = true;
				goto m;
				break;
			
			}
			}

	
	}
		
 
			
	
	return 0;
}

