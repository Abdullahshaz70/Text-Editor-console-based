#include "paragraph.h"
#include"mode.h"
#include"utility.h"

using namespace std;
char* paragraph::copyLine = nullptr;

paragraph::paragraph(const char* c) {
	addline(c);
}
paragraph::paragraph() {
	addline();
}
paragraph::paragraph(const paragraph& other) {
	for (const auto& linePtr : other.P) {
		P.push_back(new line(linePtr->getContent()));
	}
}

void paragraph::addline() {
	
	line* newLine = new line();
	P.push_back(newLine);
	
}
void paragraph::addline(const char* c) {
	
	line* newLine = new line(c);
	P.push_back(newLine);
	
}
void paragraph::insertline(int lineIndex, int columnIndex) {
	if (lineIndex < 0 or lineIndex >= P.size()) return; 

	line* leftPart = P[lineIndex]->splitLeft(columnIndex);  
	line* rightPart = P[lineIndex]->splitRight(columnIndex); 


	delete P[lineIndex];
	P[lineIndex] = leftPart;

	
	P.insert(P.begin() + lineIndex + 1, rightPart);
}


void paragraph::printLine(int lineIndex) {

	P[lineIndex]->printline();

}
int paragraph::getlinesize(int lineIndx) {

	return P[lineIndx]->size();
}

int paragraph::findnextword(int lineIndex , int columnIndex) {
	return P[lineIndex]->findNextWord(columnIndex);
}
int paragraph::findprevword(int lineIndex, int columnIndex) {

	return P[lineIndex]->findPrevWord(columnIndex);
}
void paragraph::startofline(int lineIndex, int& index) {
	P[lineIndex]->startofLine(index);
}
void paragraph::endofline(int lineIndex, int& index) {
	P[lineIndex]->endofLine(index);
}
void paragraph::Toggle(int lineIndex, int columnIndex) {
	
	P[lineIndex]->toggle(columnIndex);
}


int paragraph::paragraphSize() {
	return P.size();
}
line* paragraph::getLine(int index){

	if (index<0 or index>P.size())
		return nullptr;

	return P[index];
}

void paragraph::popBack() {
	P.pop_back();
}


void paragraph::insertAt(int lineIndex, int columnIndex, char sym) {
	if (lineIndex < 0) return;

	

	while (lineIndex >= P.size()) {
		P.push_back(new line());  
	}

	
	if (!P[lineIndex]) {
		P[lineIndex] = new line();
	}

	
	int maxColumn = (P[lineIndex] ? P[lineIndex]->size() : 0);
	if (columnIndex > maxColumn) {
		columnIndex = maxColumn;
	}


	P[lineIndex]->insertAt(columnIndex, sym);
}


void paragraph::deleteAt(int lineIndex, int columnIndex) {
	if (lineIndex < 0 || lineIndex >= P.size() || P[lineIndex] == nullptr) {
		return; 
	}

	P[lineIndex]->deleteAt(columnIndex);
}
void paragraph::deletefrom(int lineIndex, int columnIndex) {
	if (lineIndex < 0 or lineIndex > P.size())
		return;

	P[lineIndex]->deleteFrom(columnIndex);
}

void paragraph::CopyLine(paragraph& P, int lineIndex) {
	if (lineIndex < 0 || lineIndex >= P.paragraphSize()) return;

	if (copyLine != nullptr)
		delete[] copyLine;  

	const char* lineContent = P.getLine(lineIndex)->getContent();
	int length = P.getlinesize(lineIndex);

	copyLine = new char[length + 1];  
	stringcopy(copyLine, lineContent);  
}
void paragraph::pasteLine(int lineIndex) {
	if (copyLine == nullptr) return;

	if (lineIndex < 0 || lineIndex >= paragraphSize()) return;

	insertline(lineIndex, 0);  // Insert a new line at the given index

	line* newLine = getLine(lineIndex);  // Get the newly created line

	for (int i = 0; copyLine[i] != '\0'; i++) {
		newLine->insertAt(i, copyLine[i]);  // Insert copied content character by character
	}
}


bool paragraph::isLineEmpty(int lineIndex) {
	if (lineIndex < 0 or lineIndex >= P.size())
		return true;



	if (P[lineIndex] == nullptr)
		return true;

	return P[lineIndex]->isEmpty();
}


void  paragraph::searchPattern(char* pattern, bool forward) {
	if (!pattern or strsize(pattern) == 0) return;

	stringcopy(lastPattern, pattern);

	int start = forward ? 0 : P.size() - 1;
	int end = forward ? P.size() : -1;
	int step = forward ? 1 : -1;

	for (int i = start; i != end; i += step) {
		if (wordFinder(P[i]->getContent(), pattern)) {
			lastFoundIndex = i;
			cout << "Found in Line " << i + 1 << ": " << P[i]->getContent() << endl;
			return;
		}
	}

	cout << "Pattern not found!\n";
	lastFoundIndex = -1;
}
void  paragraph::moveToNextOccurrence() {

	if (strsize(lastPattern) == 0 or lastFoundIndex == -1) {
		cout << "No previous search!\n";
		return;
	}

	for (int i = lastFoundIndex + 1; i < P.size(); ++i) {
		if (wordFinder(P[i]->getContent(), lastPattern)) {
			lastFoundIndex = i;
			cout << "Next occurrence in Line " << i + 1 << ": " << P[i]->getContent() << endl;
			return;
		}
	}

	cout << "No more occurrences found!\n";
}
void  paragraph::moveToPreviousOccurrence() {
	if (strsize(lastPattern) == 0 or lastFoundIndex == -1) {
		cout << "No previous search!\n";
		return;
	}

	for (int i = lastFoundIndex - 1; i >= 0; --i) {
		if (wordFinder(P[i]->getContent(), lastPattern)) {
			lastFoundIndex = i;
			cout << "Previous occurrence in Line " << i + 1 << ": " << P[i]->getContent() << endl;
			return;
		}
	}

	cout << "No previous occurrences found!\n";
}
void paragraph::searchAndReplace(const char* oldWord, const char* newWord) {
	int oldLen = 0, newLen = 0;


	while (oldWord[oldLen] != '\0') oldLen++;
	while (newWord[newLen] != '\0') newLen++;

	for (int i = 0; i < P.size(); i++) {
		line* currentLine = P[i];
		int lineLength = currentLine->size();
		const char* content = currentLine->getContent();


		char* newContent = new char[lineLength * 2];
		int newIndex = 0, j = 0;

		while (j < lineLength) {
			bool match = true;

			for (int k = 0; k < oldLen; k++) {
				if (content[j + k] == '\0' or content[j + k] != oldWord[k]) {
					match = false;
					break;
				}
			}


			if (match) {
				for (int k = 0; k < newLen; k++)
					newContent[newIndex++] = newWord[k];

				j += oldLen;
			}
			else {
				newContent[newIndex++] = content[j++];
			}
		}

		newContent[newIndex] = '\0';
		P[i]->updateline(newContent);


	}

}

void paragraph::writeToFile(const char* filename) const {
	ofstream outputFile(filename);
	if (!outputFile.is_open())
		return;

	outputFile << P.size() << endl; 

	int enterCount = 0; 

	for (int i = 0; i < P.size(); ++i) {
		outputFile << P[i]->size() << endl; 

		const char* content = P[i]->getContent();
		if (content[0] == '\0') { 
			enterCount++;
			if (enterCount == 2) {
				outputFile << "[SECTION]" << endl;
				enterCount = 0; 
				continue;
			}
			else if (enterCount == 3) {
				outputFile << "[CHAPTER]" << endl;
				enterCount = 0; 
				continue;
			}
		}
		else {
			enterCount = 0; 
		}

		for (int j = 0; content[j] != '\0'; ++j) {
			if (content[j] == ' ')
				outputFile.put('_'); 
			else if (content[j] == '\t')
				outputFile << "[TAB]"; 
			else
				outputFile.put(content[j]);
		}

		outputFile.put('\n'); 
	}

	outputFile.close();
}

char* paragraph::getContent() const {
	int totalSize = 0;
	for (int i = 0; i < P.size(); i++) {
		totalSize += strsize(P[i]->getContent()) + 1;  // 1 for '\n'
	}

	char* content = new char[totalSize + 1];
	content[0] = '\0';

	for (int i = 0; i < P.size(); i++) {
		myStrcat(content, P[i]->getContent());
		if (i < P.size() - 1) myStrcat(content, "\n");
	}

	return content;
}

void paragraph::deleteline(int lineIndex) {
	P[lineIndex]->clear();
}



void  paragraph::indent(int lineIndex, int cursorColumn) {

	P[lineIndex]->indent(cursorColumn);
}

void paragraph::unindent(int lineIndex, int cursorColumn) {

	P[lineIndex]->unindent(cursorColumn);
}