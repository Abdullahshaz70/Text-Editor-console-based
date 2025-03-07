#include "paragraph.h"
#include"mode.h"

using namespace std;


paragraph::paragraph(const char* c) {
	addline(c);
}
paragraph::paragraph() {
	addline();
}

void paragraph::addline() {
	line* newLine = new line();
	P.push_back(newLine);

}

void paragraph::addline(const char* c) {
	//line* newLine = new line(c);
	P.push_back(new line(c));
}

void paragraph::insertline(int lineIndex, int columnIndex) {
	
	if (lineIndex < 0 or lineIndex >= P.size())
		return;
	if (columnIndex < 0 or columnIndex > P[lineIndex]->size() )
		return;


	line* newLine = P[lineIndex]->splitLeft(columnIndex);
	line* newLine1 = P[lineIndex]->splitRight(columnIndex);
	delete P[lineIndex]; 
	P[lineIndex] = newLine;
	P.insert(P.begin() + lineIndex + 1, newLine1);

}

void paragraph::printParagraph() {

	for (int i = 0; i < P.size(); i++) {
		P[i]->printline();
		cout << endl;
	}

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

	if (columnIndex < 0 or columnIndex > P[lineIndex]->size() or lineIndex < 0 or lineIndex >= P.size())
		return;

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
void paragraph::insertAt(int lineIndex, int columnIndex, char sym) {
	if (lineIndex < 0 or lineIndex > P.size())
		return;

	P[lineIndex]->insertAt(columnIndex, sym);
}
void paragraph::deleteAt(int lineIndex, int columnIndex) {
	if (lineIndex < 0 or lineIndex > P.size())
		return;

	P[lineIndex]->deleteAt(columnIndex);
}
void paragraph::deletefrom(int lineIndex, int columnIndex) {
	if (lineIndex < 0 or lineIndex > P.size())
		return;

	P[lineIndex]->deleteFrom(columnIndex);
}

void paragraph::CopyLine(int lineindex) {
	
	line* A = getLine(lineindex);

	copyLine = new char [A->size() + 1] {};

	for (int i = 0; i < A->size(); i++)
		copyLine[i] = A->getCharAt(i);

	copyLine[A->size() + 1] = '\0';

}
void paragraph::pasteLine(int lineindex) {
	if (lineindex < 0 or lineindex > P.size())
		return;
	(P.insert(P.begin() + lineindex, new line(copyLine)));
	
}



void paragraph::writeToFile(const char* filename) const {
	ofstream outputFile(filename);
	if (!outputFile.is_open())
		return;
	outputFile << P.size() << endl;

	for (int i = 0; i < P.size(); ++i) {

		outputFile << P[i]->size() << endl;

		const char* content = P[i]->getContent();

		for (int j = 0; content[j] != '\0'; ++j) 
			outputFile.put(content[j] == ' ' ? '*' : content[j]);
		

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