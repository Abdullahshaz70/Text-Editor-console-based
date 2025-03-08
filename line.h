#pragma once
#include"utility.h"
#include<fstream>

class line {
    char* Cs;

    int length=0;
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
    void indent(int cursorColumn);
 
    void unindent(int cursorColumn) {
        const int tabSize = 4;

        if (cursorColumn < tabSize)
            return; 
        int spacesToRemove = 0;
        for (int i = 0; i < tabSize; i++) {
            if (Cs[cursorColumn - (i + 1)] == ' ')
                spacesToRemove++;
            else
                break;
        }

        if (spacesToRemove == 0)
            return; 

        char* newCs = new char[length - spacesToRemove + 1] {};

    
        for (int i = 0; i < cursorColumn - spacesToRemove; i++)
            newCs[i] = Cs[i];

   
        for (int i = cursorColumn; i < length; i++)
            newCs[i - spacesToRemove] = Cs[i];

        newCs[length - spacesToRemove] = '\0';

        delete[] Cs;
        Cs = newCs;
        length -= spacesToRemove;
    }


    line* splitRight(int index);
    line* splitLeft(int index);

    char getCharAt(int index);   


    const char* getContent() const;
    
  
 //void stringcopy(const char* src) {
 //       if (src == nullptr)
 //           


 //       int length = 0;
 //       while (src[length] != '\0')
 //           length++;


 //       char* dest = new char[length + 1];
 //       for (int i = 0; i <= length; i++)
 //           dest[i] = src[i];

 //       src = nullptr;

 //       Cs = dest;
 //       dest = nullptr;
 //  }

 int strsize(const char* data) {
     int count = 0;
     for (int i = 0; data[i] != '\0'; i++)
         count++;

     return count;
 }
 bool isEmpty() {
     return Cs == nullptr or Cs[0] == '\0';
 }


 static int countDoubleEnter(line* lines[], int size);
};
