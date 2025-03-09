//#include"utility.h"
#include <iostream>
#include <conio.h>
#include "mode.h"
#include "paragraph.h"
#include"section.h"

using namespace std;
#define MAX_LENGHT_LINE 10
int cursorRow = 0, cursorColumn = 0;
//line A;
//paragraph P;
section S;
static int enterCount = 0;

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
       
        if (cursorColumn > S.getLineSize(cursorRow)) {
            cursorColumn = S.getLineSize(cursorRow);
        }
    }
}
void moveLeft() {
    if (cursorColumn > 0) {
        cursorColumn--;
    }
    else if (cursorRow > 0) {  
        cursorRow--;
        cursorColumn = S.getLineSize(cursorRow);  
    }
}
void moveRight() {
    if (cursorColumn < S.getLineSize(cursorRow)) {
        cursorColumn++;
    }
    else if (cursorRow + 1 < S.getParagraphSize(cursorRow)) {  
        cursorRow++;
        cursorColumn = 0;
    }
}
void moveDown() {
    if (cursorRow + 1 < S.getParagraphSize(cursorRow)) {
        cursorRow++;
       
        if (cursorColumn > S.getLineSize(cursorRow)) {
            cursorColumn = S.getLineSize(cursorRow);
        }
    }
}

void backSpace() {

    if (cursorRow != 0 or cursorColumn != 0) {
        S.deleteAt(cursorRow, cursorColumn - 1);
        cursorColumn--;

        if (cursorColumn < 0)
        {
            if (cursorRow != 0) {
                cursorRow--;
                cursorColumn = S.getLineSize(cursorRow);

                if (S.getLineSize(cursorRow) == 0) {


                    S.deleteline(cursorRow);
                    S.Erase(cursorRow);

                    system("cls");
                    if (cursorRow > 0) {

                        cursorRow--;
                        cursorColumn = S.getLineSize(cursorRow);
                    }
                    else
                        cursorColumn = 0;


                }
            }

        }


        gotoRowCol(cursorRow, cursorColumn);
        cout << " ";
        gotoRowCol(cursorRow, S.getLineSize(cursorRow));
        cout << " ";
    }


}
void enter_Insertion() {

    S.insertline(cursorRow, cursorColumn);

    cursorRow++;
    
   if (cursorColumn >= S.getLineSize(cursorRow))
        cursorColumn = 0;

    
    gotoRowCol(cursorRow, cursorColumn);
}


int main() {

    normalMode = true;
    S.addparagraph();

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
                            S.unindent(cursorRow, cursorColumn);
                            cursorColumn -= 4;
                            system("cls");
                        }
                    }
                    else {
                        if (cursorColumn + 4 < MAX_LENGHT_LINE) {
                            S.indent(cursorRow, cursorColumn);
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
                        S.insertline(cursorRow, cursorColumn);
                        cursorRow++;
                        cursorColumn = 0;
                    }

                    S.insertAt(cursorRow, cursorColumn, sym);
                    cursorColumn++;
                    break;
                }
            }
            else if (normalMode) {
                switch (sym) {
                case'#':
                    S.addparagraph();
                    cursorColumn = 0;
                    gotoRowCol(cursorRow, cursorColumn);
                    break;
                case 's':
                    S.writeToFile("Text.txt");
                    break;
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
                    cursorColumn = S.findnextword(cursorRow, cursorColumn);

                    break;
                case 'b':
                    cursorColumn = S.findprevword(cursorRow, cursorColumn);

                    break;
                case 'd':
                    sym = _getch();
                    if (sym == 'd') {

                        for (int i = 0; i < S.getLineSize(cursorRow); i++)
                        {
                            gotoRowCol(cursorRow, i);
                            cout << " ";
                        }
                        S.deleteFrom(cursorRow, 0);
                        cursorColumn = 0;
                    }
                    break;
                case 'D':
                    for (int i = cursorColumn; i < S.getLineSize(cursorRow); i++)
                    {
                        gotoRowCol(cursorRow, i);
                        cout << " ";
                    }
                    S.deleteFrom(cursorRow, cursorColumn);
                    break;
                case 'x':
                    S.deleteAt(cursorRow, cursorColumn);
                    gotoRowCol(cursorRow, cursorColumn);
                    cout << " ";
                    gotoRowCol(cursorRow, S.getLineSize(cursorRow));
                    cout << " ";
                    gotoRowCol(cursorRow, cursorColumn);
                    cout << " ";
                    break;
                case '0':
                    S.startOfLine(cursorRow, cursorColumn);
                    gotoRowCol(cursorRow, cursorColumn);
                    break;
                case '$':
                    S.endOfLine(cursorRow, cursorColumn);
                    gotoRowCol(cursorRow, cursorColumn);
                    break;
                case 'y':
                    sym = _getch();
                    if (sym == 'y')
                        S.copyLine(cursorRow);
                    else
                        S.print();
                    break;

                case 'P':  
                    S.addline(cursorRow);
                    S.pasteLine(cursorRow);
                    cursorColumn = 0;
                    gotoRowCol(cursorRow, cursorColumn);
                    system("cls");
                    break;

                case 'p':  
                    S.pasteLine(cursorRow + 1);
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
                    S.toggle(cursorRow, cursorColumn);

                    break;

                case -32: 
                    sym = _getch();
                    if (sym == 83)
                        S.deleteAt(cursorRow, cursorColumn + 1);
                    gotoRowCol(cursorRow, cursorColumn + 1);
                    cout << " ";
                    gotoRowCol(cursorRow, S.getLineSize(cursorRow));
                    cout << " ";

                    break;

                }
            }
            gotoRowCol(0, 0);
            S.print();
            gotoRowCol(cursorRow, cursorColumn);
        }
    }
        return 0;
}






