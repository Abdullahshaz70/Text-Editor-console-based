#pragma once
#include"section.h"
#include<vector>
using namespace std;
class chapter
{
	vector<section*> C;

public:
	chapter();
	~chapter();
	int chapterSize();

	void addSection();
	void addSection(section A);
	void addLine(int cursorRow);

	int sectionsize(int lineIndex);

	void insertline(int lineIndex, int columnIndex);
	void insertAt(int lineIndex, int columnIndex, char sym);
	
	void deleteAt(int lineIndex, int columnIndex);
	void deletefrom(int lineIndex, int columnIndex);
	void deleteline(int lineIndex);
	void Erase(int lineIndex);


	int findNextWord(int lineIndex, int columnIndex);
	int findPrevWord(int lineIndex, int columnIndex);
	void startOfLine(int lineIndex, int& index);
	void endOfLine(int lineIndex, int& index);


	int getSectionNumber(int lineIndex);
	int getLineSize(int lineIndex);
	int getTotalLines();
	int getPragraphSize(int lineIndex);
	line* getline(int lineindex);

	void copyLine(int lineIndex);
	void pasteLine(int lineIndex);

	void toggle(int lineIndex, int index);
	void indent(int lineIndex, int cursorColumn);
	void unindent(int lineIndex, int cursorColumn);

	void searchPattern(char* pattern, bool forward);
	void moveToNextOccurrence();
	void moveToPreviousOccurrence();
	void searchAndReplace(const char* oldWord, const char* newWord);

	char* getContent() const;

	section* getSection(int sectionIndex);

	void clear();
	void print();

	void printChapter();

	bool isLineEmpty(int lineIndex);

	

};

