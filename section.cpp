#include "section.h"



void section::addparagraph() {
    S.push_back(new paragraph());
}
void section::insertAt(int paragraphIndex, int lineIndex, int columnIndex, char sym) {

 
    S[paragraphIndex - 1]->insertAt(lineIndex, columnIndex, sym);
    
}
int  section::getParagraphNumber(int cursorRow) {

    if (S.empty()) {
        S.push_back(new paragraph());
    }

    int paragraphIndex = 0;
    int lineCount = 0;

    for (int i = 0; i < S.size(); i++) {
        int paraLines = S[i]->paragraphSize();

        if (cursorRow < lineCount + paraLines)
            return i + 1;

        lineCount += paraLines;
    }

    return -1;
}
void section::deleteAt(int paragraphIndex, int lineIndex, int columnIndex) {

    S[paragraphIndex-1]->deleteAt(lineIndex, columnIndex);

}
void  section::printSection(int lineIndex) {

    for (int i = 0; i < S.size(); i++)
        S[i]->printLine(lineIndex);

}

int section::getlineSize(int paragraphIndex, int lineIndex) {
    return S[paragraphIndex - 1]->getlinesize(lineIndex);
}

void section::insertparagraph(int paragraphIndex, int lineIndex, int columnIndex) {

    S[paragraphIndex - 1]->insertline(lineIndex, columnIndex);

}