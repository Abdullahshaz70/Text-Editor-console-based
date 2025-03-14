#pragma once
#include"utility.h"
#include<fstream>
#include<iostream>
using namespace std;


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
    void unindent(int cursorColumn);
 

    line* splitRight(int index);
    line* splitLeft(int index);

    char getCharAt(int index);   


    const char* getContent() const;
    
  
    int strsize(const char* data);
    bool isEmpty();


    void updateline(const char* newText);

 void printLine(); 

 
};
