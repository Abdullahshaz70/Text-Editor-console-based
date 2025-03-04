#include"utility.h"



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


int strsize(const char* data) {
	int count = 0;
	for (int i = 0; data[i] != '\0'; i++)
		count++;

	return count;
}

//char* stringcopy(const char* src) {
//	if (src == nullptr) 
//		return nullptr; 
//	
//
//	int length = 0;
//	while (src[length] != '\0') 
//		length++;
//	
//
//	char* dest = new char[length + 1];
//	for (int i = 0; i <= length; i++) 
//		dest[i] = src[i];
//	
//
//	return dest; 
//}


bool isDelimiter(char c) {
	return (c == ' ' || c == '\t' || c == '\n' || c == '.' || c == ',' ||
		c == ';' || c == ':' || c == '!' || c == '?' || c == '(' || c == ')' ||
		c == '{' || c == '}' || c == '[' || c == ']' || c == '"' || c == '\'' ||
		c == '-' || c == '_');
}


