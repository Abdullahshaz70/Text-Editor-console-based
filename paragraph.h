#pragma once
#include<iostream>
#include<vector>
#include"line.h"
#include"utility.h"



using namespace std;
class paragraph
{
	vector <line*> P;
    static char* copyLine ;



    int lastFoundIndex = -1;  

    char* lastPattern = new char[100] {};

    

public:

    paragraph();
    paragraph(const char* c);
    paragraph(const paragraph& other);

	void insertAt(int lineIndex, int columnIndex, char sym);
	void deleteAt(int lineIndex, int columnIndex);
	void deletefrom(int lineIndex, int columnIndex);
	int paragraphSize();

	line* getLine(int index);
	void addline(); 
	void addline(const char* c); 

	void insertline(int lineIndex, int columnIndex);
	int findnextword(int lineIndex, int columnIndex);
	int findprevword(int lineIndex, int columnIndex);
	void startofline(int lineIndex, int& index);
	void endofline(int lineIndex, int& index);

	void Toggle(int lineIndex, int index);
	void printLine(int lineIndex);
	int getlinesize(int lineIndx);

    static void CopyLine(paragraph& P, int lineIndex);

    void pasteLine(int lineindex);

  


	void writeToFile(const char* filename) const; 

    void popBack();
    bool isLineEmpty(int lineIndex); 

    void indent(int lineIndex, int cursorColumn);
    void unindent(int lineIndex, int cursorColumn);

    
    void printParagraph();
    void Erase(int lineindex);

    char* getContent() const;
   

    void deleteline(int lineIndex);



    void searchPattern(char* pattern, bool forward);
    void moveToNextOccurrence();
    void moveToPreviousOccurrence();
    void searchAndReplace(const char* oldWord, const char* newWord);



};

