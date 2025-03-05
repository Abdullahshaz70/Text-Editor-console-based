#pragma once
#include"utility.h"
#include<fstream>

class line {
    char* Cs;
    char* copyLine;
    int length;
public:
    
    int MAX_LENGHT = 10;

    line();
    ~line();
    line(const char* data);
    int size();

    void stringcopy(const char* src);
    void insertAt(int index, char sym);    
    void deleteAt(int index);              
    void deleteFrom(int index);
    void printline();
    void clear();
    void clearLine(int row, int col, int lineLength);

    int findNextWord(int index);           
    int findPrevWord(int index);  
    void startofLine(int& index);
    void endofLine(int& index);
    void toggle(int index);

    void CopyLine();
    void pasteLine();

    line* splitRight(int index);
    line* splitLeft(int index);

    char getCharAt(int index);   


   

    const char* getContent() const {
        return Cs;
    }
    //const char* getText() const {
    //    return Cs; // Return the text as a C-style string
    //}
};
