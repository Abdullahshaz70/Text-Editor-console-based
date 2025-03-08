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

bool islower(char c) {
	return c >= 'a' and c <= 'z';
}
bool isUpper(char c) {
	return c >= 'A' and c <= 'Z';
}

int strsize(const char* data) {
	int count = 0;
	for (int i = 0; data[i] != '\0'; i++)
		count++;

	return count;
}


void stringcopy(char* destination, const char* source) {
	if (!source or !destination) return; 

	int i = 0;
	while (source[i] != '\0') { 
		destination[i] = source[i];
		i++;
	}
	destination[i] = '\0'; 
}


bool isDelimiter(char c) {
	return (c == ' ' or c == '\t' or c == '\n' or c == '.' or c == ',' or
		c == ';' or c == ':' or c == '!' or c == '?' or c == '(' or c == ')' or
		c == '{' or c == '}' or c == '[' or c == ']' or c == '"' or c == '\'' or
		c == '-' or c == '_');
}

bool wordFinder(const char* S1, const char* S2) {
	if (!S1 or !S2 or *S2 == '\0') 
		return false; 

	for (int i = 0; S1[i] != '\0'; ++i) {
		int j = 0;


		while (S1[i + j] != '\0' and S2[j] != '\0' and S1[i + j] == S2[j]) 
			j++;
		

		if (S2[j] == '\0') 
			return true; 
	}

	return false; 
}
