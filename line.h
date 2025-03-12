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
    
  
 int strsize(const char* data) {
     int count = 0;
     for (int i = 0; data[i] != '\0'; i++)
         count++;

     return count;
 }
 bool isEmpty() {
     return Cs == nullptr or Cs[0] == '\0';
 }


 void updateline (const char* newText) {
     int newLength = 0;
     while (newText[newLength] != '\0') newLength++; 

     char* newCs = new char[newLength + 1];
     for (int i = 0; i < newLength; i++)
         newCs[i] = newText[i];

     newCs[newLength] = '\0'; 

     delete[] Cs; 
     Cs = newCs;  
     length = newLength; 
 }

 void printLine() {
     for (int i = 0; i < size(); i++) {
         cout << Cs[i] ;
     }
 
 }

 
};
