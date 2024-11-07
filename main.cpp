#include "Header.h"

int main() {
	setlocale(0, "Rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_CTYPE, ".1251");
	setlocale(LC_ALL, "Rus");
	all();
	/*string word = "спокойный", str = "ый";
	cout << word.substr(word.size() - str.size())<<endl;
	cout << str;*/
}
