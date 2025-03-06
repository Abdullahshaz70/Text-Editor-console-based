#pragma once
#include"utility.h"
#include<fstream>

class line {
    char* Cs;

    int length;
public:
    
    int MAX_LENGHT = 20;

    line();
    line(const char* data);
    ~line();
    int size();

    
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
    void indent();
 

    line* splitRight(int index);
    line* splitLeft(int index);

    char getCharAt(int index);   


    const char* getContent() const;
    
  
 void stringcopy(const char* src) {
        if (src == nullptr)
            


        int length = 0;
        while (src[length] != '\0')
            length++;


        char* dest = new char[length + 1];
        for (int i = 0; i <= length; i++)
            dest[i] = src[i];

        src = nullptr;

        Cs = dest;
        dest = nullptr;
    }
};
