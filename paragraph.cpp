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
	if (lineIndex < 0 || lineIndex >= P.size())
		return;

	if (columnIndex > P[lineIndex]->size())
		columnIndex = P[lineIndex]->size();

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


void paragraph::readfromfile(const char* filename) {
	ifstream inputFile(filename);
	if (!inputFile.is_open())
		return;

	P.clear(); 
	char A[20];
	int Lsize=0,Csize=0 ,j=0 , k =0;
	inputFile >> Lsize;
	char sym;
	int temp ;
	while (j < Lsize) {
		temp = 0;
		k = 0;
		inputFile >> Csize;
		
		while (k<Csize) {

			inputFile >> sym;

			if (sym != '*')
				A[temp++] = sym;
			else
				A[temp++] = ' ';

			inputFile >> sym;

			k++;
		}

		line* newLine = new line(A); 
		P.push_back(newLine);
		
		j++;
	}
	inputFile.close();
}