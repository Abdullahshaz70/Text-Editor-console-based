#include "section.h"


section::section() {}
section::~section() {
    for (paragraph* p : S)
        delete p;
    S.clear();
}

void section::addparagraph() {
    S.push_back(new paragraph());
}

void section::addline(int cursorRow) {
    S[getParagraphNumber(cursorRow)]->addline();
}



void section::insertAt(int lineIndex, int columnIndex, char sym) {
    int paraIndex = getParagraphNumber(lineIndex);
    if (paraIndex < 0 || paraIndex >= S.size())
        return;

    int relativeLineIndex = lineIndex; 
    if (paraIndex > 0) {
 
        int offset = 0;
        for (int i = 0; i < paraIndex; i++) {
            offset += S[i]->paragraphSize();
        }
        relativeLineIndex -= offset;
    }

    S[paraIndex]->insertAt(relativeLineIndex, columnIndex, sym);
}
void section::insertline(int lineIndex, int columnIndex) {
    int paraIndex = getParagraphNumber(lineIndex); 

    if (paraIndex < 0 || paraIndex >= S.size() || S[paraIndex] == nullptr) {
        return; 
    }

    S[paraIndex]->insertline(lineIndex, columnIndex); 
}


int section::getParagraphNumber(int cursorRow) {
    if (S.empty()) {
        S.push_back(new paragraph()); 
    }

    int lineCount = 0;

    for (int i = 0; i < S.size(); i++) {
        int paraLines = S[i]->paragraphSize();

        if (cursorRow < lineCount + paraLines)
            return i; 

        lineCount += paraLines;
    }

    return S.size() - 1; 
}
int section::getLineSize(int lineIndex) {
    int paraIndex = getParagraphNumber(lineIndex); 

    if (paraIndex < 0 || paraIndex >= S.size() || S[paraIndex] == nullptr) {
        return 0; 
    }

    return S[paraIndex]->getlinesize(lineIndex); 
}

void section::deleteAt(int lineIndex, int columnIndex) {
    int paraIndex = getParagraphNumber(lineIndex); 

    if (paraIndex < 0 or paraIndex >= S.size() or S[paraIndex] == nullptr) {
        return; 
    }

    S[paraIndex]->deleteAt(lineIndex, columnIndex);
}
void section::deleteFrom(int lineIndex, int columnIndex) {

    int paraIndex = getParagraphNumber(lineIndex) ; 

    if (paraIndex < 0 or paraIndex >= S.size()) return;

    S[paraIndex]->deletefrom(lineIndex, columnIndex);
}


void section::print() {
    for (int i = 0; i < S.size(); i++) {
        if (S[i] != nullptr) {
            S[i]->printParagraph();
            cout << endl;
        }
            
    }
}

line* section::getLine(int index) {
    int paragraphIndex = getParagraphNumber(index);
    if (paragraphIndex < 0 || paragraphIndex >= S.size())
        return nullptr;

    return S[paragraphIndex]->getLine(index);
}



int section::getParagraphSize(int lineindex) {

    return S[getParagraphNumber(lineindex)]->paragraphSize();

}

int section::findnextword(int lineIndex, int columnIndex) {
  return  S[getParagraphNumber(lineIndex)]->findnextword(lineIndex, columnIndex);
}
int section::findprevword(int lineIndex, int columnIndex) {
   return  S[getParagraphNumber(lineIndex)]->findprevword(lineIndex, columnIndex);
}


void section::startOfLine(int lineIndex, int& columnIndex) {
    S[getParagraphNumber(lineIndex) ]->startofline(lineIndex, columnIndex);
}
void section::endOfLine(int lineIndex, int& columnIndex) {
    S[getParagraphNumber(lineIndex)]->endofline(lineIndex, columnIndex);
}

void section::copyLine(int lineIndex) {
    int paragraphIndex = getParagraphNumber(lineIndex);
    if (paragraphIndex < 0 || paragraphIndex >= S.size()) return;

    S[paragraphIndex]->CopyLine(*S[paragraphIndex], lineIndex);
}

void section::pasteLine(int lineIndex) {
    int paragraphIndex = getParagraphNumber(lineIndex) ;
    if (paragraphIndex < 0 || paragraphIndex >= S.size()) return;

    S[paragraphIndex]->pasteLine(lineIndex);
}


void section::toggle(int lineindex, int index) {
    int paraIndex = getParagraphNumber(lineindex) ; 

    if (paraIndex < 0 || paraIndex >= S.size() || S[paraIndex] == nullptr) {
        return; // Prevent invalid access
    }

    S[paraIndex]->Toggle(lineindex, index);
}

void section::indent(int lineIndex, int cursorColumn) {
    int paraIndex = getParagraphNumber(lineIndex);

    if (paraIndex < 0 || paraIndex >= S.size()) return;

    S[paraIndex]->indent(lineIndex, cursorColumn);
}

void section::unindent(int lineIndex, int cursorColumn) {
    int paraIndex = getParagraphNumber(lineIndex) ; 

    if (paraIndex < 0 || paraIndex >= S.size()) return; 

    S[paraIndex]->unindent(lineIndex, cursorColumn);
}

