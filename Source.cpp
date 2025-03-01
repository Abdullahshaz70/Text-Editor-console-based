#include <iostream>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include <math.h>
#include<vector>
#include "line.h"



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
	
	int cursorRow = 0 ,cursorColumn = 0;

	line A;
	
	while (true) {
		if (_kbhit()) {

			char sym = _getch();

			switch (sym) {
				case 'h':  
					cursorColumn--;
					if (cursorColumn == -1)
						cursorColumn = 0;
					
					gotoRowCol(cursorRow, cursorColumn);
					break;

				case 'l': 
					if (A.Cs.size() != cursorColumn)
						cursorColumn++;
					gotoRowCol(cursorRow, cursorColumn);
					break;

				case 8:  
					if (cursorColumn > 0) {
						delete A.Cs[cursorColumn - 1];
						A.Cs.erase(A.Cs.begin() + cursorColumn - 1);
						cout << " ";
						cursorColumn--;
					}

					system("cls");
					for (int i = 0; i < A.Cs.size(); i++) {
						gotoRowCol(cursorRow, i);
						cout << A.Cs[i];
					}
					break;

				default:  
					char* newChar = new char[2];
					newChar[0] = sym;
					newChar[1] = '\0';

					A.Cs.insert(A.Cs.begin() + cursorColumn, newChar);
					cursorColumn++;

					system("cls");
					for (int i = 0; i < A.Cs.size(); i++) {
						gotoRowCol(cursorRow, i);
						cout << A.Cs[i];
					}

					gotoRowCol(cursorRow, cursorColumn);
					break;
			}

			
					

		}

	}
	
	

	return 0;
}









































//if (sym == 'h')
			//{
			//	cursorColumn--;
			//	if (cursorColumn == -1)
			//		cursorColumn=0;
			//
			//	gotoRowCol(cursorRow, cursorColumn);
			//}
			//else if (sym == 'l') {
			//
			//	if(A.Cs.size()!=cursorColumn)
			//		cursorColumn++;
			//
			//	gotoRowCol(cursorRow, cursorColumn);
			//
			//}
			//else if (int(sym) == 8) {
			//
			//	if (cursorColumn > 0) {
			//
			//		delete A.Cs[cursorColumn-1];
			//		A.Cs.erase(A.Cs.begin() + cursorColumn-1);
			//		cout << " ";
			//		//gotoRowCol(cursorRow, cursorColumn);
			//		cursorColumn--;
			//	}
			//
			//	system("cls");
			//	for (int i = 0; i < A.Cs.size(); i++) {
			//		gotoRowCol(cursorRow, i);
			//		cout << A.Cs[i];
			//	}
			//}
			//else {
			//	char* newChar = new char[2]; 
			//	newChar[0] = sym;
			//	newChar[1] = '\0'; 
			//
			//	A.Cs.insert(A.Cs.begin() + cursorColumn, newChar);
			//	cursorColumn++;
			//
			//
			//	system("cls");
			//	for (int i = 0; i < A.Cs.size(); i++) {
			//		gotoRowCol(cursorRow, i);
			//		cout << A.Cs[i];
			//	}
			//
			//
			//	gotoRowCol(cursorRow, cursorColumn);
		//
			//}