#pragma once


class line {
    char* Cs;
    int length;
    int MAX_LENGHT = 10;
public:
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

    int findNextWord(int index);           
    int findPrevWord(int index);          
    char getCharAt(int index);   


};
