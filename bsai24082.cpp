#include"utility.h"
//#include "cursor.h"
#include <iostream>
#include <conio.h>
#include "mode.h"
#include "paragraph.h"
using namespace std;

int cursorRow = 0, cursorColumn = 0;
line A;
paragraph P;

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

void moveUp() {
    
    if (cursorRow != 0)
        cursorRow--;

}
void moveLeft() {

    if (cursorRow != 0 and cursorColumn == 0) {
        cursorRow--;
        cursorColumn = P.getLine(cursorRow)->size();
    }

    if (cursorColumn > 0)
        cursorColumn--;
}
void moveRight() {
    if (cursorColumn < P.getLine(cursorRow)->size())
        cursorColumn++;

    if (cursorRow != 0 and cursorColumn == P.getLine(cursorRow)->size()) {
        cursorRow++;
        cursorColumn =0;
    }
}
void moveDown() {
    if (cursorRow < P.paragraphSize() - 1)
        cursorRow++;
}

int main() {
    
    normalMode = true;

    P.addline();
    while (true) {
        if (_kbhit()) {
            char sym = _getch();

            modeChanges(sym);
           
            if (insertionMode) {
                switch (sym) {
                case 8: 
                    if ( cursorRow != 0 or cursorColumn!=0 ) {
                        //A.deleteAt( cursorColumn - 1);
                        P.deleteAt( cursorRow,  cursorColumn - 1);
                         cursorColumn--;

                         if (cursorColumn < 0)
                         {
                             if (cursorRow != 0) {
                                 cursorRow--;
                                 cursorColumn = P.getLine(cursorRow)->size();
                             }
                          
                         }

                    }
                    break;
                case 13:
                    //P.insertline( cursorRow + 1);
                    P.insertline( cursorRow,  cursorColumn);
                     cursorRow++;
                    if( cursorColumn>= P.getLine(cursorRow)->size())
                         cursorColumn = 0;
                    break;
                default:
                    //A.insertAt( cursorColumn, sym);
                    P.insertAt( cursorRow,  cursorColumn, sym);
                     cursorColumn++;
                     if (cursorColumn >= A.MAX_LENGHT) {
                         P.insertline(cursorRow, cursorColumn);
                         cursorRow++ , cursorColumn = 0;
                     }
                     

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
                     cursorColumn = P.getLine( cursorRow)->findNextWord( cursorColumn);
                    break;
                case 'b':
                     cursorColumn = P.getLine( cursorRow)->findPrevWord( cursorColumn);
                    break;
                case 'd':
                    sym = _getch();
                    if (sym == 'd'){
                        //A.deleteFrom(0);
                        P.deletefrom( cursorRow, 0);
                         cursorColumn = 0;
                    }
                    else
                        P.printParagraph();
                    break;
                case 'D':
                    //A.deleteFrom( cursorColumn);
                    P.deletefrom( cursorRow,  cursorColumn);
                    break;
                case 'x':
                    //A.deleteAt( cursorColumn);
                    P.deleteAt( cursorRow,  cursorColumn);
                    break;
                case '0':
                    // cursorColumn = 0;
                    P.getLine( cursorRow)->startofLine( cursorColumn);
                    break;
                case '$':
                    // cursorColumn = A.size();
                    P.getLine( cursorRow)->endofLine( cursorColumn);
                    break;
                case 13:
                    //P.insertline( cursorRow + 1);
                    P.insertline( cursorRow,  cursorColumn);
                     cursorRow++;
                    if ( cursorColumn >= P.getLine( cursorRow)->size())
                         cursorColumn = 0;
                    break;
                case 224: 
                    sym = _getch();
                    if (sym == 83)
                        A.deleteAt( cursorColumn);
                        //P.deleteAt( cursorRow,  cursorColumn + 1);
                    break;
                }
            }

            //gotoRowCol( cursorRow, 0);
            //A.clearLine( cursorRow,  cursorColumn, A.size()/*A.MAX_LENGHT*/);
  
            //gotoRowCol( cursorRow, 0);
            //A.printline();
            system("cls");
            P.printParagraph();

            
            gotoRowCol( cursorRow,  cursorColumn);
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