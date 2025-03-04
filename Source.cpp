#include<vector>
#include "line.h"
#include"cursor.h"



int main() {
	

	line A;
	cursor Cursor;
	while (true) {
		if (_kbhit()) {
			char sym = _getch();
			Cursor.movement(sym);
		}
	}
	
	

	return 0;
}






//	switch (sym) {
//	case 'h':
//		cursorColumn--;
//		if (cursorColumn == -1)
//			cursorColumn = 0;
//
//		gotoRowCol(cursorRow, cursorColumn);
//		break;
//
//	case 'l':
//		if (A.Cs.size() != cursorColumn)
//			cursorColumn++;
//		gotoRowCol(cursorRow, cursorColumn);
//		break;
//
//	case 8:
//		if (cursorColumn > 0) {
//			delete A.Cs[cursorColumn - 1];
//			A.Cs.erase(A.Cs.begin() + cursorColumn - 1);
//			cout << " ";
//			cursorColumn--;
//		}
//
//		system("cls");
//		for (int i = 0; i < A.Cs.size(); i++) {
//			gotoRowCol(cursorRow, i);
//			cout << A.Cs[i];
//		}
//		break;
//
//	default:
//		char* newChar = new char[2];
//		newChar[0] = sym;
//		newChar[1] = '\0';
//
//		A.Cs.insert(A.Cs.begin() + cursorColumn, newChar);
//		cursorColumn++;
//
//		system("cls");
//		for (int i = 0; i < A.Cs.size(); i++) {
//			gotoRowCol(cursorRow, i);
//			cout << A.Cs[i];
//		}
//
//		gotoRowCol(cursorRow, cursorColumn);
//		break;
//	}
//
//}

//if (sym == 'h')
			//{
			//	cursorColumn--;
			//	if (cursorColumn == -1)
			//		cursorColumn=0;
			//
			//	gotoRowCol(cursorRow, cursorColumn);
			//}
			//else if (sym == 'l') {
			//
			//	if(A.Cs.size()!=cursorColumn)
			//		cursorColumn++;
			//
			//	gotoRowCol(cursorRow, cursorColumn);
			//
			//}
			//else if (int(sym) == 8) {
			//
			//	if (cursorColumn > 0) {
			//
			//		delete A.Cs[cursorColumn-1];
			//		A.Cs.erase(A.Cs.begin() + cursorColumn-1);
			//		cout << " ";
			//		//gotoRowCol(cursorRow, cursorColumn);
			//		cursorColumn--;
			//	}
			//
			//	system("cls");
			//	for (int i = 0; i < A.Cs.size(); i++) {
			//		gotoRowCol(cursorRow, i);
			//		cout << A.Cs[i];
			//	}
			//}
			//else {
			//	char* newChar = new char[2]; 
			//	newChar[0] = sym;
			//	newChar[1] = '\0'; 
			//
			//	A.Cs.insert(A.Cs.begin() + cursorColumn, newChar);
			//	cursorColumn++;
			//
			//
			//	system("cls");
			//	for (int i = 0; i < A.Cs.size(); i++) {
			//		gotoRowCol(cursorRow, i);
			//		cout << A.Cs[i];
			//	}
			//
			//
			//	gotoRowCol(cursorRow, cursorColumn);
		//
			//}