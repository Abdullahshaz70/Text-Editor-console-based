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

void  document::sectionSize(int lineIndex) {
    D[getChapterNumber(lineIndex)]->chapterSize();
}

char* document::getContent() const {
    int totalSize = 0;
    vector<char*> chapterContents;

    for (int i = 0; i < D.size(); i++) {
        char* chapContent = D[i]->getContent();
        chapterContents.push_back(chapContent);
        totalSize += strsize(chapContent) + 1;  
    }

    char* content = new char[totalSize + 1];
    content[0] = '\0';

    for (int i = 0; i < chapterContents.size(); i++) {
        myStrcat(content, chapterContents[i]);
        if (i < chapterContents.size() - 1) myStrcat(content, "\n");

        delete[] chapterContents[i];
    }

    return content;
}

void document::writeToFile(const char* filename) {
    ofstream file(filename);
    if (!file) return;

    char* content = getContent();
    int len = strsize(content);

    int emptyLineCount = 0;
    bool lastWasEmpty = false;


    file << "#### CHAPTER ####\n\n";
    file << "==== SECTION ====\n\n";
    file << "---- Paragraph ----\n\n";

    for (int i = 0; i < len; i++) {
        if (content[i] == '\n') {
            emptyLineCount++;
            lastWasEmpty = true;
        }
        else {
            if (lastWasEmpty) {
     
                if (emptyLineCount >= 3) {
  
                    file << "\n#### CHAPTER ####\n\n";
                    file << "==== SECTION ====\n\n";
                    file << "---- Paragraph ----\n\n";
                }
                else if (emptyLineCount == 2) {

                    file << "\n==== SECTION ====\n\n";
                    file << "---- Paragraph ----\n\n";
                }
                else if (emptyLineCount == 1) {
  
                    file << "\n---- Paragraph ----\n\n";
                }

                emptyLineCount = 0;
                lastWasEmpty = false;
            }


            file << (content[i] == ' ' ? '_' : content[i]);
        }
    }

    if (lastWasEmpty) {
        if (emptyLineCount >= 3) {
            file << "\n#### CHAPTER ####\n\n";
            file << "==== SECTION ====\n\n";
            file << "---- Paragraph ----\n\n";
        }
        else if (emptyLineCount == 2) {
            file << "\n==== SECTION ====\n\n";
            file << "---- Paragraph ----\n\n";
        }
        else if (emptyLineCount == 1) {
            file << "\n---- Paragraph ----\n\n";
        }
    }

    delete[] content;
    file.close();
}

void document::insertParagraph(int cursorRow) {
    int chapterIndex = getChapterNumber(cursorRow);
    if (chapterIndex < 0 || chapterIndex >= D.size()) return;

    int sectionIndex = D[chapterIndex]->getSectionNumber(cursorRow);
    if (sectionIndex < 0 || sectionIndex >= D[chapterIndex]->chapterSize()) return;

    section* sec = D[chapterIndex]->getSection(sectionIndex);
    if (sec) {
        sec->addparagraph();
    }
}

void document::insertSection(int cursorRow) {
    int chapterIndex = getChapterNumber(cursorRow);
    if (chapterIndex < 0 || chapterIndex >= D.size()) return;

    D[chapterIndex]->addSection();
}


void document::insertChapter(int cursorRow) {
    D.push_back(new chapter());
}

void document::print() {
    for (int i = 0; i < D.size(); i++) {
        if (D[i] != nullptr) {
            D[i]->printChapter();
        }
    }
    cout << endl << endl << endl;
}

bool document::isLineEmpty(int lineIndex) {
    for (int i = 0; i < D.size(); i++) {
        if (!D[i]->isLineEmpty(lineIndex)) {
            return false;
        }
    }
    return true;
}

void document::addSection(int lineIndex) {

    D[getChapterNumber(lineIndex)]->addSection();
}