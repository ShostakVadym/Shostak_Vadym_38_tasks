#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int countWords(const string& s) {
    int cnt = 0; bool in = false;
    for (char c : s) {
        if (c != ' ' && c != '\t') {
            if (!in) { in = true; cnt++; }
        } else in = false;
    }
    return cnt;
}

void processFile(const string& inFile, const string& outFile, int k) {
    ifstream fin(inFile);
    ofstream fout(outFile);
    if (!fin) { cout << "Помилка відкриття файлу!\n"; return; }

    vector<string> sentences;
    string line;
    while (getline(fin, line))
        if (!line.empty()) sentences.push_back(line);
    fin.close();

    fout << "Речення з " << k << " або більше слів:\n";
    bool found = false;
    for (auto& s : sentences) {
        if (countWords(s) >= k) {
            fout << s << "\n";
            found = true;
        }
    }
    if (!found) fout << "(таких речень не знайдено)\n";
    fout.close();
    cout << "Готово! Результат у файлі: " << outFile << "\n";
}

int main() {
    int k;
    cout << "Введіть k (мін. кількість слів): "; cin >> k;
    processFile("input.txt", "output.txt", k);
    return 0;
}
