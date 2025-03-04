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

	line* getLine(int index);
	void addline();
	void insertline(int index);
	void printParagraph();
};

