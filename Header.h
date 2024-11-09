#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE

#include <algorithm>
#include <cctype>
#include <conio.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <io.h>
#include <iomanip>
#include <iosfwd>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <windows.h> 

using namespace std;

bool determinePartOfSpeech(string word); // ������� ��� ����������� ����� ����
bool isRhyme(string word1, string word2);
void inputFromFile(const char* fname, vector<string>& adverb);
void all();

string** doubleRhyme(vector<string>& adverb);
void doubleRhymeOutput(string** mass, int massCount);
int countWordPairs(string str);


string dir(bool mode);	/// ������� �������� �� ������ � ������ "����������"(�������/���������� � �������������).
bool fileExists(const char* fname);	/// ������� ������� ����������� ������������� �����.
string isFileExists(string directory);	/// ������� ��� ��������� ���������� ������� ������. (������� ����������� ���������� ��������� ��� ����������� �� ���� ������ ������).
string getDesktopDirectory();	/// ������� ��������� �������� ���������� ������������, ��������� ������� getHomeDirectory(). ����� ���������� ������, �������������� ���� � �������� �����.
string fileChoose(); //������� ������������ ���������� �����, ������� ��� ������ �������������.

void fileStream(string type); //������� ����������� ��� ����� ��������� �������� ����� � ����������� ���������� ����� ����� � ����� "����������".
void record(ofstream fileout, const char* fname); // ������� ��� ������ � ���� ��������� � ������� � �������������.

ofstream fileOutAdd(const char* fname);	/// ��������� ������ ofstream � ������ fname, ��������� ������ ios::app ������ ����� ����������� � ����� �����. ���������� ������ ofstream, ��� ������ ������ � ��������� ����.
ofstream fileOutReset(const char* fname); /// ������� ��� ������ �� ����� � ���������, ���������� � �������. ���������� ������ ofstream, ��� ������ ������ � ��������� ����.


string removeConsonants(string input);
string checkSymbol(string pas);
string unification(string str);
