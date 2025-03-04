
#include "cursor.h"
#include <iostream>
#include <conio.h>
#include "mode.h"

using namespace std;

void modeChanges(char sym) {
    if (sym == 'i')
        insertionMode = true, normalMode = false;
    else if (int(sym) == 27 && insertionMode)
        insertionMode = false, normalMode = true;
    else if (sym == ':' && !insertionMode)
        commandMode = true, normalMode = false;
    else if (int(sym) == 27 && commandMode)
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
    normalMode = true;

    while (true) {
        if (_kbhit()) {
            char sym = _getch();

            modeChanges(sym);

            if (insertionMode) {
                switch (sym) {
                case 8: // Backspace
                    if (c.cursorColumn > 0) {
                        A.deleteAt(c.cursorColumn - 1);
                        c.cursorColumn--;
                    }
                    break;
                default:
                    A.insertAt(c.cursorColumn, sym);
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
                    if (c.cursorColumn < A.size())
                        c.cursorColumn++;
                    break;
                case 'w':
                    c.cursorColumn = A.findNextWord(c.cursorColumn);
                    break;
                case 'b':
                    c.cursorColumn = A.findPrevWord(c.cursorColumn);
                    break;
                case 'd':
                    sym = _getch();
                    if (sym == 'd') {
                        A.deleteFrom(0);
                        c.cursorColumn = 0;
                    }
                    break;
                case 'D':
                    A.deleteFrom(c.cursorColumn);
                    break;
                case 'x':
                    A.deleteAt(c.cursorColumn);
                    break;
                case '0':
                    c.cursorColumn = 0;
                    break;
                case '$':
                    c.cursorColumn = A.size();
                    break;
                case 224: // Special keys
                    sym = _getch();
                    if (sym == 83) // Delete key
                        A.deleteAt(c.cursorColumn);
                    break;
                }
            }

            // Clear the line and reprint it
            gotoRowCol(c.cursorRow, 0);
            cout << string(80, ' '); // Clear the line (assuming 80 columns)
            gotoRowCol(c.cursorRow, 0);
            A.printline();

            // Move the cursor to the correct position
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