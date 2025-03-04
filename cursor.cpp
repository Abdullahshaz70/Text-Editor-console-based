#include "cursor.h"
#include<iostream>
#include"mode.h"
#include<conio.h>
#include"utility.h"
using namespace std;


//void cursor::linePrint() {
//    gotoRowCol(cursorRow, 0);
//    for (int i = 0; i < A.size(); i++)
//        cout << A.Cs[i];
//
//    for (int i = A.size(); i < A.MAX_LENGHT; i++)
//        cout << ' ';
//
//    gotoRowCol(cursorRow, cursorColumn);
//}


//void cursor::deletefromCursortoEnd() {
//    A.deleteFrom(cursorColumn);
//    linePrint();
//    gotoRowCol(cursorRow, cursorColumn);
//}
//void cursor::nextWord() {
//    cursorColumn = A.findNextWord(cursorColumn);
//    gotoRowCol(cursorRow, cursorColumn);
//}
//void cursor::prevWord() {
//    cursorColumn = A.findPrevWord(cursorColumn);
//    gotoRowCol(cursorRow, cursorColumn);
//}
//void cursor::startofLine() {
//    cursorColumn = 0;
//}
//void cursor::endofLine(){
//    cursorColumn = A.size() - 1;
//}

//void cursor::movement(char sym) {
//    if (insertionMode) {
//        switch (sym) {
//        case 8:  
//            A.deleteAt(cursorColumn - 1);
//            cursorColumn--;
//            linePrint();
//            break;
//        default:
//            
// 
//
//
//            insertion(sym);
//        
//            break;
//        }
//
//    }
//    else if (normalMode) {
//        switch (sym) {
//        case 'h':
//            if (cursorColumn > 0)
//                cursorColumn--;
//            break;
//        case 'l':
//            if (cursorColumn < A.size())
//                cursorColumn++;
//            break;
//        case 'w':
//            nextWord();
//            break;
//        case 'b':
//            prevWord();
//            break;
//        case 'd':
//            sym = _getch();
//            if (sym == 'd')
//                A.deleteFrom(0);
//                cursorColumn = 0;
//            break;
//        case 'D':
//            deletefromCursortoEnd();
//            break;
//        case 'x':
//            A.deleteAt(cursorColumn);
//            break;
//
//        case '0':  
//            startofLine();
//            break;
//
//        case '$': 
//            endofLine();
//            break;
//
//        case 224: 
//            sym = _getch();
//            if (sym == 83) 
//                A.deleteAt(cursorColumn);
//            break;
//        }
//        P.printParagraph();
//        gotoRowCol(cursorRow, cursorColumn);
//    }
//}
