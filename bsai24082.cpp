#include"utility.h"
//#include "cursor.h"
#include <iostream>
#include <conio.h>
#include "mode.h"
#include "paragraph.h"
#include"section.h"

using namespace std;
#define MAX_LENGHT_LINE 20
int cursorRow = 0, cursorColumn = 0;
//line A;
paragraph P;
section S;
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
    gotoRowCol(cursorRow, cursorColumn);
}
void moveLeft() {

    if (cursorRow != 0 and cursorColumn == 0) {
        cursorRow--;
        cursorColumn = S.getlineSize(cursorRow);
    }

    if (cursorColumn > 0)
        cursorColumn--;

    gotoRowCol(cursorRow, cursorColumn);
}
void moveRight() {
    if (cursorColumn < S.getlineSize(cursorRow))
        cursorColumn++;

    if (cursorRow != S.getParagraphSize(cursorRow)-1 and cursorColumn == S.getlineSize(cursorRow)) {
        cursorRow++;
        cursorColumn =0;
    }
    gotoRowCol(cursorRow, cursorColumn);
}
void moveDown() {
    if (cursorRow < S.getParagraphSize(cursorRow) - 1 and S.getlineSize(cursorRow+1)>0) {
        cursorRow++;
        cursorColumn = S.getlineSize(cursorRow);
    }
    gotoRowCol(cursorRow, cursorColumn);
}
void enter_Insertion() {
    for (int i = cursorColumn; i < S.getlineSize(cursorRow); i++) {
        gotoRowCol(cursorRow, i);
        cout << " ";

    }

    S.insertparagraph(cursorRow, cursorColumn);
    cursorRow++;
    if (cursorColumn >= S.getlineSize(cursorRow))
        cursorColumn = 0;

    gotoRowCol(cursorRow, cursorColumn);
}

int main() {
    
    normalMode = true;

    S.addparagraph();
   
     while (true){
         if (_kbhit()) {
             char sym = _getch();

            
             modeChanges(sym);

             if (insertionMode) {
                 switch (sym) {
                 case 8:
                     if (cursorRow != 0 or cursorColumn != 0) {

                        
                         S.deleteAt(cursorRow, cursorColumn - 1);
                         cursorColumn--;
                        
                         if (cursorColumn < 0)
                         {
                             if (cursorRow != 0) {
                                 cursorRow--;
                                 cursorColumn = S.getlineSize(cursorRow);
                             }

                         }
                         gotoRowCol(cursorRow, cursorColumn);
                         cout << " ";
                     }

                     break;
                 case 13:
                     enter_Insertion();
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
                 case 224: 
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
                         S.insertparagraph( cursorRow, cursorColumn);
                         cursorRow++, cursorColumn = 0;

                     }

                     S.insertAt(cursorRow, cursorColumn, sym);
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
                     cursorColumn = S.findNextWord(cursorRow, cursorColumn);
                   
                     break;
                 case 'b':
                     cursorColumn = S.findPrevWord(cursorRow, cursorColumn);
                    
                     break;
                 case 'd':
                     sym = _getch();
                     if (sym == 'd') {

                         for (int i = 0; i < S.getlineSize(cursorRow); i++)
                         {
                             gotoRowCol(cursorRow, i);
                             cout << " ";
                         }
                         S.deleteFrom(cursorRow, 0);
                         cursorColumn = 0;
                     }
                         break;
                 case 'D':
                     for (int i = cursorColumn; i < S.getlineSize(cursorRow); i++)
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
                     break;
                 case '0':
                     S.startOfLine(cursorRow, cursorColumn);
                     gotoRowCol(cursorRow, cursorColumn);
                     break;
                 case '$':
                     S.endOfLine(cursorRow, cursorColumn);
                     gotoRowCol(cursorRow, cursorColumn);
                     break;
                     {

                 case'y':
                     sym = _getch();
                     if (sym == 'y')
                         S.copyLine(cursorRow);
                         //P.CopyLine(cursorRow);

                     else
                         S.printSection(cursorRow);
                     break;
                 case'P':

                     P.insertline(cursorRow, 0);
                     P.pasteLine(cursorRow);
                     gotoRowCol(cursorRow, 0);
                     for (int i = 0; i < P.getlinesize(cursorRow); i++) {
                         cout << P.getLine(cursorRow)->getCharAt(i);
                     }
                     cursorColumn = 0;
                     gotoRowCol(cursorRow, cursorColumn);
                     break;

                 case 'p':
                     //P.addline();
                     S.addparagraph();
                     cursorRow++;
                     gotoRowCol(cursorRow, cursorColumn);
                     //P.pasteLine(cursorRow);
                     S.pasteLine(cursorRow);
                     break;
                     }
                 case 13:
                     enter_Insertion();
                     break;
                 case 126:
                     S.toggle(cursorRow, cursorColumn);

                     break;

                 case -32: //delete
                     sym = _getch();
                     if (sym == 83)
                         S.deleteAt(cursorRow, cursorColumn+1);
                     gotoRowCol(cursorRow, cursorColumn+1);
                     cout << " ";
                     gotoRowCol(cursorRow, S.getlineSize(cursorRow));
                     cout << " ";

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

                             P.writeToFile("Text.txt");
                             return 0;
                         }
                         else
                             P.writeToFile("Text.txt");

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
                     case 'n': 
                         P.moveToNextOccurrence();
                         system("pause");
                         break;
                     case 'N': 
                         P.moveToPreviousOccurrence();
                         system("pause");
                         break;
                     default:
                         break;
                     
                     }
                 }
             }
         

            gotoRowCol( cursorRow,  0);
            
            S.printSection(cursorRow);
            gotoRowCol( cursorRow,  cursorColumn);
          

         }
     }

     

    return 0;
}

int main43() {

    P.addline("haha");
    P.printParagraph();
    P.CopyLine(0);
    P.pasteLine(1);
   
    P.printParagraph();


    //S.addParagraph("heelo");
    //S.paragraphIncrement();
    //S.addParagraph("heelo");
    //S.paragraphIncrement();
    //S.addParagraph("heelo");
    //S.paragraphIncrement();

    //S.sectionPrint();
    //cout << endl;

    //S.insertAt(3, 0, 6, 'r');

    //S.sectionPrint();
    //cout << endl;

    //cout << S.totalParagraph();

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



