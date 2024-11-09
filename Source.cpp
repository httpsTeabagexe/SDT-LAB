
#include "Header.h" 

#include <filesystem>

//подсчет общего числа найденных рифмующихся пар в поступающем тексте, а также формирование их 
//упорядоченного списка с подсчетом числа появлений каждого из слов, найденных в роли члена пары, 
//и идентификацией предложений, в которых содержатся найденные слова. 
vector<string> exceptions = {
    "долой", "домой" , "наперебой" ,"порой", "украдкой" ,"вдвое", "втрое", "надвое", "более",
    "далее", "заранее","менее", "наиболее", "наименее",
    "позднее", "ранее", "скорее" ,"невзирая", "впервые", "дорого", "итого",
    "намного", "недорого", "некого", "немного", "строго",
    "нечего", "вплотную", "вслепую", "впустую", "вручную", "зачастую", "напрямую", "более",
    //слова с окончанием "ому"/"ему" не записаны, т.к. все начинаются с "по-", что является признаком наречия. 
    //слова с окончанием "ом", "ем", не внесены в исключения, из-за их большого количества. 
    //свеху представлены исключения, для окончаний схожих с окончаниями прилагательных 
    "напролет", "незачем", "затем", "замужем", "живьем", "днем", "втроем", "вдвоем", "вчетвером",
    "видать", "вплоть", "вспять", "насмерть", "наизусть", "опять", "чуть",
    //свеху представлены исключения, для окончаний схожих с окончаниями глаголов 
    "бегом", "битком" , "босиком" ,"вверх", "вбок" , "вниз", "вглубь", "вдаль" ,"вдобавок",
    "вдоволь", "вдоль" ,"вдруг", "взад", "вконец", "вмиг", "вновь", "внутрь", "вокруг",
    "вперед" , "вплоть", "впредь", "впрок", "впрямь" , "враз" ,"врасплох", "всерьез",
    "вскользь", "вслед" ,"вслух", "замуж" , "затем", "кругом", "мельком", "набок",
    "назад", "наотрез", "наперед", "напоказ" , "наотрез", "наперед", "напоследок", "напролет",
    "напрочь", "насквозь", "наспех", "настежь" , "наугад", "невпопад", "пешком", "поверх",
    "подряд", "пополам", "прямиком", "чересчур",
    //свеху представлены исключения, для окончаний с согласными буквами 
    "ещё", "уже", "зря", "еле", "наперебой", "невзначай", "порой", "украдкой"
};
vector<string> adjectivEendings = {
    "ый", "ий", "ой", "ое", "ее", "ая", "яя", "ые", "ие", "ом", "ем", "ыми", "ими",
    "ого", "его", "ей", "ых" , "их", "ому", "ему", "ым", "им", "ую" , "юю", "ых"
};
vector<string> verbEendings = {
    "ешь", "ет", "ем", "ете" , "ут", "ют", "ишь", "ит",
    "им", "ите", "ат", "ят", "ть", "ться", "тся", "ся"
};
vector<string> vowels = {
    "у", "е", "ы", "а", "о", "э", "я", "и", "ю"
};

vector<string> adverb = {};
int pairsCount = 0;

void all() {
    cout << "Добро пожаловать в программу, которая ищет пары рифмующихся наречий." << endl;
    string infoDirectory = dir(false);
    cout << "Список файлов в папке 'Информация':" << endl;
    string command = "cd /d " + infoDirectory + " && dir /b *.txt";
    system(command.c_str());
    cout << "Выберите файл, содержащий свободный текст на русском языке (Файл должен храниться в папке 'Информация'). " << endl;
    inputFromFile(fileChoose().c_str(), adverb);
    cout << "Наречия:" << endl;
    for (const auto& str : adverb) { cout << str << " "; }
    cout << endl;
    doubleRhyme(adverb);
}


string** doubleRhyme(vector<string>& adverb) {
    int rhymeCount = 0, wordCount = 1, size = adverb.size();
    bool check = false;
    string** dynamicArrays = new string * [size]; // Создаем динамический массив строк

    for (size_t i = 0; i < adverb.size(); ++i) {
        for (size_t j = i + 1; j < adverb.size(); ++j) {
            if (isRhyme(adverb[i], adverb[j])) { // Проверяем, рифмуются ли слова
                if (wordCount == 1) dynamicArrays[rhymeCount] = new string[20]; // Инициализируем массив для новой рифмующейся пары
                check = true;
                dynamicArrays[rhymeCount][0] = adverb[i]; // Добавляем первое слово пары
                dynamicArrays[rhymeCount][wordCount] = adverb[j]; // Добавляем второе слово пары
                adverb.erase(adverb.begin() + j); // Удаляем второе слово из списка, чтобы избежать повторов
                j--;
                wordCount++;
            }
        }
        wordCount = 1; // Сбрасываем счетчик слов
        if (check) rhymeCount++; // Увеличиваем счетчик рифмующихся пар
        check = false; // Сбрасываем флаг проверки
    }
    doubleRhymeOutput(dynamicArrays, rhymeCount); // Выводим результат
    return dynamicArrays; // Возвращаем массив рифмующихся пар
}


// Функция для вывода рифмующихся пар и подсчета количества пар
void doubleRhymeOutput(string** mass, int massCount) {
    for (size_t i = 0; i < massCount; ++i) { // Проходим по каждой рифмующейся паре
        string str;
        cout << "Array contents: ";
        int j = 0;
        while (!mass[i][j].empty()) { // Проходим по каждому слову в текущей паре
            cout << mass[i][j] << " "; // Выводим слово
            str += mass[i][j] + " "; // Добавляем слово в строку для подсчета пар
            j++;
        }
        cout << endl;
        pairsCount += countWordPairs(str); // Подсчитываем количество пар слов в строке и добавляем к общему счетчику
    }
    cout << "Количество пар рифм: " << pairsCount << endl;

    // Освобождение памяти
    for (size_t i = 0; i < massCount; ++i) {
        delete[] mass[i]; // Удаляем каждый массив строк
    }
    delete[] mass; // Удаляем массив указателей
}

int countWordPairs(string str) {
    istringstream stream(str);
    string word;
    int wordCount = 0;
    while (stream >> word) { wordCount++; }
    return wordCount * (wordCount - 1) / 2;
}

// Функция для определения части речи
bool determinePartOfSpeech(string word) { 
    if (word.size() <= 3) return false; // Если длина слова меньше или равна 3, возвращаем false

    if (find(exceptions.begin(), exceptions.end(), word) != exceptions.end()) return true; // Если слово находится в списке исключений, возвращаем true
    if (word.size() > 3 && word.substr(0, 3) == "по-") return true; // Если слово начинается с "по-", возвращаем true

    if (word.size() >= 4) {
        string ending = word.substr(word.size() - 3); // Получаем окончание слова
        if (find(vowels.begin(), vowels.end(), ending) != vowels.end()) return true; // Если окончание является гласной, возвращаем true
        if (find(adjectivEendings.begin(), adjectivEendings.end(), ending) != adjectivEendings.end()) return false; // Если окончание является окончанием прилагательного, возвращаем false
        if (find(verbEendings.begin(), verbEendings.end(), ending) != verbEendings.end()) return false; // Если окончание является окончанием глагола, возвращаем false
    }

    return false; // В остальных случаях возвращаем false
}


bool isRhyme(string word1,string word2) {
    const string suffix1 = word1.substr(word1.size() - 3);
    const string suffix2 = word2.substr(word2.size() - 3);
    if (suffix1 == suffix2) return true;

    const string reduced1 = removeConsonants(word1.substr(word1.size() - 4));
    const string reduced2 = removeConsonants(word2.substr(word2.size() - 4));
    if (reduced1 == reduced2) return true;

    return removeConsonants(word1) == removeConsonants(word2);
}

string removeConsonants(string input) {
    const string vowels = "аеёиоуыэюя"; // Гласные буквы русского языка 
    string result;
    result.reserve(input.size()); // Reserve memory to avoid multiple allocations
    for (char ch : input) {
        if (vowels.find(ch) != string::npos) {
            result += ch;
        }
    }
    return result.length() > 1 ? result : input;
}

string checkSymbol(string pas) { // Вспомогательная функция для проверки передаваемой строки на специальные символы и её дальнейшего форматирования.
    string result;
    result.reserve(pas.size()); // Reserve memory to avoid multiple allocations
    for (char c : pas) {
        if ((c >= 'а' && c <= 'я') || (c >= 'А' && c <= 'Я')) {
            result += c;
        }
    }
    if (result.empty()) {
        cout << "Слово " << pas << " полностью состояло из непредвиденных символов и было удалено. " << endl;
    }
    return result;
}

string unification(string str) {
    string result;
    for (char c : str) {
        if ((c >= 'а' and c <= 'я')) { result += c; }
        else { if ((c >= 'А' and c <= 'Я')) { c += 32; result += c; } }
    }
    return result;
}

void inputFromFile(const char* fname, vector<string>& adverb) {  // Функция для заполнения структуры информацией из файла.
    string word, temp, str;
    ifstream fin(fname);
    if (!fin.is_open()) { cout << "Ошибка открытия файла." << endl; }
    while (fin) {
        getline(fin, str);
        if (!str.empty()) {
            int firstPos = 0, lastPos = 0, delta;
            while (str.find_first_not_of(" ", lastPos) != -1) {
                firstPos = str.find_first_not_of(" ", lastPos);
                lastPos = str.find_first_of(" ", firstPos);
                delta = lastPos - firstPos;
                word = str.substr(firstPos, delta); // Формируем слово: оно начинается с первого символа, который не равен пробелу, до следующего ближайшего пробела.
                word = checkSymbol(word); word = unification(word);
                //cout << word << " - " << determinePartOfSpeech(word) << endl;
                if (!word.empty()) {
                    if ((adverb.empty() or find(adverb.begin(), adverb.end(), word) == adverb.end()) and (determinePartOfSpeech(word))) { adverb.push_back(word); }
                }
            }
        }
    }
}

string fileChoose() { //Функция возвращающая директорию файла, который был указан пользователем.
    string location = dir(false);
    cout << "Введите название файла (Например, если файл называется 'пример.txt', то введите только 'пример'): ";
    return isFileExists(location);
}

string isFileExists(string directory) { //Функция для получения директории входных файлов. (Имеется возможность завершения программы при поступлении на вход пустой строки).
    string tempfilename = "filewithstrangename.txt", tempdirectory;
    tempdirectory = directory + "\\" + tempfilename;
    while (!fileExists(tempdirectory.c_str())) {
        getline(cin, tempfilename);
        if (tempfilename == "") {// Для завершения ENTER
            cout << "Программа завершена." << endl;
            remove("file.txt");
            cout << "Нажмите цифру 1 для выхода из программы.";
            int anw = _getch();
            while (anw != '1') { anw = _getch(); }
            if (anw == 49) { exit(0); }
        }
        tempdirectory = directory + "\\" + tempfilename + ".txt";
        if (fileExists(tempdirectory.c_str())) { cout << "Файл " << tempfilename + ".txt" << " найден в папке!" << endl; return tempdirectory; }
        else if (fileExists((directory + "\\" + tempfilename).c_str())) { cout << "Файл " << tempfilename << " найден в папке!" << endl; return (directory + "\\" + tempfilename); }
        else { cout << "Файл отсутствует в папке, попробуйте ещё раз." << endl; }
    }
}

string dir(bool mode) {
    string currentDir = filesystem::current_path().string();
    string infoDirectory = currentDir + "\\Информация";
    if (mode) {
        if (filesystem::exists(infoDirectory)) {
            cout << "Папка 'Информация' уже существует в текущем каталоге. В ней будет храниться Ваш файл." << endl;
        }
        else {
            if (filesystem::create_directory(infoDirectory)) {
                cout << "Папка 'Информация' успешно создана в текущем каталоге. В ней будет храниться Ваш файл." << endl;
            }
            else {
                cerr << "Не удалось создать папку 'Информация' в текущем каталоге." << endl;
                return "";
            }
        }
    }
    else {
        if (!filesystem::exists(infoDirectory)) {
            cerr << "Папки 'Информация' нет в текущем каталоге!" << endl
                << "Для загрузки информации из файлов создайте папку 'Информация' и добавьте в неё файлы сформированной информации." << endl;
            cerr << "Нажмите цифру 1 для завершения программы.";
            int anw = _getch();
            while (anw != '1') { anw = _getch(); }
            if (anw == '1') { exit(0); }
        }
    }
    return infoDirectory;
}


//Функция принимает домашнюю директорию пользователя, используя функцию getHomeDirectory(). Затем возвращает строку, представляющую путь к рабочему столу.
const char* homeDir = nullptr;
string getDesktopDirectory() { 
    if ((homeDir = getenv("HOME")) == nullptr) { homeDir = getenv("USERPROFILE"); }
    if (homeDir == nullptr) { return ""; }
    if (string(homeDir).empty()) { return ""; }
    return string(homeDir) + "\\Desktop\\";
}

bool fileExists(const char* fname) { //Булевая функция проверяющая существование файла.
    _finddata_t data;
    long nFind = _findfirst(fname, &data);
    if (nFind != -1) { _findclose(nFind); return true; }
    return false;
}

void record(ofstream fileout, const char* fname) { // Функция для записи в файл структуры с данными о производствах.
    fileOutAdd(fname) << left << setw(20) << "Предприятие" << left << setw(20) << "Имеющиеся изделия->" << endl;

    fileOutAdd(fname).close();

}

void fileStream(string type) {
    cout << "Как Вы хотите назвать файл? (Если Вы хотите дополнить/перезаписать уже существующий файл из папки 'Информация' на рабочем столе - введите его название. Например, если файл называется 'пример.txt', то введите только 'пример')" << endl;
    string filename, location;
    while (filename.empty()) {
        cout << "Введите название файла: ";
        getline(cin, filename);
    }
    filename = checkSymbol(filename);
    location = dir(true) + "\\" + filename + ".txt";
    cout << "Путь к файлу -> " << location << endl;

    if (fileExists(location.c_str())) {
        cout << "Файл уже есть в папке. (Выберите 1 или 2)" << endl
             << "1) Перезаписать файл." << endl
             << "2) Дополнить существующий файл." << endl;
        char anw;
        do {
            anw = _getch();
        } while (anw < '1' || anw > '2');

        if (anw == '1') {
            record(fileOutReset(location.c_str()), location.c_str());
        } else {
            record(fileOutAdd(location.c_str()), location.c_str());
        }
    } else {
        record(fileOutAdd(location.c_str()), location.c_str());
    }
}

ofstream fileOutReset(const char* fname) { //Удаляет все данные из файла с названием, переданным в функцию. Возвращает объект ofstream, для записи данных в указанный файл.
    ofstream del1;
    del1.open(fname, std::ofstream::trunc);
    del1.close();
    ofstream fout;
    fout.open(fname, ios::app);
    return fout;
}

ofstream fileOutAdd(const char* fname) { //создается объект ofstream с именем fname, благодаря режиму ios::app данные будут добавляться в конец файла. Возвращает объект ofstream, для записи данных в указанный файл.
    ofstream fout;
    fout.open(fname, ios::app);
    return fout;
}
