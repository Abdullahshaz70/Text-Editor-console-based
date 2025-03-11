#include "Document.h"

#include "document.h"

document::document() {}

document::~document() {
    for (chapter* ch : D)
        delete ch;
    D.clear();
}

int document::documentSize() {
    return D.size();
}

void document::addChapter() {
    D.push_back(new chapter());
}

void document::addChapter(chapter A) {
    D.push_back(new chapter(A));
}

void document::addLine(int cursorRow) {
    D[getChapterNumber(cursorRow)]->addLine(cursorRow);
}

void document::clear() {
    D.clear();
}

void document::deleteAt(int lineIndex, int columnIndex) {
    int chapIndex = getChapterNumber(lineIndex);
    if (chapIndex < 0 || chapIndex >= D.size() || D[chapIndex] == nullptr) return;
    D[chapIndex]->deleteAt(lineIndex, columnIndex);
}

void document::deleteFrom(int lineIndex, int columnIndex) {
    int chapIndex = getChapterNumber(lineIndex);
    if (chapIndex < 0 || chapIndex >= D.size()) return;
    D[chapIndex]->deletefrom(lineIndex, columnIndex);
}

void document::deleteLine(int lineIndex) {
    int chapIndex = getChapterNumber(lineIndex);
    if (chapIndex < 0 || chapIndex >= D.size()) return;
    D[chapIndex]->deleteline(lineIndex);
}

void document::insertAt(int lineIndex, int columnIndex, char sym) {
    int chapIndex = getChapterNumber(lineIndex);
    if (chapIndex < 0 || chapIndex >= D.size()) return;

    int relativeLineIndex = lineIndex;
    if (chapIndex > 0) {
        int offset = 0;
        for (int i = 0; i < chapIndex; i++) {
            offset += D[i]->getTotalLines();
        }
        relativeLineIndex -= offset;
    }

    D[chapIndex]->insertAt(relativeLineIndex, columnIndex, sym);
}

void document::insertLine(int lineIndex, int columnIndex) {
    int chapIndex = getChapterNumber(lineIndex);
    if (chapIndex < 0 || chapIndex >= D.size() || D[chapIndex] == nullptr) return;
    D[chapIndex]->insertline(lineIndex, columnIndex);
}

int document::getChapterNumber(int lineIndex) {
    int totalLines = 0;

    for (int i = 0; i < D.size(); i++) {
        int chapterLines = D[i]->getTotalLines();

        if (lineIndex < totalLines + chapterLines)
            return i;

        totalLines += chapterLines;
    }

    return D.size() - 1;
}

int document::getLineSize(int lineIndex) {
    int chapIndex = getChapterNumber(lineIndex);
    if (chapIndex < 0 || chapIndex >= D.size() || D[chapIndex] == nullptr) return 0;
    return D[chapIndex]->getLineSize(lineIndex);
}

int document::getTotalLines() {
    int totalLines = 0;
    for (int i = 0; i < D.size(); i++) {
        totalLines += D[i]->getTotalLines();
    }
    return totalLines;
}

void document::Erase(int lineIndex) {
    int chapIndex = getChapterNumber(lineIndex);
    if (chapIndex < 0 || chapIndex >= D.size()) return;
    delete D[chapIndex];
    D.erase(D.begin() + chapIndex);
}

int document::findNextWord(int lineIndex, int columnIndex) {
    int chapIndex = getChapterNumber(lineIndex);
    if (chapIndex < 0 || chapIndex >= D.size()) return -1;
    return D[chapIndex]->findNextWord(lineIndex, columnIndex);
}

int document::findPrevWord(int lineIndex, int columnIndex) {
    int chapIndex = getChapterNumber(lineIndex);
    if (chapIndex < 0 || chapIndex >= D.size()) return -1;
    return D[chapIndex]->findPrevWord(lineIndex, columnIndex);
}

void document::startOfLine(int lineIndex, int& columnIndex) {
    int chapIndex = getChapterNumber(lineIndex);
    if (chapIndex < 0 || chapIndex >= D.size()) return;
    D[chapIndex]->startOfLine(lineIndex, columnIndex);
}

void document::endOfLine(int lineIndex, int& columnIndex) {
    int chapIndex = getChapterNumber(lineIndex);
    if (chapIndex < 0 || chapIndex >= D.size()) return;
    D[chapIndex]->endOfLine(lineIndex, columnIndex);
}

void document::copyLine(int lineIndex) {
    int chapIndex = getChapterNumber(lineIndex);
    if (chapIndex < 0 || chapIndex >= D.size()) return;
    D[chapIndex]->copyLine(lineIndex);
}

void document::pasteLine(int lineIndex) {
    int chapIndex = getChapterNumber(lineIndex);
    if (chapIndex < 0 || chapIndex >= D.size()) return;
    D[chapIndex]->pasteLine(lineIndex);
}

void document::toggle(int lineIndex, int index) {
    D[getChapterNumber(lineIndex)]->toggle(lineIndex, index);
}

void document::indent(int lineIndex, int cursorColumn) {
    D[getChapterNumber(lineIndex)]->indent(lineIndex, cursorColumn);
}

void document::unindent(int lineIndex, int cursorColumn) {
    D[getChapterNumber(lineIndex)]->unindent(lineIndex, cursorColumn);
}

void document::searchPattern(char* pattern, bool forward) {
    if (!pattern || strsize(pattern) == 0) return;
    for (int i = 0; i < D.size(); i++) {
        D[i]->searchPattern(pattern, forward);
    }
}

void document::moveToNextOccurrence() {
    for (int i = 0; i < D.size(); i++) {
        D[i]->moveToNextOccurrence();
    }
}

void document::moveToPreviousOccurrence() {
    for (int i = 0; i < D.size(); i++) {
        D[i]->moveToPreviousOccurrence();
    }
}

void document::searchAndReplace(const char* oldWord, const char* newWord) {
    for (int i = 0; i < D.size(); i++) {
        D[i]->searchAndReplace(oldWord, newWord);
    }
}

void document::print() {
    for (int i = 0; i < D.size(); i++) {
        if (D[i] != nullptr) {
            D[i]->print();
            std::cout << std::endl;
        }
    }
}

void  document::sectionSize(int lineIndex) {
    D[getChapterNumber(lineIndex)]->chapterSize();
}



void document::writeToFile(const char* filename) {
    ofstream file(filename);
    if (!file) return;

    for (int i = 0; i < D.size(); i++) {
        file << "\n\n\n\n"; 
        for (int j = 0; j < D[i]->chapterSize(); j++) {
            file << "\n\n\n";
            for (int k = 0; k < D[i]->sectionsize(j); k++) {
                file << "\n\n"; 
                for (int l = 0; l < D[i]->getPragraphSize(k); l++) {
                    file << D[i].get(l)<< "\n";
                }
            }
        }
    }
    file.close();
}


//void document::readFromFile(const char* filename) {
//    ifstream file(filename);
//    if (!file) return;
//
//    D.clear();
//    string line;
//    int newlineCount = 0;
//    chapter* currentChapter = nullptr;
//    section* currentSection = nullptr;
//    paragraph* currentParagraph = nullptr;
//
//    while (getline(file, line)) {
//        if (line.empty()) {
//            newlineCount++;
//            continue;
//        }
//
//        if (newlineCount >= 4 || D.empty()) { // New Chapter
//            D.push_back(new chapter());
//            currentChapter = &D.back();
//            currentChapter->addSection();
//            currentSection = currentChapter->C.back();
//            currentSection->addParagraph();
//            currentParagraph = currentSection->S.back();
//        }
//        else if (newlineCount == 3) { // New Section
//            currentChapter->addSection();
//            currentSection = currentChapter->C.back();
//            currentSection->addParagraph();
//            currentParagraph = currentSection->S.back();
//        }
//        else if (newlineCount == 2) { // New Paragraph
//            currentSection->addParagraph();
//            currentParagraph = currentSection->S.back();
//        }
//
//        currentParagraph->addLine(line);
//        newlineCount = 0;
//    }
//    file.close();
//}
