#include "Header.h"

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

void all() {
    cout << "����� ���������� � ���������, ������� ���� ���� ����������� �������." << endl;
    cout << "�������� ����, ���������� ��������� ����� �� ������� ����� (���� ������ ��������� � ����� '����������' �� ������� �����). " << endl;
    inputFromFile(fileChoose().c_str(), adverb);
    cout << "�������:" << endl;
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
                cout << adverb[i] << " " << rhymeCount << " " << adverb[j] << " " << wordCount << "         =====   �����" << endl;
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

    //// ������������ ������
    //for (size_t i = 0; i < massCount; ++i) {
    //    delete[] mass[i];
    //}
    //delete[] mass;
}
bool determinePartOfSpeech(string word) { // ������� ��� ����������� ����� ����
    bool adverb = false;
    if (word.size() <= 3) { return false; }
    for (string str : exceptions) { if (word == str) { return true; } }
    if (word.size() > 3 and (word.substr(0, 3) == "��-")) { return true; }
    if (word.size() >= 4) {
        for (string str : vowels) { if (word.substr(word.size() - str.size()) == str) { adverb = true; } }
        for (string str : adjectivEendings) { if (word.substr(word.size() - str.size()) == str) { adverb = false; } }
        for (string str : verbEendings) { if (word.substr(word.size() - str.size()) == str) { adverb = false; } }
    }
    return adverb;
}

string checkSymbol(string pas) { // ��������������� ������� ��� �������� ������������ ������ �� ����������� ������� � � ����������� ��������������.
    string result;
    for (char c : pas) { if ((c >= '�' and c <= '�') or (c >= '�' and c <= '�')) { result += c; } }
    if (result.empty()) { cout << "����� " << pas << " ��������� �������� �� �������������� �������� � ���� �������. " << endl; }
    if (result.length() < pas.length() and (!result.empty())) { cout << "C������ ���� �������. ���������: "; cout << result << endl; }
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
                cout << word << " - " << determinePartOfSpeech(word) << endl;
                if (!word.empty()) {
                    if ((adverb.empty() or find(adverb.begin(), adverb.end(), word) == adverb.end()) and (determinePartOfSpeech(word))) { adverb.push_back(word); }
                }
            }
        }
    }
}

string fileChoose() { //������� ������������ ���������� �����, ������� ��� ������ �������������.
    string location;
    location = dir(false);
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
string dir(bool mode) { //������� �������� �� ������ � ������ "����������"(�������/���������� � �������������).
    string desktopDir = getDesktopDirectory();
    if (desktopDir.empty()) { cout << "�� ������� �������� ������� ���� ������������." << endl; }
    string infoDirectory = desktopDir + "����������";
    if (mode) {
        if (filesystem::exists(infoDirectory)) { cout << "����� '����������' ��� ���������� �� ������� �����. � ��� ����� ��������� ��� ����." << endl; }
        else {
            if (filesystem::create_directory(infoDirectory)) { cout << "����� '����������' ������� ������� �� ������� �����. � ��� ����� ��������� ��� ����." << endl; }
            else { cout << "�� ������� ������� ����� '����������' �� ������� �����." << endl; }
        }
    }
    if (!mode) {
        if (!filesystem::exists(infoDirectory)) {
            cout << "����� '����������' ��� �� ������� �����!" << endl << "��� �������� ���������� �� ������ �������� ����� '����������' � �������� � �� ����� �������������� ����������." << endl;
            cout << "������� ����� 1 ��� ���������� ���������.";
            int anw = _getch();
            while (anw != '1') { anw = _getch(); }
            if (anw == 49) { exit(0); }
        }
    }
    return infoDirectory;
}
string getDesktopDirectory() { //������� ��������� �������� ���������� ������������, ��������� ������� getHomeDirectory(). ����� ���������� ������, �������������� ���� � �������� �����.
    const char* homeDir = nullptr;
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

void fileStream(string type) { //������� ����������� ��� ����� ��������� �������� ����� � ����������� ���������� ����� ����� � ����� "����������".
    cout << "��� �� ������ ������� ����? (���� �� ������ ���������/������������ ��� ������������ ���� �� ����� '����������' �� ������� ����� - ������� ��� ��������. ��������, ���� ���� ���������� '������.txt', �� ������� ������ '������')" << endl;
    string filename, location;
    while (filename.empty()) { cout << "������� �������� �����: "; getline(cin, filename); }
    filename = checkSymbol(filename);
    location = dir(true);
    location = location + "\\" + filename + ".txt";
    cout << "���� � ����� -> " << location << endl;
    if (fileExists(location.c_str())) {
        cout << "���� ��� ���� � �����. (�������� 1 ��� 2)" << endl << "1) ������������ ����." << endl << "2) ��������� ������������ ����." << endl;
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
