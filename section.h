#pragma once
#pragma once
#include<iostream>
#include<vector>
#include"paragraph.h"



class section
{
	vector <paragraph*> S;
	int paragraphnumber = 0;

	public:

		void addparagraph();



		void insertAt(int paragraphIndex, int lineIndex, int columnIndex, char sym);
        int getParagraphNumber(int cursorRow);
		void deleteAt(int paragraphIndex, int lineIndex, int columnIndex);

		void insertparagraph(int paragraphIndex, int lineIndex, int columnIndex);
		int getlineSize(int paragraphIndex, int lineIndex);

		void printSection(int lineIndex);
     
		
};

