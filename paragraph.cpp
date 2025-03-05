#include "paragraph.h"

using namespace std;

void paragraph::addline() {
	line* newLine = new line();
	P.push_back(newLine);
}
//void paragraph::insertline(int index) {
//
//	if (index<0 or index>P.size())
//		return;
//
//	line* newLine = new line();
//	P.insert(P.begin() + index, newLine);
//
//}

void paragraph::insertline(int lineIndex, int columnIndex) {
	
	if (columnIndex < 0 or columnIndex > P[lineIndex]->size() or lineIndex < 0 or lineIndex >= P.size())
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