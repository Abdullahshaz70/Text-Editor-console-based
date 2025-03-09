#pragma once
#pragma once
#include<iostream>
#include<vector>
#include"paragraph.h"



class section
{
	vector <paragraph*> S;
	

	public:

		section();
		~section();
		int sectionSize() {
			return S.size();
		}
		void addparagraph();
		void addline(int cursorRow);

		void insertline(int lineIndex, int columnIndex);
		void insertAt(int lineIndex, int columnIndex, char sym);
		void insertparagraph( int lineIndex, int columnIndex);


		int getParagraphSize(int lineindex);
		int getlineSize( int lineIndex);
        int getParagraphNumber(int cursorRow);
		int getLineSize(int lineindex);
		line* getLine(int index);

		void deleteAt(int lineIndex, int columnIndex);

		void indent(int lineIndex, int cursorColumn);
		void unindent(int lineIndex, int cursorColumn);

		void toggle(int lineindex, int index);
		void copyLine(int lineIndex);
		void pasteLine(int lineIndex);

		int findnextword(int lineIndex, int columnIndex);
		int findprevword(int lineIndex, int columnIndex);
		void deleteFrom(int lineIndex, int columnIndex);
		void startOfLine(int lineIndex, int& columnIndex);
		void endOfLine(int lineIndex, int& columnIndex);

		void print();
     
		void Erase(int paragraphIndex) {
			if (paragraphIndex < 0 || paragraphIndex >= S.size()) return;

			delete S[paragraphIndex]; // Free allocated memory
			S.erase(S.begin() + paragraphIndex);
		}

		void deleteline(int lineIndex) {
			int paraIndex = getParagraphNumber(lineIndex) - 1; // Convert to 0-based index

			if (paraIndex < 0 || paraIndex >= S.size() || S[paraIndex] == nullptr) return;

			S[paraIndex]->deleteline(lineIndex);
		}

};

