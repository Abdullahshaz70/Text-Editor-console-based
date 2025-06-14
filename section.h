#pragma once
#pragma once
#include<iostream>
#include<vector>
#include"paragraph.h"



class section
{
	vector <paragraph*> S;
	

	public:

		section();
		~section();
		int sectionSize();
		section(const section& other);
		void addparagraph();
		void addline(int cursorRow);

		void insertline(int lineIndex, int columnIndex);
		void insertAt(int lineIndex, int columnIndex, char sym);
	

		int getParagraphSize(int lineindex);
		int getTotalLines();
        int getParagraphNumber(int cursorRow);
		int getLineSize(int lineindex);
		line* getLine(int index);

		void deleteAt(int lineIndex, int columnIndex);

		void indent(int lineIndex, int cursorColumn);
		void unindent(int lineIndex, int cursorColumn);

		void toggle(int lineindex, int index);
		void copyLine(int lineIndex);
		void pasteLine(int lineIndex);

		int findnextword(int lineIndex, int columnIndex);
		int findprevword(int lineIndex, int columnIndex);
		void deleteFrom(int lineIndex, int columnIndex);
		void startOfLine(int lineIndex, int& columnIndex);
		void endOfLine(int lineIndex, int& columnIndex);

		void searchPattern(char* pattern, bool forward);
		void moveToNextOccurrence();
		void moveToPreviousOccurrence();
		void searchAndReplace(const char* oldWord, const char* newWord);

		void print(int i=0);
     
	


		void Erase(int paragraphIndex);

		void deleteline(int lineIndex);
		void writeToFile(const char* filename) const;


		char* getContent() const;

		bool isLineEmpty(int lineIndex);
		void printSection();

};

