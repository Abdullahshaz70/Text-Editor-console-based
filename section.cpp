#include "section.h"


section::section() { addparagraph(); }
section::~section() {
    for (paragraph* p : S)
        delete p;
    S.clear();
}
section::section(const section& other) {
    for (int i = 0; i < other.S.size(); i++) 
        S.push_back(new paragraph(*other.S[i])); 
    
}


void section::addparagraph() {
    S.push_back(new paragraph());
}
void section::addline(int cursorRow) {
    S[getParagraphNumber(cursorRow)]->addline();
}


void section::insertAt(int lineIndex, int columnIndex, char sym) {
    int paraIndex = getParagraphNumber(lineIndex);


    if (paraIndex < 0 || paraIndex >= S.size()) {
        S.push_back(new paragraph()); 
        paraIndex = S.size() - 1;  
    }

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
int section::getTotalLines() {
    int totalLines = 0;
    for (int i = 0; i < S.size(); i++) {
        totalLines += S[i]->paragraphSize();
    }
    return totalLines;
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


void section::print(int sectionIndex) {
    //cout << "  --- Section " << sectionIndex + 1 << " ---\n";

    for (int i = 0; i < S.size(); i++) {
        if (S[i] != nullptr) {
            S[i]->printParagraph();
        }
    }
    cout << endl; 
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

int section::sectionSize() {
    return S.size();
}

void  section::Erase(int paragraphIndex) {
    if (paragraphIndex < 0 or paragraphIndex >= S.size()) return;

    delete S[paragraphIndex];
    S.erase(S.begin() + paragraphIndex);
}
void  section::deleteline(int lineIndex) {
    int paraIndex = getParagraphNumber(lineIndex) ;

    if (paraIndex < 0 || paraIndex >= S.size() || S[paraIndex] == nullptr) return;

    S[paraIndex]->deleteline(lineIndex);
}

void section::searchPattern(char* pattern, bool forward) {
    if (!pattern || strsize(pattern) == 0) return;

    for (int i = 0; i < S.size(); i++) {
        S[i]->searchPattern(pattern, forward);
    }
}
void section::moveToNextOccurrence() {
    for (int i = 0; i < S.size(); i++) {
        S[i]->moveToNextOccurrence();
    }
}
void section::moveToPreviousOccurrence() {
    for (int i = 0; i < S.size(); i++) {
        S[i]->moveToPreviousOccurrence();
    }
}
void section::searchAndReplace(const char* oldWord, const char* newWord) {
    for (int i = 0; i < S.size(); i++) {
        S[i]->searchAndReplace(oldWord, newWord);
    }
}


void section::writeToFile(const char* filename) const {
    ofstream outputFile(filename);
    if (!outputFile.is_open())
        return;

    outputFile << S.size() << endl; 

    for (int i = 0; i < S.size(); ++i) {
        outputFile << "[PARAGRAPH]" << endl;  
        outputFile << S[i]->paragraphSize() << endl; 

        for (int j = 0; j < S[i]->paragraphSize(); ++j) {
            const char* content = S[i]->getLine(j)->getContent();

            if (content[0] == '\0') { 
                outputFile << endl;
                continue;
            }

            for (int k = 0; content[k] != '\0'; ++k) {
                if (content[k] == ' ')
                    outputFile.put('_'); 
                else if (content[k] == '\t')
                    outputFile << "[TAB]"; 
                else
                    outputFile.put(content[k]);
            }

            outputFile.put('\n');  
        }
    }

    outputFile.close();
}

char* section::getContent() const {
    int totalSize = 0;
    std::vector<char*> paraContents;

    for (int i = 0; i < S.size(); i++) {
        char* paraContent = S[i]->getContent();
        paraContents.push_back(paraContent);
        totalSize += strsize(paraContent) + 1;  // 1 for '\n'
    }

    char* content = new char[totalSize + 1];
    content[0] = '\0';

    for (size_t i = 0; i < paraContents.size(); i++) {
        myStrcat(content, paraContents[i]);
        if (i < paraContents.size() - 1) myStrcat(content, "\n");

        delete[] paraContents[i];
    }

    return content;
}


bool section::isLineEmpty(int lineIndex) {
    for (int i = 0; i < S.size(); i++) {
        if (!S[i]->isLineEmpty(lineIndex)) {
            return false;
        }
    }
    return true;
}
void section::printSection() {
    for (int i = 0; i < S.size(); i++) {
        if (S[i] != nullptr) {
            S[i]->printParagraph();

        }
    }

}
