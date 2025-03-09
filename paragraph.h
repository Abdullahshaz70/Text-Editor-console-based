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
                cout << P[i]->getContent(); 
                cout << endl; 
            }
            else if (P[i]->isEmpty()) {
                cout <<" ";
                
            }
            
        }
    }


    void Erase(int lineindex) {
        P.erase(P.begin() + lineindex);
    }

    void deleteline(int lineIndex) {
        P[lineIndex + 1]->clear();
    }
    paragraph& operator=(const paragraph& other) {
        if (this != &other) { 
            for (int i = 0; i < P.size(); i++) {
                delete P[i];
            }
            P.clear();

          
            for (int i = 0; i < other.P.size(); i++) {
                P.push_back(new line(*other.P[i])); \
            }
        }
        return *this;
    }
  

    void searchPattern(char* pattern, bool forward) {
        if (!pattern or strsize(pattern) == 0) return; 

        stringcopy(lastPattern, pattern);

        int start = forward ? 0 : P.size() - 1;
        int end = forward ? P.size() : -1;
        int step = forward ? 1 : -1;

        for (int i = start; i != end; i += step) {
            if (wordFinder(P[i]->getContent(), pattern)) { 
                lastFoundIndex = i;  
              cout << "Found in Line " << i + 1 << ": " << P[i]->getContent() << endl;
                return;
            }
        }

       cout << "Pattern not found!\n";
        lastFoundIndex = -1;  
    }
    void moveToNextOccurrence() {

        if (strsize(lastPattern) == 0 or lastFoundIndex == -1) {
         cout << "No previous search!\n";
            return;
        }

        for (int i = lastFoundIndex + 1; i < P.size(); ++i) {
            if (wordFinder(P[i]->getContent(), lastPattern)) {
                lastFoundIndex = i;
             cout << "Next occurrence in Line " << i + 1 << ": " << P[i]->getContent() << endl;
                return;
            }
        }

        cout << "No more occurrences found!\n";
    }
    void moveToPreviousOccurrence() {
        if (strsize(lastPattern) == 0 or lastFoundIndex == -1) {
            cout << "No previous search!\n";
            return;
        }

        for (int i = lastFoundIndex - 1; i >= 0; --i) {
            if (wordFinder(P[i]->getContent(), lastPattern)) {
                lastFoundIndex = i;
                cout << "Previous occurrence in Line " << i + 1 << ": " << P[i]->getContent() << endl;
                return;
            }
        }

        cout << "No previous occurrences found!\n";
    }
    void searchAndReplace(const char* oldWord, const char* newWord) {
        int oldLen = 0, newLen = 0;

        
        while (oldWord[oldLen] != '\0') oldLen++;
        while (newWord[newLen] != '\0') newLen++;

        for (int i = 1; i < P.size(); i++) {
            line* currentLine = P[i];
            int lineLength = currentLine->size();
            const char* content = currentLine->getContent();

           
            char* newContent = new char[lineLength * 2];
            int newIndex = 0, j = 0;

            while (j < lineLength) {
                bool match = true;

                for (int k = 0; k < oldLen; k++) {
                    if (content[j + k] == '\0' || content[j + k] != oldWord[k]) {
                        match = false;
                        break;
                    }
                }

               
                if (match) {
                    for (int k = 0; k < newLen; k++)
                        newContent[newIndex++] = newWord[k];

                    j += oldLen; 
                }
                else {
                    newContent[newIndex++] = content[j++];
                }
            }

            newContent[newIndex] = '\0';  
            P[i]->updateline(newContent);
           
           
        }
    }



};

