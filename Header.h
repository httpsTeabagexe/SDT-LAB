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
#include <ostream>
#include <string>
#include <vector>
#include <windows.h> 

using namespace std;

bool determinePartOfSpeech(string word); // Функция для определения части речи
bool isRhyme(string word1, string word2);
void inputFromFile(const char* fname, vector<string>& adverb);
void all();

void doubleRhyme(vector<string>& adverb);
void doubleRhymeOutput(string** mass, int massCount);


string dir(bool mode);	/// Функция отвечает за работу с папкой "Информация"(создает/уведомляет о существовании).
bool fileExists(const char* fname);	/// Булевая функция проверяющая существование файла.
string isFileExists(string directory);	/// Функция для получения директории входных файлов. (Имеется возможность завершения программы при поступлении на вход пустой строки).
string getDesktopDirectory();	/// Функция принимает домашнюю директорию пользователя, используя функцию getHomeDirectory(). Затем возвращает строку, представляющую путь к рабочему столу.
string fileChoose(); //Функция возвращающая директорию файла, который был указан пользователем.

void fileStream(string type); //Функция необходимая для ввода желаемого названия файла и дальнейшего сохранения этого файла в папке "Информация".
void record(ofstream fileout, const char* fname); // Функция для записи в файл структуры с данными о производствах.

ofstream fileOutAdd(const char* fname);	/// Создается объект ofstream с именем fname, благодаря режиму ios::app данные будут добавляться в конец файла. Возвращает объект ofstream, для записи данных в указанный файл.
ofstream fileOutReset(const char* fname); /// Удаляет все данные из файла с названием, переданным в функцию. Возвращает объект ofstream, для записи данных в указанный файл.


string removeConsonants(string input);
string checkSymbol(string pas);
string unification(string str);

