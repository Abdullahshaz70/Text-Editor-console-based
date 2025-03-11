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
		int sectionSize();
		section(const section& other);
		void addparagraph();
		void addline(int cursorRow);

		void insertline(int lineIndex, int columnIndex);
		void insertAt(int lineIndex, int columnIndex, char sym);
	

		int getParagraphSize(int lineindex);
		int getTotalLines();
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

		void searchPattern(char* pattern, bool forward);
		void moveToNextOccurrence();
		void moveToPreviousOccurrence();
		void searchAndReplace(const char* oldWord, const char* newWord);

		void print(int i=0);
     

		void Erase(int paragraphIndex);

		void deleteline(int lineIndex);
		void writeToFile(const char* filename) const;


		char* getContent() const {
			int totalSize = 0;
			for (int i = 0; i < S.size(); i++) {
				char* paraContent = S[i]->getContent();
				totalSize += strsize(paraContent) + 2; // +2 for paragraph separator "\n\n"
				delete[] paraContent;
			}

			char* content = new char[totalSize + 1]; // Extra space for '\0'
			content[0] = '\0';

			for (int i = 0; i < S.size(); i++) {
				char* paraContent = S[i]->getContent();
				myStrcat(content, paraContent);
				if (i < S.size() - 1) myStrcat(content, "\n\n"); // Separate paragraphs
				delete[] paraContent;
			}

			return content;
		}

};

