#include "chapter.h"

chapter::chapter() {
    addSection();
}
chapter::~chapter(){
	for (section* p : C)
		delete p;
	C.clear();
}
int chapter::chapterSize() {
	return C.size();
}

void chapter::addSection() {
	C.push_back(new section());
}
void chapter::addSection(section A) {
	C.push_back(new section(A));
}
void chapter::addLine(int cursorRow) {
    C[getSectionNumber(cursorRow)]->addline(cursorRow);
}


void chapter::clear() {
	C.clear();
}

int chapter::sectionsize(int lineIndex) {
    return C[getSectionNumber(lineIndex)]->sectionSize();
}

void chapter::deleteAt(int lineIndex, int columnIndex) {
    int secIndex = getSectionNumber(lineIndex);

    if (secIndex < 0 || secIndex >= C.size() || C[secIndex] == nullptr) {
        return;
    }

    C[secIndex]->deleteAt(lineIndex, columnIndex);
}
void chapter::deletefrom(int lineIndex, int columnIndex) {
    int secIndex = getSectionNumber(lineIndex);

    if (secIndex < 0 || secIndex >= C.size()) {
        return;
    }

    C[secIndex]->deleteFrom(lineIndex, columnIndex);
}
void  chapter::deleteline(int lineIndex) {
    int secIndex = getSectionNumber(lineIndex);

    if (secIndex < 0 || secIndex >= C.size()) {
        return;
    }

    C[secIndex]->deleteline(lineIndex);
}


void chapter::insertAt(int lineIndex, int columnIndex, char sym) {
    int secIndex = getSectionNumber(lineIndex);  
    if (secIndex < 0 || secIndex >= C.size())
        return;

    int relativeLineIndex = lineIndex;
    if (secIndex > 0) {
        int offset = 0;
        for (int i = 0; i < secIndex; i++) {
            offset += C[i]->sectionSize();  
        }
        relativeLineIndex -= offset;
    }

    C[secIndex]->insertAt(relativeLineIndex, columnIndex, sym);  
}
void chapter::insertline(int lineIndex, int columnIndex) {
    int secIndex = getSectionNumber(lineIndex);
    if (secIndex < 0 || secIndex >= C.size() || C[secIndex] == nullptr)
        return;

    C[secIndex]->insertline(lineIndex, columnIndex);  
}

int chapter::getSectionNumber(int lineIndex) {
    int totalLines = 0;

    for (int i = 0; i < C.size(); i++) {
        int sectionLines = C[i]->sectionSize();

        if (lineIndex < totalLines + sectionLines)
            return i;

        totalLines += sectionLines;
    }

    return C.size()-1;  
}
int chapter::getLineSize(int lineIndex) {
    int secIndex = getSectionNumber(lineIndex);

    if (secIndex < 0 || secIndex >= C.size() || C[secIndex] == nullptr) {
        return 0;
    }

    return C[secIndex]->getLineSize(lineIndex);
}
int chapter::getTotalLines() {
    int totalLines = 0;
    for (int i = 0; i < C.size(); i++) {
        totalLines += C[i]->getTotalLines();
    }
    return totalLines;
}


void chapter::Erase(int lineIndex) {

    int secIndex = getSectionNumber(lineIndex);
    if (secIndex < 0 || secIndex >= C.size())
        return;

    delete C[secIndex]; 
    C.erase(C.begin() + secIndex);
}


int chapter::findNextWord(int lineIndex, int columnIndex) {
    int sectionIndex = getSectionNumber(lineIndex);
    if (sectionIndex < 0 || sectionIndex >= C.size()) return -1;
    return C[sectionIndex]->findnextword(lineIndex, columnIndex);
}
int chapter::findPrevWord(int lineIndex, int columnIndex) {
    int sectionIndex = getSectionNumber(lineIndex);
    if (sectionIndex < 0 || sectionIndex >= C.size()) return -1;
    return C[sectionIndex]->findprevword(lineIndex, columnIndex);
}
void chapter::startOfLine(int lineIndex, int& columnIndex) {
    int sectionIndex = getSectionNumber(lineIndex);
    if (sectionIndex < 0 || sectionIndex >= C.size()) return;
    C[sectionIndex]->startOfLine(lineIndex, columnIndex);
}
void chapter::endOfLine(int lineIndex, int& columnIndex) {
    int sectionIndex = getSectionNumber(lineIndex);
    if (sectionIndex < 0 || sectionIndex >= C.size()) return;
    C[sectionIndex]->endOfLine(lineIndex, columnIndex);
}

void chapter::copyLine(int lineIndex) {
    int sectionIndex = getSectionNumber(lineIndex);
    if (sectionIndex < 0 || sectionIndex >= C.size()) return;

    C[sectionIndex]->copyLine(lineIndex);
}
void chapter::pasteLine(int lineIndex) {
    int sectionIndex = getSectionNumber(lineIndex);
    if (sectionIndex < 0 || sectionIndex >= C.size()) return;

    C[sectionIndex]->pasteLine(lineIndex);
}

void chapter::toggle(int lineIndex, int index) {
    C[getSectionNumber(lineIndex)]->toggle(lineIndex, index);
}
void chapter::indent(int lineIndex, int cursorColumn) {
    C[getSectionNumber(lineIndex)]->indent(lineIndex, cursorColumn);
}
void chapter::unindent(int lineIndex, int cursorColumn) {
    C[getSectionNumber(lineIndex)]->unindent(lineIndex, cursorColumn);
}

void chapter::searchPattern(char* pattern, bool forward) {
    if (!pattern || strsize(pattern) == 0) return;

    for (int i = 0; i < C.size(); i++) {
        C[i]->searchPattern(pattern, forward);
    }
}
void chapter::moveToNextOccurrence() {
    for (int i = 0; i < C.size(); i++) {
        C[i]->moveToNextOccurrence();
    }
}
void chapter::moveToPreviousOccurrence() {
    for (int i = 0; i < C.size(); i++) {
       C[i]->moveToPreviousOccurrence();
    }
}
void chapter::searchAndReplace(const char* oldWord, const char* newWord) {
    for (int i = 0; i < C.size(); i++) {
        C[i]->searchAndReplace(oldWord, newWord);
    }
}

int chapter::getPragraphSize(int lineIndex) {
   return C[getSectionNumber(lineIndex)]->getParagraphSize(lineIndex);
}


line* chapter::getline(int lineindex) {
   return C[getSectionNumber(lineindex)]->getLine(lineindex);
}

//void chapter:: print() {
//    for (int i = 0; i < C.size(); i++) {
//        if (C[i] != nullptr) {
//            C[i]->print(i); 
//            cout << endl;
//        }
//    }
//}

void chapter::print(int chapterIndex) {
    //cout << "\n======= Chapter " << chapterIndex + 1 << " =======\n";

    for (int i = 0; i < C.size(); i++) {
        if (C[i] != nullptr) {
            C[i]->print(i); 
        }
    }
}