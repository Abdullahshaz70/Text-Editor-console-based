#include "line.h"
#include"utility.h"
#include <iostream>


using namespace std;


line::line() {
    Cs = new char[1];
    Cs[0] = '\0';
    length = 0;
}
line::line(const char* data) {

    Cs = new char[strsize(data) + 1] {};
    stringcopy(data);
   
}

line::~line() {
    clear();
}

void line::clear() {
    delete[] Cs; 
    Cs = new char[1]; 
    Cs[0] = '\0'; 
    length = 0; 
}

void line::clearLine(int row, int col, int lineLength) {
    gotoRowCol(row, col);
    for (int i = 0; i < lineLength; i++) 
        cout << ' '; 
    gotoRowCol(row, col);
}

int line::size() {
    int count = 0;
    for (int i = 0; Cs[i] != '\0'; i++)
        count++;
    return count;
}

void line::printline() {
    for (int i = 0; i < size(); i++)
        cout<<Cs[i];
}


void line::insertAt(int index, char sym) {
    char* newChar = new char[length + 2];

    for (int i = 0; i < index; i++)
        newChar[i] = Cs[i];

    newChar[index] = sym;

    for (int i = index; i < length; i++)
        newChar[i + 1] = Cs[i];

    newChar[length + 1] = '\0';
    delete[] Cs;
    Cs = newChar;
    length++;
}
void line::deleteAt(int index) {
    if (index < 0 or index >= length)
        return;

    for (int i = index; i < length - 1; i++)
        Cs[i] = Cs[i + 1];

    Cs[length - 1] = '\0';
    length--;
}
void line::deleteFrom(int index) {
    if (index < 0 or index >= length)
        return;

    Cs[index] = '\0';
    length = index;
    
}
int line::findNextWord(int index) {
    while (index < length and !isDelimiter(Cs[index]))
        index++;

    while (index < length and isDelimiter(Cs[index]))
        index++;

    return index;
}
int line::findPrevWord(int index) {
    while (index > 0 and !isDelimiter(Cs[index]))
        index--;

    while (index > 0 and isDelimiter(Cs[index]))
        index--;

    while (index > 0 and !isDelimiter(Cs[index]))
        index--;

    return (index > 0) ? index + 1 : 0;
}
char line::getCharAt(int index) {
    if (index < 0 or index >= length)
        return '\0';
    return Cs[index];
}

void line::stringcopy(const char* src) {
    if (src == nullptr) {
        Cs = nullptr;
        return;
    }

    int length = 0;
    while (src[length] != '\0')
        length++;

    delete[] Cs; 
    Cs = new char[length + 1]; 

    for (int i = 0; i <= length; i++)
        Cs[i] = src[i];
}