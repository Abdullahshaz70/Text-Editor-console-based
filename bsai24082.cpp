#include "cursor.h"
#include <iostream>
#include <conio.h>
#include "mode.h"
#include "paragraph.h"

using namespace std;

void modeChanges(char sym) {
    if (sym == 'i')
        insertionMode = true, normalMode = false;
    else if (int(sym) == 27 and insertionMode)
        insertionMode = false, normalMode = true;
    else if (sym == ':' and !insertionMode)
        commandMode = true, normalMode = false;
    else if (int(sym) == 27 and commandMode)
        commandMode = false, normalMode = true;
    else
        normalMode = true;

    gotoRowCol(50, 90);
    if (insertionMode)
        cout << "insertionmode";
    else if (commandMode)
        cout << "commandMode";
    else if (normalMode)
        cout << "normalMode";
}

int main() {
    cursor c;
    line A;
    paragraph P;
    normalMode = true;

    P.addline();
    while (true) {
        if (_kbhit()) {
            char sym = _getch();

            modeChanges(sym);
           
            if (insertionMode) {
                switch (sym) {
                case 8: 
                    if (c.cursorColumn > 0) {
                        //A.deleteAt(c.cursorColumn - 1);
                        P.deleteAt(c.cursorRow, c.cursorColumn - 1);
                        c.cursorColumn--;
                    }
                    break;
                case 13:
                    P.insertline(c.cursorRow + 1);
                    c.cursorRow++;
                    if(c.cursorColumn>= P.getLine(c.cursorRow)->size())
                    c.cursorColumn = 0;
                    break;
                default:
                    //A.insertAt(c.cursorColumn, sym);
                    P.insertAt(c.cursorRow, c.cursorColumn, sym);
                    
                    c.cursorColumn++;
                    break;
                }
            }
            else if (normalMode) {
                switch (sym) {
                case 'h':
                    if (c.cursorColumn > 0)
                        c.cursorColumn--;
                    break;
                case 'l':
                    //if (c.cursorColumn < A.size())
                    if (c.cursorColumn < P.getLine(c.cursorRow)->size())
                        c.cursorColumn++;
                    break;
                case 'w':
                    c.cursorColumn = P.getLine(c.cursorRow)->findNextWord(c.cursorColumn);
                    break;
                case 'b':
                    c.cursorColumn = P.getLine(c.cursorRow)->findPrevWord(c.cursorColumn);
                    break;
                case 'd':
                    sym = _getch();
                    if (sym == 'd'){
                        //A.deleteFrom(0);
                        P.deletefrom(c.cursorRow, 0);
                        c.cursorColumn = 0;
                    }
                    else
                        P.printParagraph();
                    break;
                case 'D':
                    //A.deleteFrom(c.cursorColumn);
                    P.deletefrom(c.cursorRow, c.cursorColumn);
                    break;
                case 'x':
                    //A.deleteAt(c.cursorColumn);
                    P.deleteAt(c.cursorRow, c.cursorColumn);
                    break;
                case '0':
                    //c.cursorColumn = 0;
                    P.getLine(c.cursorRow)->startofLine(c.cursorColumn);
                    break;
                case '$':
                    //c.cursorColumn = A.size();
                    P.getLine(c.cursorRow)->endofLine(c.cursorColumn);
                    break;
                case 13:
                   /* P.insertline(c.cursorRow + 1);
                    c.cursorRow++;
                    if (c.cursorColumn >= P.getLine(c.cursorRow)->size())
                        c.cursorColumn = 0;*/
                    break;
                case 224: 
                    sym = _getch();
                    if (sym == 83)
                        A.deleteAt(c.cursorColumn);
                        //P.deleteAt(c.cursorRow, c.cursorColumn + 1);
                    break;
                }
            }

            //gotoRowCol(c.cursorRow, 0);
            //A.clearLine(c.cursorRow, c.cursorColumn, A.size()/*A.MAX_LENGHT*/);
  
            //gotoRowCol(c.cursorRow, 0);
            //A.printline();
            system("cls");
            P.printParagraph();

            
            gotoRowCol(c.cursorRow, c.cursorColumn);
        }
    }

    return 0;
}

int main798() {


   

    while (true) {
        int ch = _getch();
        if (ch == 224) {
            int extended = _getch();  // Get extended key
            std::cout << "Extended Key Code: " << extended << std::endl;
        }
        else {
            std::cout << "Key Code: " << ch << std::endl;
        }
    }
    return 0;
}