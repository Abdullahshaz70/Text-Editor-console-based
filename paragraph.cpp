#include "paragraph.h"


void paragraph::addline() {
	line* newLine = new line();
	P.push_back(newLine);
}
void paragraph::insertline(int index) {

	if (index<0 or index>P.size())
		return;

	line* newLine = new line();
	P.insert(P.begin() + index, newLine);

}
void paragraph::printParagraph() {

	for (int i = 0; i < P.size(); i++) {
		P[i]->printline();
		cout << endl;
	}

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