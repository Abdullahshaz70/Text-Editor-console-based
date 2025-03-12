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
    void readfromfile(const char* filename);

    void popBack();
    bool isLineEmpty(int lineIndex); 

    void indent(int lineIndex,int cursorColumn) {
        
        P[lineIndex]->indent(cursorColumn);
    }

    void unindent(int lineIndex, int cursorColumn) {

        P[lineIndex]->unindent(cursorColumn);
    }

    
    void printParagraph() {
        for (int i = 0; i < P.size(); ++i) {
            if (P[i] != nullptr) {
                P[i]->printLine();
                cout << endl;
            }
       
        }
        
    }

    char* getContent() const {
        int totalSize = 0;
        for (int i = 0; i < P.size(); i++) {
            totalSize += strsize(P[i]->getContent()) + 1;
        }

        char* content = new char[totalSize + 1]; 
        content[0] = '\0';

        for (int i = 0; i < P.size(); i++) {
            myStrcat(content, P[i]->getContent());
            if (i < P.size() - 1) myStrcat(content, "\n");
        }

        return content;
    }


    void Erase(int lineindex) {
        P.erase(P.begin() + lineindex);
    }

    void deleteline(int lineIndex) {
        P[lineIndex]->clear();
    }



    void searchPattern(char* pattern, bool forward);
    void moveToNextOccurrence();
    void moveToPreviousOccurrence();
    void searchAndReplace(const char* oldWord, const char* newWord);



};

