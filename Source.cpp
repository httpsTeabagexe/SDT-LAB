
#include "Header.h" 

#include <filesystem>

//������� ������ ����� ��������� ����������� ��� � ����������� ������, � ����� ������������ �� 
//�������������� ������ � ��������� ����� ��������� ������� �� ����, ��������� � ���� ����� ����, 
//� �������������� �����������, � ������� ���������� ��������� �����. 
vector<string> exceptions = {
    "�����", "�����" , "���������" ,"�����", "��������" ,"�����", "�����", "������", "�����",
    "�����", "�������","�����", "��������", "��������",
    "�������", "�����", "������" ,"��������", "�������", "������", "�����",
    "�������", "��������", "������", "�������", "������",
    "������", "��������", "�������", "�������", "�������", "��������", "��������", "�����",
    //����� � ���������� "���"/"���" �� ��������, �.�. ��� ���������� � "��-", ��� �������� ��������� �������. 
    //����� � ���������� "��", "��", �� ������� � ����������, ��-�� �� �������� ����������. 
    //����� ������������ ����������, ��� ��������� ������ � ����������� �������������� 
    "��������", "�������", "�����", "�������", "������", "����", "������", "������", "���������",
    "������", "������", "������", "��������", "��������", "�����", "����",
    //����� ������������ ����������, ��� ��������� ������ � ����������� �������� 
    "�����", "������" , "�������" ,"�����", "����" , "����", "������", "�����" ,"��������",
    "�������", "�����" ,"�����", "����", "������", "����", "�����", "������", "������",
    "������" , "������", "������", "�����", "������" , "����" ,"��������", "�������",
    "��������", "�����" ,"�����", "�����" , "�����", "������", "�������", "�����",
    "�����", "�������", "�������", "�������" , "�������", "�������", "����������", "��������",
    "�������", "��������", "������", "�������" , "������", "��������", "������", "������",
    "������", "�������", "��������", "��������",
    //����� ������������ ����������, ��� ��������� � ���������� ������� 
    "���", "���", "���", "���", "���������", "���������", "�����", "��������"
};
vector<string> adjectivEendings = {
    "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��", "���", "���",
    "���", "���", "��", "��" , "��", "���", "���", "��", "��", "��" , "��", "��"
};
vector<string> verbEendings = {
    "���", "��", "��", "���" , "��", "��", "���", "��",
    "��", "���", "��", "��", "��", "����", "���", "��"
};
vector<string> vowels = {
    "�", "�", "�", "�", "�", "�", "�", "�", "�"
};

vector<string> adverb = {};
int pairsCount = 0;

void all() {
    cout << "����� ���������� � ���������, ������� ���� ���� ����������� �������." << endl;
    string infoDirectory = dir(false);
    cout << "������ ������ � ����� '����������':" << endl;
    string command = "cd /d " + infoDirectory + " && dir /b *.txt";
    system(command.c_str());
    cout << "�������� ����, ���������� ��������� ����� �� ������� ����� (���� ������ ��������� � ����� '����������'). " << endl;
    inputFromFile(fileChoose().c_str(), adverb);
    cout << "�������:" << endl;
    for (const auto& str : adverb) { cout << str << " "; }
    cout << endl;
    doubleRhyme(adverb);
}


string** doubleRhyme(vector<string>& adverb) {
    int rhymeCount = 0, wordCount = 1, size = adverb.size();
    bool check = false;
    string** dynamicArrays = new string * [size]; // ������� ������������ ������ �����

    for (size_t i = 0; i < adverb.size(); ++i) {
        for (size_t j = i + 1; j < adverb.size(); ++j) {
            if (isRhyme(adverb[i], adverb[j])) { // ���������, ��������� �� �����
                if (wordCount == 1) dynamicArrays[rhymeCount] = new string[20]; // �������������� ������ ��� ����� ����������� ����
                check = true;
                dynamicArrays[rhymeCount][0] = adverb[i]; // ��������� ������ ����� ����
                dynamicArrays[rhymeCount][wordCount] = adverb[j]; // ��������� ������ ����� ����
                adverb.erase(adverb.begin() + j); // ������� ������ ����� �� ������, ����� �������� ��������
                j--;
                wordCount++;
            }
        }
        wordCount = 1; // ���������� ������� ����
        if (check) rhymeCount++; // ����������� ������� ����������� ���
        check = false; // ���������� ���� ��������
    }
    doubleRhymeOutput(dynamicArrays, rhymeCount); // ������� ���������
    return dynamicArrays; // ���������� ������ ����������� ���
}


// ������� ��� ������ ����������� ��� � �������� ���������� ���
void doubleRhymeOutput(string** mass, int massCount) {
    for (size_t i = 0; i < massCount; ++i) { // �������� �� ������ ����������� ����
        string str;
        cout << "Array contents: ";
        int j = 0;
        while (!mass[i][j].empty()) { // �������� �� ������� ����� � ������� ����
            cout << mass[i][j] << " "; // ������� �����
            str += mass[i][j] + " "; // ��������� ����� � ������ ��� �������� ���
            j++;
        }
        cout << endl;
        pairsCount += countWordPairs(str); // ������������ ���������� ��� ���� � ������ � ��������� � ������ ��������
    }
    cout << "���������� ��� ����: " << pairsCount << endl;

    // ������������ ������
    for (size_t i = 0; i < massCount; ++i) {
        delete[] mass[i]; // ������� ������ ������ �����
    }
    delete[] mass; // ������� ������ ����������
}

int countWordPairs(string str) {
    istringstream stream(str);
    string word;
    int wordCount = 0;
    while (stream >> word) { wordCount++; }
    return wordCount * (wordCount - 1) / 2;
}

// ������� ��� ����������� ����� ����
bool determinePartOfSpeech(string word) { 
    if (word.size() <= 3) return false; // ���� ����� ����� ������ ��� ����� 3, ���������� false

    if (find(exceptions.begin(), exceptions.end(), word) != exceptions.end()) return true; // ���� ����� ��������� � ������ ����������, ���������� true
    if (word.size() > 3 && word.substr(0, 3) == "��-") return true; // ���� ����� ���������� � "��-", ���������� true

    if (word.size() >= 4) {
        string ending = word.substr(word.size() - 3); // �������� ��������� �����
        if (find(vowels.begin(), vowels.end(), ending) != vowels.end()) return true; // ���� ��������� �������� �������, ���������� true
        if (find(adjectivEendings.begin(), adjectivEendings.end(), ending) != adjectivEendings.end()) return false; // ���� ��������� �������� ���������� ���������������, ���������� false
        if (find(verbEendings.begin(), verbEendings.end(), ending) != verbEendings.end()) return false; // ���� ��������� �������� ���������� �������, ���������� false
    }

    return false; // � ��������� ������� ���������� false
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
    const string vowels = "���������"; // ������� ����� �������� ����� 
    string result;
    result.reserve(input.size()); // Reserve memory to avoid multiple allocations
    for (char ch : input) {
        if (vowels.find(ch) != string::npos) {
            result += ch;
        }
    }
    return result.length() > 1 ? result : input;
}

string checkSymbol(string pas) { // ��������������� ������� ��� �������� ������������ ������ �� ����������� ������� � � ����������� ��������������.
    string result;
    result.reserve(pas.size()); // Reserve memory to avoid multiple allocations
    for (char c : pas) {
        if ((c >= '�' && c <= '�') || (c >= '�' && c <= '�')) {
            result += c;
        }
    }
    if (result.empty()) {
        cout << "����� " << pas << " ��������� �������� �� �������������� �������� � ���� �������. " << endl;
    }
    return result;
}

string unification(string str) {
    string result;
    for (char c : str) {
        if ((c >= '�' and c <= '�')) { result += c; }
        else { if ((c >= '�' and c <= '�')) { c += 32; result += c; } }
    }
    return result;
}

void inputFromFile(const char* fname, vector<string>& adverb) {  // ������� ��� ���������� ��������� ����������� �� �����.
    string word, temp, str;
    ifstream fin(fname);
    if (!fin.is_open()) { cout << "������ �������� �����." << endl; }
    while (fin) {
        getline(fin, str);
        if (!str.empty()) {
            int firstPos = 0, lastPos = 0, delta;
            while (str.find_first_not_of(" ", lastPos) != -1) {
                firstPos = str.find_first_not_of(" ", lastPos);
                lastPos = str.find_first_of(" ", firstPos);
                delta = lastPos - firstPos;
                word = str.substr(firstPos, delta); // ��������� �����: ��� ���������� � ������� �������, ������� �� ����� �������, �� ���������� ���������� �������.
                word = checkSymbol(word); word = unification(word);
                //cout << word << " - " << determinePartOfSpeech(word) << endl;
                if (!word.empty()) {
                    if ((adverb.empty() or find(adverb.begin(), adverb.end(), word) == adverb.end()) and (determinePartOfSpeech(word))) { adverb.push_back(word); }
                }
            }
        }
    }
}

string fileChoose() { //������� ������������ ���������� �����, ������� ��� ������ �������������.
    string location = dir(false);
    cout << "������� �������� ����� (��������, ���� ���� ���������� '������.txt', �� ������� ������ '������'): ";
    return isFileExists(location);
}

string isFileExists(string directory) { //������� ��� ��������� ���������� ������� ������. (������� ����������� ���������� ��������� ��� ����������� �� ���� ������ ������).
    string tempfilename = "filewithstrangename.txt", tempdirectory;
    tempdirectory = directory + "\\" + tempfilename;
    while (!fileExists(tempdirectory.c_str())) {
        getline(cin, tempfilename);
        if (tempfilename == "") {// ��� ���������� ENTER
            cout << "��������� ���������." << endl;
            remove("file.txt");
            cout << "������� ����� 1 ��� ������ �� ���������.";
            int anw = _getch();
            while (anw != '1') { anw = _getch(); }
            if (anw == 49) { exit(0); }
        }
        tempdirectory = directory + "\\" + tempfilename + ".txt";
        if (fileExists(tempdirectory.c_str())) { cout << "���� " << tempfilename + ".txt" << " ������ � �����!" << endl; return tempdirectory; }
        else if (fileExists((directory + "\\" + tempfilename).c_str())) { cout << "���� " << tempfilename << " ������ � �����!" << endl; return (directory + "\\" + tempfilename); }
        else { cout << "���� ����������� � �����, ���������� ��� ���." << endl; }
    }
}

string dir(bool mode) {
    string currentDir = filesystem::current_path().string();
    string infoDirectory = currentDir + "\\����������";
    if (mode) {
        if (filesystem::exists(infoDirectory)) {
            cout << "����� '����������' ��� ���������� � ������� ��������. � ��� ����� ��������� ��� ����." << endl;
        }
        else {
            if (filesystem::create_directory(infoDirectory)) {
                cout << "����� '����������' ������� ������� � ������� ��������. � ��� ����� ��������� ��� ����." << endl;
            }
            else {
                cerr << "�� ������� ������� ����� '����������' � ������� ��������." << endl;
                return "";
            }
        }
    }
    else {
        if (!filesystem::exists(infoDirectory)) {
            cerr << "����� '����������' ��� � ������� ��������!" << endl
                << "��� �������� ���������� �� ������ �������� ����� '����������' � �������� � �� ����� �������������� ����������." << endl;
            cerr << "������� ����� 1 ��� ���������� ���������.";
            int anw = _getch();
            while (anw != '1') { anw = _getch(); }
            if (anw == '1') { exit(0); }
        }
    }
    return infoDirectory;
}


//������� ��������� �������� ���������� ������������, ��������� ������� getHomeDirectory(). ����� ���������� ������, �������������� ���� � �������� �����.
const char* homeDir = nullptr;
string getDesktopDirectory() { 
    if ((homeDir = getenv("HOME")) == nullptr) { homeDir = getenv("USERPROFILE"); }
    if (homeDir == nullptr) { return ""; }
    if (string(homeDir).empty()) { return ""; }
    return string(homeDir) + "\\Desktop\\";
}

bool fileExists(const char* fname) { //������� ������� ����������� ������������� �����.
    _finddata_t data;
    long nFind = _findfirst(fname, &data);
    if (nFind != -1) { _findclose(nFind); return true; }
    return false;
}

void record(ofstream fileout, const char* fname) { // ������� ��� ������ � ���� ��������� � ������� � �������������.
    fileOutAdd(fname) << left << setw(20) << "�����������" << left << setw(20) << "��������� �������->" << endl;

    fileOutAdd(fname).close();

}

void fileStream(string type) {
    cout << "��� �� ������ ������� ����? (���� �� ������ ���������/������������ ��� ������������ ���� �� ����� '����������' �� ������� ����� - ������� ��� ��������. ��������, ���� ���� ���������� '������.txt', �� ������� ������ '������')" << endl;
    string filename, location;
    while (filename.empty()) {
        cout << "������� �������� �����: ";
        getline(cin, filename);
    }
    filename = checkSymbol(filename);
    location = dir(true) + "\\" + filename + ".txt";
    cout << "���� � ����� -> " << location << endl;

    if (fileExists(location.c_str())) {
        cout << "���� ��� ���� � �����. (�������� 1 ��� 2)" << endl
             << "1) ������������ ����." << endl
             << "2) ��������� ������������ ����." << endl;
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

ofstream fileOutReset(const char* fname) { //������� ��� ������ �� ����� � ���������, ���������� � �������. ���������� ������ ofstream, ��� ������ ������ � ��������� ����.
    ofstream del1;
    del1.open(fname, std::ofstream::trunc);
    del1.close();
    ofstream fout;
    fout.open(fname, ios::app);
    return fout;
}

ofstream fileOutAdd(const char* fname) { //��������� ������ ofstream � ������ fname, ��������� ������ ios::app ������ ����� ����������� � ����� �����. ���������� ������ ofstream, ��� ������ ������ � ��������� ����.
    ofstream fout;
    fout.open(fname, ios::app);
    return fout;
}
