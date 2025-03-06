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

    if (cursorRow != P.paragraphSize()-1 and cursorColumn == P.getLine(cursorRow)->size()) {
        cursorRow++;
        cursorColumn =0;
    }
}
void moveDown() {
    if (cursorRow < P.paragraphSize() - 1 and P.getlinesize(cursorRow+1)>0) {
        cursorRow++;
        cursorColumn = P.getlinesize(cursorRow);
    }
}


int main() {
    
    ofstream rdr("output.txt");

    normalMode = true;

    P.addline();
       
    P.printLine(cursorRow);

     while (true){
         if (_kbhit()) {
             char sym = _getch();

             modeChanges(sym);

             if (insertionMode) {
                 switch (sym) {
                 case 8:
                     if (cursorRow != 0 or cursorColumn != 0) {

                         P.deleteAt(cursorRow, cursorColumn - 1);
                         cursorColumn--;


                         if (cursorColumn < 0)
                         {
                             if (cursorRow != 0) {
                                 cursorRow--;
                                 cursorColumn = P.getlinesize(cursorRow);

                             }

                         }
                     }
                     break;
                 case 13:
                     P.insertline(cursorRow, cursorColumn);
                     cursorRow++;

                     if (cursorColumn >= P.getlinesize(cursorRow))
                         cursorColumn = 0;

                     break;

                 case -32:
                     sym = _getch();
                     if (sym == 75)
                         moveLeft();
                     else if (sym == 77)
                         moveRight();
                     else if (sym == 80)
                         moveDown();
                     else if (sym == 72)
                         moveUp();

                     break;

                 default:

                     P.insertAt(cursorRow, cursorColumn, sym);
                     cursorColumn++;

                     if (cursorColumn >= A.MAX_LENGHT) {
                         P.insertline(cursorRow, cursorColumn);
                         cursorRow++, cursorColumn = 0;

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
                     cursorColumn = P.findnextword(cursorRow, cursorColumn);
                     break;
                 case 'b':
                     cursorColumn = P.findprevword(cursorRow, cursorColumn);
                     break;
                 case 'd':
                     sym = _getch();
                     if (sym == 'd') {
                         P.deletefrom(cursorRow, 0);
                         cursorColumn = 0;

                     }
                     else


                         break;
                 case 'D':
                     P.deletefrom(cursorRow, cursorColumn);

                     break;
                 case 'x':
                     P.deleteAt(cursorRow, cursorColumn);

                     break;
                 case '0':

                     P.startofline(cursorRow, cursorColumn);
                     break;
                 case '$':

                     P.endofline(cursorRow, cursorColumn);
                     break;
                 case'y':
                     sym = _getch();
                     if (sym == 'y')
                         P.CopyLine(cursorRow);
                     else
                         P.printParagraph();
                     break;
                 case'P':
                     P.insertline(cursorRow - 1, 0);
                     cursorRow--;
                     P.pasteLine(cursorRow);

                     break;
                 case 'p':
                     P.addline();
                     cursorRow++;
                     P.pasteLine(cursorRow);
                     break;
                 case 13:

                     P.insertline(cursorRow, cursorColumn);
                     cursorRow++;

                     if (cursorColumn >= P.getlinesize(cursorRow)) {

                         cursorColumn = 0;

                     }
                     break;
                 case 126:
                     P.Toggle(cursorRow, cursorColumn);

                     break;

                 case -32: //delete
                     sym = _getch();
                     if (sym == 83)
                         P.deleteAt(cursorRow, cursorColumn);

                     break;

                 }
             }
             else if (commandMode) {
                 char* H = new char[5];
                 H[0] = 'h';
                 H[1] = 'e';
                 H[2] = 'h';
                 H[3] = 'e';
                 H[4] = '\0';
                 if (sym == ':') {
                     sym = _getch();
                     switch (sym) {
                     case 'w': {

                         sym = _getch();
                         if (sym == 'q') {

                             P.writeToFile("output.txt");
                             return 0;
                         }
                         else
                             P.writeToFile("output.txt");

                         break;
                     }
                     case 'q':
                         sym = _getch();
                         if (sym == '!')
                             return 0;

                         else
                             return 0;

                         break;

                     case '/': { 
                         //cin >> command;
                         P.searchPattern(H, true);
                         system("pause");
                         break;
                     }
                     case '?': { 
                         //cin >> command;
                            
                         P.searchPattern(H, false);
                         system("pause");
                         break;
                     }
                     case 'n': // Move to next occurrence
                         P.moveToNextOccurrence();
                         system("pause");
                         break;
                     case 'N': // Move to previous occurrence
                         P.moveToPreviousOccurrence();
                         system("pause");
                         break;
                     default:
                         break;
                     
                     }
                 }
             }
         
            system("cls");
          
            P.printParagraph();

            gotoRowCol( cursorRow,  cursorColumn);
         }
     }

    return 0;
}

int main543() {

    P.addline("haha");
    P.addline("haha");
    P.addline("haha");
    P.addline("haha");
   
    P.printParagraph();

    //while (true) {
    //    int ch = _getch();
    //    if (ch == 224) {
    //        int extended = _getch();  // Get extended key
    //        std::cout << "Extended Key Code: " << extended << std::endl;
    //    }
    //    else {
    //        std::cout << "Key Code: " << ch << std::endl;
    //    }
    //}
    return 0;
}



