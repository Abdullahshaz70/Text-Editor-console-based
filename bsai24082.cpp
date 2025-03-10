//#include"utility.h"
#include <iostream>
#include <conio.h>
#include "mode.h"
#include "paragraph.h"
#include"section.h"
#include"chapter.h"
using namespace std;
#define MAX_LENGHT_LINE 10
#define MAX_LENGHT_PAGE 20
int cursorRow = 0, cursorColumn = 0 , x=0;

//section S;
chapter C;

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




//void moveUp() {
//    if (cursorRow > 0) {
//        cursorRow--;
//       
//        if (cursorColumn > C.getLineSize(cursorRow)) {
//            cursorColumn = C.getLineSize(cursorRow);
//        }
//    }
//}
//void moveLeft() {
//    if (cursorColumn > 0) {
//        cursorColumn--;
//    }
//    else if (cursorRow > 0) {  
//        cursorRow--;
//        cursorColumn = C.getLineSize(cursorRow);  
//    }
//}
//void moveRight() {
//    if (cursorColumn < C.getLineSize(cursorRow)) {
//        cursorColumn++;
//    }
//    else if (cursorRow + 1 < C.getParagraphSize(cursorRow)) {  
//        cursorRow++;
//        cursorColumn = 0;
//    }
//}
//void moveDown() {
//    if (cursorRow + 1 < C.getParagraphSize(cursorRow)) {
//        cursorRow++;
//       
//        if (cursorColumn > C.getLineSize(cursorRow)) {
//            cursorColumn = C.getLineSize(cursorRow);
//        }
//    }
//}
void moveUp() {
    if (cursorRow > 0) {
        cursorRow--;
        int lineSize = C.getLineSize(cursorRow);
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
        cursorColumn = C.getLineSize(cursorRow);
    }
}

void moveRight() {
    if (cursorColumn < C.getLineSize(cursorRow)) {
        cursorColumn++;
    }
    else if (cursorRow + 1 < C.getTotalLines()) {
        cursorRow++;
        cursorColumn = 0;
    }
}

void moveDown() {
    if (cursorRow + 1 < C.getTotalLines()) {
        cursorRow++;
        int lineSize = C.getLineSize(cursorRow);
        if (cursorColumn > lineSize) {
            cursorColumn = lineSize;
        }
    }
}


void backSpace() {

    if (cursorRow != 0 or cursorColumn != 0) {

        
        C.deleteAt(cursorRow, cursorColumn - 1);
        cursorColumn--;

        if (cursorColumn < 0)
        {
            if (cursorRow != 0) {
                cursorRow--;
                cursorColumn = C.getLineSize(cursorRow);

                if (C.getLineSize(cursorRow) == 0) {


                    C.deleteline(cursorRow);
                    C.Erase(cursorRow);

                    system("cls");
                    if (cursorRow > 0) {

                        cursorRow--;
                        cursorColumn = C.getLineSize(cursorRow);
                    }
                    else
                        cursorColumn = 0;


                }
            }

        }


        gotoRowCol(cursorRow, cursorColumn);
        cout << " ";
        gotoRowCol(cursorRow, C.getLineSize(cursorRow));
        cout << " ";
    }


}
void enter_Insertion() {

    C.insertline(cursorRow, cursorColumn);

    cursorRow++;
    
   if (cursorColumn >= C.getLineSize(cursorRow))
        cursorColumn = 0;

    
    gotoRowCol(cursorRow, cursorColumn);
}


int main() {

    normalMode = true;
    C.addSection();
    //S.addparagraph();

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
                            C.unindent(cursorRow, cursorColumn);
                            cursorColumn -= 4;
                            system("cls");
                        }
                    }
                    else {
                        if (cursorColumn + 4 < MAX_LENGHT_LINE) {
                            C.indent(cursorRow, cursorColumn);
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
                        C.insertline(cursorRow, cursorColumn);
                        cursorRow++;
                        cursorColumn = 0;
                    }

                    C.insertAt(cursorRow, cursorColumn, sym);
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
                    cursorColumn = C.findNextWord(cursorRow, cursorColumn);

                    break;
                case 'b':
                    cursorColumn = C.findPrevWord(cursorRow, cursorColumn);

                    break;
                case 'd':
                    sym = _getch();
                    if (sym == 'd') {

                        for (int i = 0; i < C.getLineSize(cursorRow); i++)
                        {
                            gotoRowCol(cursorRow, i);
                            cout << " ";
                        }
                        C.deletefrom(cursorRow, 0);
                        cursorColumn = 0;
                    }
                    break;
                case 'D':
                    for (int i = cursorColumn; i < C.getLineSize(cursorRow); i++)
                    {
                        gotoRowCol(cursorRow, i);
                        cout << " ";
                    }
                    C.deletefrom(cursorRow, cursorColumn);
                    break;
                case 'x':
                    C.deleteAt(cursorRow, cursorColumn);
                    gotoRowCol(cursorRow, cursorColumn);
                    cout << " ";
                    gotoRowCol(cursorRow, C.getLineSize(cursorRow));
                    cout << " ";
                    gotoRowCol(cursorRow, cursorColumn);
                    cout << " ";
                    break;
                case '0':
                    C.startOfLine(cursorRow, cursorColumn);
                    gotoRowCol(cursorRow, cursorColumn);
                    break;
                case '$':
                    C.endOfLine(cursorRow, cursorColumn);
                    gotoRowCol(cursorRow, cursorColumn);
                    break;
                case 'y':
                    sym = _getch();
                    if (sym == 'y')
                        C.copyLine(cursorRow);
                    else
                        C.print();
                    break;

                case 'P':  
                    C.addLine(cursorRow);
                    C.pasteLine(cursorRow);
                    cursorColumn = 0;
                    gotoRowCol(cursorRow, cursorColumn);
                    system("cls");
                    break;

                case 'p':  
                    C.pasteLine(cursorRow);
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
                    C.toggle(cursorRow, cursorColumn);

                    break;

                case -32: 
                    sym = _getch();
                    if (sym == 83)
                        C.deleteAt(cursorRow, cursorColumn + 1);
                    gotoRowCol(cursorRow, cursorColumn + 1);
                    cout << " ";
                    gotoRowCol(cursorRow, C.getLineSize(cursorRow));
                    cout << " ";

                    break;

                }
            }
            else if (commandMode) {
                
                switch (sym) {
                case 'w':
                    sym = _getch();
                    //S.writeToFile("Text.txt");

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
                    C.searchPattern(searchPattern, true);  
                    system("pause");
                    system("cls");
                    break;
                }

                case '?': {
                    char searchPattern[100];
                    cout << "Enter search pattern: ";
                    cin >> searchPattern;
                    C.searchPattern(searchPattern, false);
                    system("pause");
                    system("cls");
                    break;
                }

                case 'n':
                    C.moveToNextOccurrence();
                    system("pause");
                    system("cls");
                    break;

                case 'N':
                    C.moveToPreviousOccurrence();
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
                    C.searchAndReplace(word, newWord);
                    system("pause");
                    system("cls");
                }

            }
            gotoRowCol(0, 0);
        
                C.print();
          

            gotoRowCol(cursorRow, cursorColumn);
        }
    }
        return 0;
}






