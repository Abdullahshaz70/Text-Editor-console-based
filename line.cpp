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

    if (data) {
        length = strsize(data);
        Cs = new char[length + 1];
        //stringcopy(data);

        for (int i = 0; i < length; i++) {
            Cs[i] = data[i];
        }
        Cs[length] = '\0';  

    }
    else {
        Cs = new char[1];
        Cs[0] = '\0'; 
    }
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
    return length;
}
void line::printline() {
    for (int i = 0; i < size(); i++)
        cout<<Cs[i];
}


void line::insertAt(int index, char sym) {
    if (index < 0 or index > length) 
        return;

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

void line::printLine() {
    for (int i = 0; i < size(); i++) {
        cout << Cs[i];
    }

}

void line::deleteAt(int index) {
    if (index < 0 || index >= length || Cs == nullptr)
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
void line::toggle(int index) {
    if (index < 0 || index >= length || Cs == nullptr)
        return;

    if (islower(Cs[index])) 
        Cs[index] = Cs[index] - 32;
    else if(isupper(Cs[index]))
        Cs[index] = Cs[index] + 32;

}
void line::startofLine(int& index) {
    index = 0;
}
void line::endofLine(int& index) {
    index = size();
}

line* line::splitLeft(int index) {
    line* newLine = new line();

    if (index < 0 or index > length)
        return newLine;

    newLine->length = index;
    newLine->Cs = new char[newLine->length + 1];

    for (int i = 0; i < newLine->length; i++)
        newLine->Cs[i] = Cs[i];

    newLine->Cs[newLine->length] = '\0';

   
    return newLine;
}
line* line::splitRight(int index) {
    line* newLine = new line();

    if (index < 0 or index > length)
        return newLine;

    newLine->length = length - index;
    newLine->Cs = new char[newLine->length + 1];

    for (int i = 0; i < newLine->length; i++)
        newLine->Cs[i] = Cs[index + i];

    newLine->Cs[newLine->length] = '\0';

 
    return newLine;
}

void line::indent(int cursorColumn) {
    if (cursorColumn < 0 || cursorColumn > length)
        return;

    char* newCs = new char[length + 2]; 
    for (int i = 0; i < cursorColumn; i++)
        newCs[i] = Cs[i];

   
    newCs[cursorColumn] = '\t';

  
    for (int i = cursorColumn; i < length; i++)
        newCs[i + 1] = Cs[i];


    newCs[length + 1] = '\0';

 
    delete[] Cs;
    Cs = newCs;

  
    length++;
}
void line::unindent(int cursorColumn) {
    const int tabSize = 4;

    if (cursorColumn < tabSize)
        return;

    int spacesToRemove = 0;

    
    for (int i = 1; i <= length; i++) {
        if (Cs[i] == '\t') {
            {
                for (int j = i;i-4>=0 and j -1 >= i - 4; j--) {
                    Cs[j] = Cs[j - 1];
               }
            }
        }
    }

  
    if (spacesToRemove == 0)
        return;

   
    for (int i = cursorColumn; i-1 >= cursorColumn-4; i--)
        Cs[i] = Cs[i-1];

    
    Cs[length] = '\0';

   
    length -= spacesToRemove;
}



const char* line:: getContent() const {
    return Cs;
}