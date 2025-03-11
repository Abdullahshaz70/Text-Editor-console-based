//#include"utility.h"
#include <iostream>
#include <conio.h>
#include "mode.h"
#include"Document.h"
using namespace std;
#define MAX_LENGHT_LINE 80
#define MAX_LENGHT_PAGE 30
int cursorRow = 0, cursorColumn = 0 , x=0;

//section S;
//chapter C;
document D;

void modeChanges(char sym) {
    if (sym == 'i')
        insertionMode = true, normalMode = false;

    else if (int(sym) == 27 and insertionMode)
        insertionMode = false, normalMode = true;

    else if (sym == ':' and !insertionMode)
        commandMode = true, normalMode = false;

    else if (int(sym) == 27 and commandMode)
        commandMode = false, normalMode = true;

  /* 

    gotoRowCol(50, 90);
    if (insertionMode)
        cout << "insertionmode";
    else if (commandMode)
        cout << "commandMode";
    else if (normalMode)
        cout << "normalMode";*/
}



void moveUp() {
    if (cursorRow > 0) {
        cursorRow--;
        int lineSize = D.getLineSize(cursorRow);
        if (cursorColumn > lineSize) {
            cursorColumn = lineSize;
        }
    }
}

void moveLeft() {
    if (cursorColumn > 0) {
        cursorColumn--;
    }
    else if (cursorRow > 0) {
        cursorRow--;
        cursorColumn = D.getLineSize(cursorRow);
    }
}

void moveRight() {
    if (cursorColumn < D.getLineSize(cursorRow)) {
        cursorColumn++;
    }
    else if (cursorRow + 1 < D.getTotalLines()) {
        cursorRow++;
        cursorColumn = 0;
    }
}

void moveDown() {
    if (cursorRow + 1 < D.getTotalLines()) {
        cursorRow++;
        int lineSize = D.getLineSize(cursorRow);
        if (cursorColumn > lineSize) {
            cursorColumn = lineSize;
        }
    }
}

void backSpace() {

    if (cursorRow != 0 or cursorColumn != 0) {

        
        D.deleteAt(cursorRow, cursorColumn - 1);
        cursorColumn--;

        if (cursorColumn < 0)
        {
            if (cursorRow != 0) {
                cursorRow--;
                cursorColumn = D.getLineSize(cursorRow);

                if (D.getLineSize(cursorRow) == 0) {


                    D.deleteLine(cursorRow);
                    D.Erase(cursorRow);

                    system("cls");
                    if (cursorRow > 0) {

                        cursorRow--;
                        cursorColumn = D.getLineSize(cursorRow);
                    }
                    else
                        cursorColumn = 0;


                }
            }

        }


        gotoRowCol(cursorRow, cursorColumn);
        cout << " ";
        gotoRowCol(cursorRow, D.getLineSize(cursorRow));
        cout << " ";
    }


}

void enter_Insertion() {

    D.insertLine(cursorRow, cursorColumn);

    cursorRow++;
    
   if (cursorColumn >= D.getLineSize(cursorRow))
        cursorColumn = 0;

    
    gotoRowCol(cursorRow, cursorColumn);
}


int main() {

    normalMode = true;
    D.addChapter();
  

    while (true) {
        if (_kbhit()) {
            char sym = _getch();

            modeChanges(sym);

            if (insertionMode) {
                switch (sym) {
                case 8:
                    backSpace();
                    break;
                case 9:
                    if (GetAsyncKeyState(VK_SHIFT)) {
                        if (cursorColumn - 4 >= 0) {
                            D.unindent(cursorRow, cursorColumn);
                            cursorColumn -= 4;
                            system("cls");
                        }
                    }
                    else {
                        if (cursorColumn + 4 < MAX_LENGHT_LINE) {
                            D.indent(cursorRow, cursorColumn);
                            cursorColumn += 4;
                            system("cls");

                        }
                    }
                    break;

                case 13:
                        enter_Insertion();
                        system("cls");
                        gotoRowCol(cursorRow, cursorColumn);
                    
                    break;

                case -32:
                    sym = _getch();
                    switch (sym) {
                    case 75: moveLeft(); break;
                    case 77: moveRight(); break;
                    case 72: moveUp(); break;
                    case 80: moveDown(); break;
                    }
                    break;

                default:
                    if (cursorColumn >= MAX_LENGHT_LINE) {
                        D.insertLine(cursorRow, cursorColumn);
                        cursorRow++;
                        cursorColumn = 0;
                    }

                    D.insertAt(cursorRow, cursorColumn, sym);
                    cursorColumn++;
                    break;
                }
            }
            else if (normalMode) {
                switch (sym) {
                case 'h':
                    moveLeft();
                    break;
                case 'l':
                    moveRight();
                    break;
                case 'j':
                    moveDown();
                    break;
                case 'k':
                    moveUp();
                    break;
                case 'w':
                    cursorColumn = D.findNextWord(cursorRow, cursorColumn);

                    break;
                case 'b':
                    cursorColumn = D.findPrevWord(cursorRow, cursorColumn);

                    break;
                case 'd':
                    sym = _getch();
                    if (sym == 'd') {

                        for (int i = 0; i < D.getLineSize(cursorRow); i++)
                        {
                            gotoRowCol(cursorRow, i);
                            cout << " ";
                        }
                        D.deleteFrom(cursorRow, 0);
                        cursorColumn = 0;
                    }
                    break;
                case 'D':
                    for (int i = cursorColumn; i < D.getLineSize(cursorRow); i++)
                    {
                        gotoRowCol(cursorRow, i);
                        cout << " ";
                    }
                    D.deleteFrom(cursorRow, cursorColumn);
                    break;
                case 'x':
                    D.deleteAt(cursorRow, cursorColumn);
                    gotoRowCol(cursorRow, cursorColumn);
                    cout << " ";
                    gotoRowCol(cursorRow, D.getLineSize(cursorRow));
                    cout << " ";
                    gotoRowCol(cursorRow, cursorColumn);
                    cout << " ";
                    break;
                case '0':
                    D.startOfLine(cursorRow, cursorColumn);
                    gotoRowCol(cursorRow, cursorColumn);
                    break;
                case '$':
                    D.endOfLine(cursorRow, cursorColumn);
                    gotoRowCol(cursorRow, cursorColumn);
                    break;
                case 'y':
                    sym = _getch();
                    if (sym == 'y')
                        D.copyLine(cursorRow);
                    else
                        D.print();
                    break;

                case 'P':  
                    D.addLine(cursorRow);
                    D.pasteLine(cursorRow);
                    cursorColumn = 0;
                    gotoRowCol(cursorRow, cursorColumn);
                    system("cls");
                    break;

                case 'p':  
                    D.pasteLine(cursorRow);
                    cursorRow++;
                    cursorColumn = 0;
                    gotoRowCol(cursorRow, cursorColumn);
                    system("cls");
                    break;


                case 13:
                    enter_Insertion();
                    system("cls");
                    gotoRowCol(cursorRow, cursorColumn);
                   
                    break;
                case 126:
                    D.toggle(cursorRow, cursorColumn);

                    break;

                case -32: 
                    sym = _getch();
                    if (sym == 83)
                        D.deleteAt(cursorRow, cursorColumn + 1);
                    gotoRowCol(cursorRow, cursorColumn + 1);
                    cout << " ";
                    gotoRowCol(cursorRow, D.getLineSize(cursorRow));
                    cout << " ";

                    break;

                }
            }
            else if (commandMode) {
                
                switch (sym) {
                case 'w':
                    sym = _getch();
                    D.writeToFile("Text.txt");

                    if (sym == 'q')
                        return 0; 

                    break;

                case 'q':
                    sym = _getch();
                    if (sym == '!')
                        return 0; 
                    return 0;  

                case '/': {
                    char searchPattern[100];
                    cout << "Enter search pattern: ";
                    cin >> searchPattern;
                    D.searchPattern(searchPattern, true);  
                    system("pause");
                    system("cls");
                    break;
                }

                case '?': {
                    char searchPattern[100];
                    cout << "Enter search pattern: ";
                    cin >> searchPattern;
                    D.searchPattern(searchPattern, false);
                    system("pause");
                    system("cls");
                    break;
                }

                case 'n':
                    D.moveToNextOccurrence();
                    system("pause");
                    system("cls");
                    break;

                case 'N':
                    D.moveToPreviousOccurrence();
                    system("pause");
                    system("cls");
                    break;

                case 'F':
                    char word[100];
                    cout << "Enter word to be replaced: ";
                    cin >> word;
                    char newWord[100];
                    cout << "Enter word to be replaced: ";
                    cin >> newWord;
                    D.searchAndReplace(word, newWord);
                    system("pause");
                    system("cls");
                }

            }
            gotoRowCol(0, 0);
        
                D.print();
          

            gotoRowCol(cursorRow, cursorColumn);
        }
    }
        return 0;
}






