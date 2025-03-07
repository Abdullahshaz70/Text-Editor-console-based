#pragma once
#pragma once
#include<iostream>
#include<vector>
#include"paragraph.h"



class section
{
	vector <paragraph*> S;
	int paragraphnumber = 0;

	public:

		void addparagraph();

		int getParagraphSize(int lineindex);

		void insertAt(int lineIndex, int columnIndex, char sym);
        int getParagraphNumber(int cursorRow);
		void deleteAt(int lineIndex, int columnIndex);

		void insertparagraph( int lineIndex, int columnIndex);
		int getlineSize( int lineIndex);

		void toggle(int lineindex, int index);
		void copyLine(int lineIndex);
		void pasteLine(int lineIndex);

		int findNextWord(int lineIndex, int columnIndex);
		int findPrevWord(int lineIndex, int columnIndex);
		void deleteFrom(int lineIndex, int columnIndex);
		void startOfLine(int lineIndex, int& columnIndex);
		void endOfLine(int lineIndex, int& columnIndex);

		void printSection(int lineIndex);
     

		int countDoubleEnter() {
			int count = 0;

			for (int p = 0; p < S.size(); p++) { 
				paragraph* para = S[p];

				size_t i = 0;
				while (i < para->paragraphSize()) { 
					if (para->isLineEmpty(i)) {
						count++;  
						while (i < para->paragraphSize() && para->isLineEmpty(i)) {
							i++;
						}
					}
					else {
						i++; 
					}
				}
			}

			return count; 
		}

		int sectionSize() {
			return S.size();
		}
};

