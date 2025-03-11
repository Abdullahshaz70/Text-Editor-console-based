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

    char* getContent() const {
        int totalSize = 0;
        for (int i = 0; i < D.size(); i++) {
            char* chapContent = D[i]->getContent();
            totalSize += strsize(chapContent) + 4; // +4 for chapter separator "\n\n\n\n"
            delete[] chapContent;
        }

        char* content = new char[totalSize + 1]; // Extra space for '\0'
        content[0] = '\0';

        for (int i = 0; i < D.size(); i++) {
            char* chapContent = D[i]->getContent();
            myStrcat(content, chapContent);
            if (i < D.size() - 1) myStrcat(content, "\n\n\n\n"); // Separate chapters
            delete[] chapContent;
        }

        return content;
    }


    void sectionSize(int lineIndex);
  
};
