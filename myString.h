#pragma once
class myString
{
	char* Cs;
	int size;

	int numberSize(int _n);
	int l(const char* _p);
	void itos(int _n);
	char toupper(char _c);
	char tolower(char _c);
	void clear();
	bool is_Delimiter(char c, const char* delim);

public:
	myString();
	myString(const char _c);
	myString(const char* p);
	myString(const int& _size, const char _c);
	myString(int _n);
	myString(const myString& _S);
	int lenght();
	int string_to_Integer(const char* _c);

	void print()const;
	void trim(const char* _c);
	void replaceAt(const int& index, const char& _c);
	

	char characterAt(const int& i);

	bool isEqual(const myString& M);
	bool isLess(const myString& M);
	bool isGreater(const myString& M);
	myString* Split(char delim, int& count);
	myString* Split1(char delim, int& count);
	myString* tokene(const char* delim, int& count);

	~myString();

};

