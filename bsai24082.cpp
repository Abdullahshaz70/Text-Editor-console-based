//#include"utility.h"
#include <iostream>
#include <conio.h>
#include "mode.h"
#include "paragraph.h"
//#include"section.h"

using namespace std;
#define MAX_LENGHT_LINE 80
int cursorRow = 0, cursorColumn = 0;
//line A;
paragraph P;
//section S;
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
    
    if (cursorRow != 0)
        cursorRow--;
    gotoRowCol(cursorRow, cursorColumn);
}
void moveLeft() {

    if (cursorRow != 0 and cursorColumn == 0) {
        cursorRow--;
        cursorColumn = P.getlinesize(cursorRow);
    }

    if (cursorColumn > 0)
        cursorColumn--;

    gotoRowCol(cursorRow, cursorColumn);
}
void moveRight() {
    if (cursorColumn < P.getlinesize(cursorRow))
        cursorColumn++;

    if (cursorRow != P.paragraphSize()-2 and cursorColumn == P.getlinesize(cursorRow)) {
        cursorRow++;
        cursorColumn =0;
    }
    gotoRowCol(cursorRow, cursorColumn);
}
void moveDown() {
    if (cursorRow < P.paragraphSize()-2 and P.getlinesize(cursorRow) > 0) {
        cursorRow++;
        cursorColumn = P.getlinesize(cursorRow);
    }
    gotoRowCol(cursorRow, cursorColumn);
}



void enter_Insertion() {

    

    //for (int i = cursorColumn; i <= P.getlinesize(cursorRow); i++) {
    //    gotoRowCol(cursorRow, i);
    //    cout << " ";

    //}

   P.insertline(cursorRow, cursorColumn);
    cursorRow++;
    if (cursorColumn >= P.getlinesize(cursorRow))
        cursorColumn = 0;

    gotoRowCol(cursorRow, cursorColumn);
}


//void enter_Insertion() {
//    if (cursorRow < 0 or cursorRow >= P.paragraphSize()) return; 
//    cout << endl << endl;
//    P.insertline(cursorRow, cursorColumn); 
//
//  /*  S.printParagraph();
//
//    for (int i = cursorColumn; i < MAX_LENGHT_LINE; i++)
//    {
//        gotoRowCol(cursorRow, cursorColumn);
//        cout << " ";
//    }*/
//
//    cursorRow++;
//    cursorColumn = 0;
//
//    //system("cls");
//   
//    gotoRowCol(cursorRow, cursorColumn); 
//}


void backSpace() {

        if (cursorRow != 0 or cursorColumn != 0) {
            P.deleteAt(cursorRow, cursorColumn - 1);
            cursorColumn--;

            if (cursorColumn < 0)
            {
                if (cursorRow != 0) {
                    cursorRow--;
                    cursorColumn = P.getlinesize(cursorRow);

                    if (P.getlinesize(cursorRow) == 0) {


                        P.deleteline(cursorRow);
                        P.Erase(cursorRow);

                        system("cls");
                        if (cursorRow > 0) {

                            cursorRow--;
                            cursorColumn = P.getlinesize(cursorRow);
                        }
                        else
                            cursorColumn = 0;


                    }
                }

            }


            gotoRowCol(cursorRow, cursorColumn);
            cout << " ";
            gotoRowCol(cursorRow, P.getlinesize(cursorRow));
            cout << " ";
        }

       
}

int main789() {
    
    normalMode = true;

    P.addline();
   
     //while (true){
     //    if (_kbhit()) {
     //        char sym = _getch();

     //       
     //        modeChanges(sym);

     //        if (insertionMode) {
     //            switch (sym) {
     //            case 8:
     //                //handleBackspace(cursorRow, cursorColumn);
     //               /* if (cursorRow != 0 or cursorColumn != 0) {

     //                   
     //                    P.deleteAt(cursorRow, cursorColumn - 1);
     //                    cursorColumn--;
     //                   
     //                    if (cursorColumn < 0)
     //                    {
     //                        if (cursorRow != 0) {
     //                            cursorRow--;
     //                            cursorColumn = P.getlinesize(cursorRow);
     //                        }

     //                    }
     //                    gotoRowCol(cursorRow, cursorColumn);
     //                    cout << " ";
     //                }*/
     //                break;
     //            case 13:
     //                enter_Insertion();
     //                P.printParagraph();
     //                break;
     //            case -32:
     //                sym = _getch();
     //                if (sym == 75)
     //                    moveLeft();
     //                else if (sym == 77)
     //                    moveRight();
     //                else if (sym == 80)
     //                    moveDown();
     //                else if (sym == 72)
     //                    moveUp();

     //                break;
     //            case 224: 
     //                    sym = _getch();
     //                    switch (sym) {
     //                    case 75: moveLeft(); break;  
     //                    case 77: moveRight(); break; 
     //                    case 72: moveUp(); break;   
     //                    case 80: moveDown(); break;  
     //                   
     //                    }
     //                    break;

     //            default:

     //                if (cursorColumn >= MAX_LENGHT_LINE) {
     //                    //S.insertparagraph( cursorRow, cursorColumn);
     //                    P.insertline(cursorRow, cursorColumn);
     //                    cursorRow++, cursorColumn = 0;
     //                    gotoRowCol(cursorRow, cursorColumn);
     //                }

     //                P.insertAt(cursorRow, cursorColumn, sym);
     //                cursorColumn++;
     //                break;
     //            }
     //        }
             //else if (normalMode) {
             //    switch (sym) {
             //    case 'h':
             //        moveLeft();
             //        break;
             //    case 'l':
             //        moveRight();     
             //        break;
             //    case 'j':
             //        moveDown();                    
             //        break;
             //    case 'k':
             //        moveUp();
             //        break;
             //    case 'w':
             //        cursorColumn = P.findnextword(cursorRow, cursorColumn);
             //      
             //        break;
             //    case 'b':
             //        cursorColumn = P.findprevword(cursorRow, cursorColumn);
             //       
             //        break;
             //    case 'd':
             //        sym = _getch();
             //        if (sym == 'd') {

             //            for (int i = 0; i < P.getlinesize(cursorRow); i++)
             //            {
             //                gotoRowCol(cursorRow, i);
             //                cout << " ";
             //            }
             //            P.deletefrom(cursorRow, 0);
             //            cursorColumn = 0;
             //        }
             //            break;
             //    case 'D':
             //        for (int i = cursorColumn; i < P.getlinesize(cursorRow); i++)
             //        {
             //            gotoRowCol(cursorRow, i);
             //            cout << " ";
             //        }
             //        P.deletefrom(cursorRow, cursorColumn);
             //        break;
             //    case 'x':
             //        P.deleteAt(cursorRow, cursorColumn);
             //        gotoRowCol(cursorRow, cursorColumn);
             //        cout << " ";
             //        break;
             //    case '0':
             //        P.startofline(cursorRow, cursorColumn);
             //        gotoRowCol(cursorRow, cursorColumn);
             //        break;
             //    case '$':
             //        P.endofline(cursorRow, cursorColumn);
             //        gotoRowCol(cursorRow, cursorColumn);
             //        break;
             //    //    {
             //    //case'y':
             //    //    sym = _getch();
             //    //    if (sym == 'y')
             //    //        S.copyLine(cursorRow);
             //    //        //P.CopyLine(cursorRow);
             //    //    else
             //    //        S.printSection(cursorRow);
             //    //    break;
             //    //case'P':
             //    //    P.insertline(cursorRow, 0);
             //    //    P.pasteLine(cursorRow);
             //    //    gotoRowCol(cursorRow, 0);
             //    //    for (int i = 0; i < P.getlinesize(cursorRow); i++) {
             //    //        cout << P.getLine(cursorRow)->getCharAt(i);
             //    //    }
             //    //    cursorColumn = 0;
             //    //    gotoRowCol(cursorRow, cursorColumn);
             //    //    break;
             //    //case 'p':
             //    //    //P.addline();
             //    //    S.addparagraph();
             //    //    cursorRow++;
             //    //    gotoRowCol(cursorRow, cursorColumn);
             //    //    //P.pasteLine(cursorRow);
             //    //    S.pasteLine(cursorRow);
             //    //    break;
             //    //    }
             //    case 13:
             //        enter_Insertion();
             //        break;
             //    case 126:
             //        P.Toggle(cursorRow, cursorColumn);

             //        break;

             //    case -32: //delete
             //        sym = _getch();
             //        if (sym == 83)
             //            P.deleteAt(cursorRow, cursorColumn+1);
             //        gotoRowCol(cursorRow, cursorColumn+1);
             //        cout << " ";
             //        gotoRowCol(cursorRow, P.getlinesize(cursorRow));
             //        cout << " ";

             //        break;

             //    }
             //}
             //else if (commandMode) {
             //    char* H = new char[5];
             //    H[0] = 'h';
             //    H[1] = 'e';
             //    H[2] = 'h';
             //    H[3] = 'e';
             //    H[4] = '\0';
             //    if (sym == ':') {
             //        sym = _getch();
             //        switch (sym) {
             //        case 'w': {
             //            sym = _getch();
             //            if (sym == 'q') {
             //                P.writeToFile("Text.txt");
             //                return 0;
             //            }
             //            else
             //                P.writeToFile("Text.txt");
             //            break;
             //        }
             //        case 'q':
             //            sym = _getch();
             //            if (sym == '!')
             //                return 0;
             //            else {
             //                system("cls");
             //                int doubleEnterCount = S.countDoubleEnter();
             //                cout << "Double enters detected: " << doubleEnterCount + 1 << endl;
             //                return 0;
             //            }
             //            
             //            break;
             //        case '/': { 
             //            //cin >> command;
             //            P.searchPattern(H, true);
             //            system("pause");
             //            break;
             //        }
             //        case '?': { 
             //            //cin >> command;
             //               
             //            P.searchPattern(H, false);
             //            system("pause");
             //            break;
             //        }
             //        case 'n': 
             //            P.moveToNextOccurrence();
             //            system("pause");
             //            break;
             //        case 'N': 
             //            P.moveToPreviousOccurrence();
             //            system("pause");
             //            break;
             //        default:
             //            break;
             //        
             //        }
             //    }
             //}
         

          
            
            system("cls");
            P.printParagraph();

            gotoRowCol( cursorRow,  cursorColumn);
          

         
     

     

    return 0;
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
                    backSpace();
                    break;
                case 9:
                    if (GetAsyncKeyState(VK_SHIFT)) {
                        if (cursorColumn - 4 >= 0) {
                            P.unindent(cursorRow, cursorColumn);
                            cursorColumn -= 4;
                            system("cls");
                        }
                    }
                    else {
                        if (cursorColumn + 4 < MAX_LENGHT_LINE) {
                            P.indent(cursorRow, cursorColumn);
                            cursorColumn += 4;
                        }
                    }
                    break;

                case 13:
                    enter_Insertion();
                    system("cls");
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
                        P.insertline(cursorRow, cursorColumn);
                        cursorRow++;
                        cursorColumn = 0;
                    }

                    P.insertAt(cursorRow, cursorColumn, sym);
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
                    cursorColumn = P.findnextword(cursorRow, cursorColumn);

                    break;
                case 'b':
                    cursorColumn = P.findprevword(cursorRow, cursorColumn);

                    break;
                case 'd':
                    sym = _getch();
                    if (sym == 'd') {

                        for (int i = 0; i < P.getlinesize(cursorRow); i++)
                        {
                            gotoRowCol(cursorRow, i);
                            cout << " ";
                        }
                        P.deletefrom(cursorRow, 0);
                        cursorColumn = 0;
                    }
                    break;
                case 'D':
                    for (int i = cursorColumn; i < P.getlinesize(cursorRow); i++)
                    {
                        gotoRowCol(cursorRow, i);
                        cout << " ";
                    }
                    P.deletefrom(cursorRow, cursorColumn);
                    break;
                case 'x':
                    P.deleteAt(cursorRow, cursorColumn);
                    gotoRowCol(cursorRow, cursorColumn);
                    cout << " ";
                    break;
                case '0':
                    P.startofline(cursorRow, cursorColumn);
                    gotoRowCol(cursorRow, cursorColumn);
                    break;
                case '$':
                    P.endofline(cursorRow, cursorColumn);
                    gotoRowCol(cursorRow, cursorColumn);
                    break;

                case 'y':
                    sym = _getch();
                    if (sym == 'y')
                        P.CopyLine(P, cursorRow);
                    else
                        P.printParagraph();
                    break;

                case 'P':
                    P.pasteLine(cursorRow);
                    gotoRowCol(cursorRow, 0);
                    for (int i = 0; i < P.getlinesize(cursorRow); i++)
                        cout << P.getLine(cursorRow)->getCharAt(i);

                    cursorColumn = 0;
                    gotoRowCol(cursorRow, cursorColumn);
                    system("cls");
                    break;

                case 'p':
                    P.addline();
                    cursorRow++;
                    if (cursorRow > 0)
                        cursorRow--;
                    gotoRowCol(cursorRow, cursorColumn);
                    P.pasteLine(cursorRow);
                    system("cls");
                    break;


                case 13:
                    enter_Insertion();
                    break;
                case 126:
                    P.Toggle(cursorRow, cursorColumn);

                    break;

                case -32: //delete
                    sym = _getch();
                    if (sym == 83)
                        P.deleteAt(cursorRow, cursorColumn + 1);
                    gotoRowCol(cursorRow, cursorColumn + 1);
                    cout << " ";
                    gotoRowCol(cursorRow, P.getlinesize(cursorRow));
                    cout << " ";

                    break;

                }
            }
            else if (commandMode) {
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
                        return 0;




                        //case '/': { 
                        //    //cin >> command;
                        //    P.searchPattern(H, true);
                        //    system("pause");
                        //    break;
                        //}
                        //case '?': { 
                        //    //cin >> command;
                        //       
                        //    P.searchPattern(H, false);
                        //    system("pause");
                        //    break;
                        //}
                        //case 'n': 
                        //    P.moveToNextOccurrence();
                        //    system("pause");
                        //    break;
                        //case 'N': 
                        //    P.moveToPreviousOccurrence();
                        //    system("pause");
                        //    break;
                        //default:
                        //    break;
                        //
                    }
                }
            }
                gotoRowCol(0, 0);
                P.printParagraph();
                gotoRowCol(cursorRow, cursorColumn);
        }

    }
        return 0;
}
