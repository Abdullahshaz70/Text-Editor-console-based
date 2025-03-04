#pragma once


class line {
    char* Cs;
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
    char getCharAt(int index);   


};
