#pragma once
#include<iostream>
#include<vector>
#include"line.h"
using namespace std;
class paragraph
{
	vector <line*> P;

public:

	void insertAt(int lineIndex, int columnIndex, char sym);
	void deleteAt(int lineIndex, int columnIndex);
	void deletefrom(int lineIndex, int columnIndex);
	int paragraphSize();

	line* getLine(int index);
	void addline();

	//void insertline(int index);
	void toggle(int lineIndx, int colunIndex);
	void insertline(int lineIndex, int columnIndex);


	int findnextword(int lineIndex, int columnIndex);
	int findprevword(int lineIndex, int columnIndex);

	void startofline(int lineIndex, int& index);
	void endofline(int lineIndex, int& index);
	void Toggle(int lineIndex, int index);

	void printLine(int lineIndex);

	int getlinesize(int lineIndx);






	void printParagraph();
};

