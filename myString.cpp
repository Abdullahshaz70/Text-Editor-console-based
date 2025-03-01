#include "myString.h"
#include<iostream>
//#include<string>
using namespace std;

int myString::numberSize(int _n) {
	int size = 0;
	while (_n != 0) {
		_n /= 10;
		size++;
	}
	return size;
}
int myString::l(const char* _p) {
	int _size = 0;
	for (int i = 0; _p[i] != '\0'; i++)
		_size++;
	return _size;
}
void myString::itos(int _n) {
	int dividend = 1;
	int _numberSize = numberSize(_n);
	size = _numberSize;
	Cs = new char[_numberSize + 1];

	while (_numberSize - 1 != 0) {
		dividend = dividend * 10;
		_numberSize--;
	}

	for (int i = 0; _n != 0; i++) {

		Cs[i] = _n / dividend + '0';
		_n %= dividend;
		dividend /= 10;
	}
}
void myString::clear() {

	delete[] Cs;
	Cs = nullptr;
	size = 0;

}
char myString::tolower(char _c) {

	return _c + 32;

}
char myString::toupper(char _c) {

	return _c - 32;

}
bool myString::is_Delimiter(char c, const char* delim) {
	for (int i = 0; delim[i] != '\0'; ++i) {
		if (c == delim[i])
			return true;

	}
	return false;
}

myString::myString() {
	Cs = nullptr;
	size = 0;
}
myString::myString(const char _c) {

	Cs = new char[size + 1] {};
	size++;
	for (int i = 0; i < size; i++)
		Cs[i] = _c;

}
myString::myString(const char* _p) {

	int _size = strlen(_p);

	Cs = new char[_size + 1];

	for (int i = 0; i < _size; i++)
		Cs[i] = _p[i];

	size = _size;
}
myString::myString(const int& _size, const char _c) {

	Cs = new char[_size + 1] {};

	for (int i = 0; i < _size; i++)
		Cs[i] = _c;
	size = _size;
}
myString::myString(int _n) {
	itos(_n);
}
myString::myString(const myString& _S) {

	size = _S.size;
	Cs = new char[size + 1] {};
	for (int i = 0; i < size; i++)
		Cs[i] = _S.Cs[i];

}

myString* myString::Split(char delim, int& count) {

	count = 0;
	for (int i = 0; i < size; i++) {
		if (Cs[i] != delim) {
			if (i == 0 or Cs[i - 1] == delim)
				count++;

		}
	}

	myString* A = new myString[count];

	int subIndex = 0;
	int start = 0;
	for (int i = 0; i <= size; i++) {
		if (i == size or Cs[i] == delim) {
			if (i > start) {
				int length = i - start;
				A[subIndex].Cs = new char[length + 1];
				A[subIndex].size = length;

				for (int j = 0; j < length; j++)
					A[subIndex].Cs[j] = Cs[start + j];

				A[subIndex].Cs[length] = '\0';

				subIndex++;
			}
			start = i + 1;
		}
	}

	return A;
}
myString* myString::tokene(const char* delim, int& count) {

	count = 0;
	bool inToken = false;

	for (int i = 0; i < size; i++) {
		bool isDelimiter = false;


		for (int j = 0; delim[j] != '\0'; j++) {
			if (Cs[i] == delim[j]) {
				isDelimiter = true;
				break;
			}
		}

		if (!isDelimiter) {
			if (!inToken) {
				count++;
				inToken = true;
			}
		}
		else {
			inToken = false;
		}
	}


	myString* tokens = new myString[count];

	int tokenIndex = 0;
	int start = -1;
	inToken = false;

	for (int i = 0; i <= size; i++) {
		bool isDelimiter = (i == size);
		for (int j = 0; delim[j] != '\0'; j++) {
			if (Cs[i] == delim[j]) {
				isDelimiter = true;
				break;
			}
		}

		if (!isDelimiter) {
			if (!inToken) {
				start = i;
				inToken = true;
			}
		}
		else {
			if (inToken) {

				int length = i - start;
				tokens[tokenIndex].Cs = new char[length + 1];
				tokens[tokenIndex].size = length;

				for (int k = 0; k < length; k++) {
					tokens[tokenIndex].Cs[k] = Cs[start + k];
				}
				tokens[tokenIndex].Cs[length] = '\0';

				tokenIndex++;
			}
			inToken = false;
		}
	}

	return tokens;
}

void myString::print()const {
	for (int i = 0; i < size; i++)
		cout << Cs[i] << " ";
}
int myString::lenght() {

	if (size == 0)
		return 0;

	for (int i = 0; Cs[i] != '\0'; i++)
		size++;
	return size;
}
int myString::string_to_Integer(const char* _c) {
	int product = 0;
	for (int i = 0; i < l(_c); i++)
	{
		if (i != 0)
			product *= 10;

		switch (_c[i]) {
		case '1':
			product += 1;
			break;
		case '2':
			product += 2;
			break;
		case '3':
			product += 3;
			break;
		case '4':
			product += 4;
			break;
		case '5':
			product += 5;
			break;
		case '6':
			product += 6;
			break;
		case '7':
			product += 7;
			break;
		case '8':
			product += 8;
			break;
		case '9':
			product += 9;
			break;
		case '0':
			product += 0;
			break;
		}
	}
	return product;
}
void myString::trim(const char* _c) {
	int temp = 0;
	int _size = l(_c);
	Cs = new char[_size + 1];
	for (int i = 0; i < _size; i++)
	{
		if (_c[i] == '\t' or _c[i] == '\n' or _c[i] == ' ')
			continue;
		else {
			Cs[temp++] = _c[i];
		}
	}

	size = temp;
}
char myString::characterAt(const int& i) {

	if (i > size)
	{
		cout << "ERROR" << endl;
		return '0';
	}

	return Cs[i];

}
void myString::replaceAt(const int& i, const char& _c) {
	if (i > size)
	{
		cout << "ERROR" << endl;
		return;
	}

	Cs[i] == _c;

}

bool myString::isEqual(const myString& M) {

	if (size == M.size)
	{
		for (int i = 0; i < M.size; i++) {
			if (Cs[i] != M.Cs[i])
				return false;
		}
	}

	if (size != M.size)
		return false;

	return true;
}
bool myString::isLess(const myString& M) {

	int _size = 0;

	if (size > M.size)
		_size = size;
	else
		_size = M.size;

	char c1{};
	char c2{};
	for (int i = 0; i < _size; i++) {

		c1 = tolower(Cs[i]);
		c2 = tolower(M.Cs[i]);


		if (c1 < c2)
			return true;
		else if (c1 == c2)
			continue;
	}

	return false;
}
bool myString::isGreater(const myString& M) {

	int _size = 0;

	if (size > M.size)
		_size = size;
	else
		_size = M.size;

	char c1{};
	char c2{};
	for (int i = 0; i < _size; i++) {

		c1 = tolower(Cs[i]);
		c2 = tolower(M.Cs[i]);


		if (c1 > c2)
			return true;
		else if (c1 == c2)
			continue;
	}

	return false;
}

myString::~myString() {
	clear();
}