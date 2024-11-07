#include "Header.h"

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

void all() {
    cout << "Добро пожаловать в программу, которая ищет пары рифмующихся наречий." << endl;
    cout << "Выберите файл, содержащий свободный текст на русском языке (Файл должен храниться в папке 'Информация' на рабочем столе). " << endl;
    inputFromFile(fileChoose().c_str(), adverb);
    cout << "Наречия:" << endl;
    for (string str : adverb) { cout << str << " "; } cout << endl;
    doubleRhyme(adverb);
}

void doubleRhyme(vector<string>& adverb) {
    int rhymeCount = 0, wordCount = 1, size = adverb.size();
    bool check = false;
    string** dynamicArrays = new string * [size];

    for (size_t i = 0; i < adverb.size(); ++i) {
        for (size_t j = i + 1; j < adverb.size(); ++j) {
            if (isRhyme(adverb[i], adverb[j])) {
                if (wordCount == 1) dynamicArrays[rhymeCount] = new string[20];
                check = true;
                dynamicArrays[rhymeCount][0] = adverb[i];
                dynamicArrays[rhymeCount][wordCount] = adverb[j];
                cout << adverb[i] << " " << rhymeCount << " " << adverb[j] << " " << wordCount << "         =====   РИФМА" << endl;
                adverb.erase(adverb.begin() + j);
                j--;
                wordCount++;
            }
        }
        if (check) {
            cout << "Massiv: ";
            for (int j = 0; j < wordCount; j++) {
                cout << dynamicArrays[rhymeCount][j] << " ";
            }
            cout << endl;
        }
        wordCount = 1;
        if (check) rhymeCount++;
        check = false;
    }
    doubleRhymeOutput(dynamicArrays, rhymeCount);
}

void doubleRhymeOutput(string** mass, int massCount) {
    for (size_t i = 0; i < massCount; ++i) {
        cout << "Array contents: ";
        int j = 0;
        while (!mass[i][j].empty()) { cout << mass[i][j] << " "; j++; }
        cout << endl;
    }

    //// Освобождение памяти
    //for (size_t i = 0; i < massCount; ++i) {
    //    delete[] mass[i];
    //}
    //delete[] mass;
}
bool determinePartOfSpeech(string word) { // Функция для определения части речи
    bool adverb = false;
    if (word.size() <= 3) { return false; }
    for (string str : exceptions) { if (word == str) { return true; } }
    if (word.size() > 3 and (word.substr(0, 3) == "по-")) { return true; }
    if (word.size() >= 4) {
        for (string str : vowels) { if (word.substr(word.size() - str.size()) == str) { adverb = true; } }
        for (string str : adjectivEendings) { if (word.substr(word.size() - str.size()) == str) { adverb = false; } }
        for (string str : verbEendings) { if (word.substr(word.size() - str.size()) == str) { adverb = false; } }
    }
    return adverb;
}

string checkSymbol(string pas) { // Вспомогательная функция для проверки передаваемой строки на специальные символы и её дальнейшего форматирования.
    string result;
    for (char c : pas) { if ((c >= 'а' and c <= 'я') or (c >= 'А' and c <= 'Я')) { result += c; } }
    if (result.empty()) { cout << "Слово " << pas << " полностью состояло из непредвиденных символов и было удалено. " << endl; }
    if (result.length() < pas.length() and (!result.empty())) { cout << "Cимволы были удалены. Результат: "; cout << result << endl; }
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
                cout << word << " - " << determinePartOfSpeech(word) << endl;
                if (!word.empty()) {
                    if ((adverb.empty() or find(adverb.begin(), adverb.end(), word) == adverb.end()) and (determinePartOfSpeech(word))) { adverb.push_back(word); }
                }
            }
        }
    }
}

string fileChoose() { //Функция возвращающая директорию файла, который был указан пользователем.
    string location;
    location = dir(false);
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
string dir(bool mode) { //Функция отвечает за работу с папкой "Информация"(создает/уведомляет о существовании).
    string desktopDir = getDesktopDirectory();
    if (desktopDir.empty()) { cout << "Не удалось получить рабочий стол пользователя." << endl; }
    string infoDirectory = desktopDir + "Информация";
    if (mode) {
        if (filesystem::exists(infoDirectory)) { cout << "Папка 'Информация' уже существует на рабочем столе. В ней будет храниться Ваш файл." << endl; }
        else {
            if (filesystem::create_directory(infoDirectory)) { cout << "Папка 'Информация' успешно создана на рабочем столе. В ней будет храниться Ваш файл." << endl; }
            else { cout << "Не удалось создать папку 'Информация' на рабочем столе." << endl; }
        }
    }
    if (!mode) {
        if (!filesystem::exists(infoDirectory)) {
            cout << "Папки 'Информация' нет на рабочем столе!" << endl << "Для загрузки информации из файлов создайте папку 'Информация' и добавьте в неё файлы сформированной информации." << endl;
            cout << "Нажмите цифру 1 для завершения программы.";
            int anw = _getch();
            while (anw != '1') { anw = _getch(); }
            if (anw == 49) { exit(0); }
        }
    }
    return infoDirectory;
}
string getDesktopDirectory() { //Функция принимает домашнюю директорию пользователя, используя функцию getHomeDirectory(). Затем возвращает строку, представляющую путь к рабочему столу.
    const char* homeDir = nullptr;
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

void fileStream(string type) { //Функция необходимая для ввода желаемого названия файла и дальнейшего сохранения этого файла в папке "Информация".
    cout << "Как Вы хотите назвать файл? (Если Вы хотите дополнить/перезаписать уже существующий файл из папки 'Информация' на рабочем столе - введите его название. Например, если файл называется 'пример.txt', то введите только 'пример')" << endl;
    string filename, location;
    while (filename.empty()) { cout << "Введите название файла: "; getline(cin, filename); }
    filename = checkSymbol(filename);
    location = dir(true);
    location = location + "\\" + filename + ".txt";
    cout << "Путь к файлу -> " << location << endl;
    if (fileExists(location.c_str())) {
        cout << "Файл уже есть в папке. (Выберите 1 или 2)" << endl << "1) Перезаписать файл." << endl << "2) Дополнить существующий файл." << endl;
        int anw = _getch();
        while (anw < '1' or anw > '2') { anw = _getch(); }
        if (anw == 49) { record(fileOutReset(location.c_str()), location.c_str()); }
        if (anw == 50) { record(fileOutAdd(location.c_str()), location.c_str()); }

        else { record(fileOutAdd(location.c_str()), location.c_str()); }
    }
}

bool isRhyme(std::string word1, std::string word2) {
    // Convert to lowercase for case-insensitive comparison
    std::transform(word1.begin(), word1.end(), word1.begin(), ::tolower);
    std::transform(word2.begin(), word2.end(), word2.begin(), ::tolower);

    // Basic rhyme check (last two letters):
    int len1 = word1.length();
    int len2 = word2.length();
    if (len1 < 2 || len2 < 2) {
        return false;
    }
    return word1.substr(len1 - 2) == word2.substr(len2 - 2);

    //  Add more sophisticated rhyme detection logic here as needed
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
