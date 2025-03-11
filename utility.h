#pragma once

#include<windows.h>

void gotoRowCol(int rpos, int cpos);
void color(int k);
void hideConsoleCursor();
void getRowColbyLeftClick(int& rpos, int& cpos);

bool islower(char c);
bool isUpper(char c);
int strsize(const char* data);
void stringcopy(char* destination, const char* source);
bool isDelimiter(char c);


void myStrcat(char* dest, const char* src);

bool wordFinder(char const* S1, char const* S2);

