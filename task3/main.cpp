#include <iostream>
#include <ctime>
using namespace std;

double** createMatrix(int n) {
    double** m = new double*[n];
    for (int i = 0; i < n; i++)
        m[i] = new double[n];
    return m;
}

void fillRandom(double** m, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            m[i][j] = rand() % 97 - 48; // [-48..48]
}

void printMatrix(double** m, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << m[i][j] << "\t";
        cout << endl;
    }
}

void deleteMatrix(double** m, int n) {
    for (int i = 0; i < n; i++)
        delete[] m[i];
    delete[] m;
}

double findMin(double** m, int n) {
    double mn = m[0][0];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (m[i][j] < mn) mn = m[i][j];
    return mn;
}

// Сектор 3\ (i >= j) — порахувати елементи < k
int sector3BackslashCount(double** m, int n, int k) {
    int count = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j <= i; j++)
            if (m[i][j] < k) count++;
    return count;
}

// Сектор 6 (i < j) — замінити мінімумом матриці
int sector6Replace(double** m, int n, double minVal) {
    int count = 0;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++) {
            m[i][j] = minVal;
            count++;
        }
    return count;
}

int main() {
    srand(time(0));
    int n, k;
    cout << "Введіть розмір матриці n: "; cin >> n;
    cout << "Введіть число k: "; cin >> k;

    double** m = createMatrix(n);
    fillRandom(m, n);

    cout << "\nПочаткова матриця:\n";
    printMatrix(m, n);

    int cnt = sector3BackslashCount(m, n, k);
    cout << "\nСектор 3\\ — елементів < " << k << ": " << cnt << endl;

    double mn = findMin(m, n);
    int replaced = sector6Replace(m, n, mn);
    cout << "Сектор 6 — замінено елементів: " << replaced << " (на " << mn << ")" << endl;

    cout << "\nМатриця після змін:\n";
    printMatrix(m, n);

    deleteMatrix(m, n);
    return 0;
}
