#include <iostream>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include <math.h>
#include<vector>
using namespace std;

void getRowColbyLeftClick(int& rpos, int& cpos)
{
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD Events;
	INPUT_RECORD InputRecord;
	SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT |
		ENABLE_EXTENDED_FLAGS);
	do
	{
		ReadConsoleInput(hInput, &InputRecord, 1, &Events);
		if (InputRecord.Event.MouseEvent.dwButtonState ==

			FROM_LEFT_1ST_BUTTON_PRESSED)

		{
			cpos = InputRecord.Event.MouseEvent.dwMousePosition.X;
			rpos = InputRecord.Event.MouseEvent.dwMousePosition.Y;
			break;
		}
	} while (true);
}
void gotoRowCol(int rpos, int cpos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = cpos;
	scrn.Y = rpos;
	SetConsoleCursorPosition(hOuput, scrn);
}
void hideConsoleCursor()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(hConsole, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(hConsole, &cursorInfo);
}
void color(int k)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, k);
}

int main() {

	int cursorRow = 0, cursorColumn = 0, documnetLine = 0;
	
	vector<vector<char>*> Document;
	vector <char>* v = new vector<char>{};

	Document.push_back(v);

	while (true) {

		if (_kbhit()) {
			int key = _getch();

			if (key == 224) {
				key = _getch();

				switch (key) {
				case 72:
					cursorRow--;
					break;
				case 80:
					cursorRow++;
					break;
				case 77:
					cursorColumn++;
					break;
				case 75:
					cursorColumn--;
					break;

				}
				gotoRowCol(cursorRow, cursorColumn);
			}
			else {
				char sym = (char)key;
				gotoRowCol(cursorRow, cursorColumn);
				cout << sym;
			}

		}

	}

	return 0;
}