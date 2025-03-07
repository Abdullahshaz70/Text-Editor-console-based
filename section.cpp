#include "section.h"



void section::addparagraph() {
    S.push_back(new paragraph());
}

void section::insertAt(int lineIndex, int columnIndex, char sym) {

    S[getParagraphNumber(lineIndex) - 1]->insertAt(lineIndex, columnIndex, sym);
    
}

//void section::insertAt(int lineIndex, int columnIndex, char sym) {
//    if (S[getParagraphNumber(lineIndex)-1] == nullptr) return;
//
//   
//    while (S.size() <= getParagraphNumber(lineIndex)-1) {
//        S.push_back(new paragraph());
//    }
//
//    
//    if (sym == '\r') {
//        if (S[getParagraphNumber(lineIndex) - 1]->isLineEmpty(lineIndex)) {
//          
//            S.insert(S.begin() + getParagraphNumber(lineIndex) - 1 + 1, new paragraph());
//        }
//        else {
//     
//            S[getParagraphNumber(lineIndex) - 1]->insertline(lineIndex, columnIndex);
//        }
//    }
//    else {
//      
//        S[getParagraphNumber(lineIndex) - 1]->insertAt(lineIndex, columnIndex, sym);
//    }
//}



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
void section::deleteAt(int lineIndex, int columnIndex) {

    S[getParagraphNumber(lineIndex) - 1]->deleteAt(lineIndex, columnIndex);

}
void  section::printSection(int lineIndex) {

    for (int i = 0; i < S.size(); i++)
        S[i]->printLine(lineIndex);

}

int section::getlineSize( int lineIndex) {
    return  S[getParagraphNumber(lineIndex) - 1]->getlinesize(lineIndex);
}
int section::getParagraphSize(int lineindex) {

    return S[getParagraphNumber(lineindex) - 1]->paragraphSize();

}

int section::findNextWord(int lineIndex, int columnIndex) {
  return  S[getParagraphNumber(lineIndex) - 1]->findnextword(lineIndex, columnIndex);
}
int section::findPrevWord(int lineIndex, int columnIndex) {
   return  S[getParagraphNumber(lineIndex) - 1]->findprevword(lineIndex, columnIndex);
}

void section::deleteFrom(int lineIndex, int columnIndex) {
    S[getParagraphNumber(lineIndex) - 1]->deletefrom(lineIndex, columnIndex);
}
void section::startOfLine(int lineIndex, int& columnIndex) {
    S[getParagraphNumber(lineIndex) - 1]->startofline(lineIndex, columnIndex);
}
void section::endOfLine(int lineIndex, int& columnIndex) {
    S[getParagraphNumber(lineIndex) - 1]->endofline(lineIndex, columnIndex);
}

void section::copyLine(int lineIndex) {
    S[getParagraphNumber(lineIndex) - 1]->CopyLine(lineIndex);
}
void section::pasteLine(int lineIndex) {
    S[getParagraphNumber(lineIndex) - 1]->pasteLine(lineIndex);
}

void section::toggle(int lineindex , int index) {
    S[getParagraphSize(lineindex) - 1]->Toggle(lineindex, index);
}

void section::insertparagraph(int lineIndex, int columnIndex) {
    
    S[getParagraphNumber(lineIndex) - 1]->insertline(lineIndex, columnIndex);

}