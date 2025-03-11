#pragma once
#include"chapter.h"
#include<vector>
class document {
private:
    vector<chapter*> D;

public:
    document();
    ~document();

    int documentSize();
    void addChapter();
    void addChapter(chapter A);
    void addLine(int cursorRow);
    void clear();

    void deleteAt(int lineIndex, int columnIndex);
    void deleteFrom(int lineIndex, int columnIndex);
    void deleteLine(int lineIndex);

    void insertAt(int lineIndex, int columnIndex, char sym);
    void insertLine(int lineIndex, int columnIndex);

    int getChapterNumber(int lineIndex);
    int getLineSize(int lineIndex);
    int getTotalLines();

    void Erase(int lineIndex);

    int findNextWord(int lineIndex, int columnIndex);
    int findPrevWord(int lineIndex, int columnIndex);
    void startOfLine(int lineIndex, int& columnIndex);
    void endOfLine(int lineIndex, int& columnIndex);

    void copyLine(int lineIndex);
    void pasteLine(int lineIndex);

    void toggle(int lineIndex, int index);
    void indent(int lineIndex, int cursorColumn);
    void unindent(int lineIndex, int cursorColumn);

    void searchPattern(char* pattern, bool forward);
    void moveToNextOccurrence();
    void moveToPreviousOccurrence();
    void searchAndReplace(const char* oldWord, const char* newWord);

    void writeToFile(const char* filenanme);
    //void readFromFile(const char* filenanme);
    void print();


    void sectionSize(int lineIndex);
  
};
