#include <iostream>
#include <chrono>
#include <future>
#include <cstdlib>
#include <ctime>
using namespace std;
using namespace chrono;

void showArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
}

void bubbleSort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++)
        for (int j = 0; j < size - i - 1; j++)
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
}

void insertionSort(int arr[], int size) {
    for (int i = 1; i < size; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void shellSort(int arr[], int size) {
    for (int gap = size / 2; gap > 0; gap /= 2)
        for (int i = gap; i < size; i++) {
            int temp = arr[i];
            int j = i;
            while (j >= gap && arr[j - gap] > temp) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = temp;
        }
}

int binarySearch(int arr[], int left, int right, int key) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == key) return mid;
        if (arr[mid] < key) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

int main() {
    srand(time(0));

    cout << "******************************************\n";
    cout << "\tПОРІВНЯННЯ ЧАСУ СОРТУВАННЯ\n";
    cout << "******************************************\n";

    int sizes[] = { 10, 50, 800, 5000, 40000, 120000 };
    for (int s = 0; s < 6; s++) {
        int n = sizes[s];
        int *a1 = new int[n], *a2 = new int[n], *a3 = new int[n];
        for (int i = 0; i < n; i++)
            a1[i] = a2[i] = a3[i] = rand() % 10000;

        auto t1 = high_resolution_clock::now();
        bubbleSort(a1, n);
        double tB = duration<double>(high_resolution_clock::now()-t1).count();

        auto t2 = high_resolution_clock::now();
        insertionSort(a2, n);
        double tI = duration<double>(high_resolution_clock::now()-t2).count();

        auto t3 = high_resolution_clock::now();
        shellSort(a3, n);
        double tS = duration<double>(high_resolution_clock::now()-t3).count();

        cout << "\nРозмір: " << n
             << " -> Бульбашка: " << tB << " сек."
             << ", Вставками: " << tI << " сек."
             << ", Шелла: " << tS << " сек.\n";
        cout << "------------------------------------------\n";
        delete[] a1; delete[] a2; delete[] a3;
    }

    // Синхронне та асинхронне
    cout << "\n===== СИНХРОННЕ ТА АСИНХРОННЕ =====\n";
    int n = 120000;
    int *arrS = new int[n], *arrA = new int[n];
    for (int i = 0; i < n; i++) arrS[i] = arrA[i] = rand() % 10000;

    auto ts = high_resolution_clock::now();
    shellSort(arrS, n);
    double syncT = duration<double>(high_resolution_clock::now()-ts).count();

    auto ta = high_resolution_clock::now();
    future<void> f = async(launch::async, shellSort, arrA, n);
    f.get();
    double asyncT = duration<double>(high_resolution_clock::now()-ta).count();

    cout << "Синхронне Шелла: " << syncT << " сек.\n";
    cout << "Асинхронне Шелла: " << asyncT << " сек.\n";
    delete[] arrS; delete[] arrA;

    // Бінарний пошук
    cout << "\n===== БІНАРНИЙ ПОШУК =====\n";
    int m = 20;
    int *arr = new int[m];
    for (int i = 0; i < m; i++) arr[i] = rand() % 100;
    shellSort(arr, m);
    cout << "Масив: "; showArray(arr, m);
    int key;
    cout << "Введіть число для пошуку: "; cin >> key;
    int idx = binarySearch(arr, 0, m - 1, key);
    if (idx != -1) cout << "Знайдено! Індекс: " << idx << endl;
    else cout << "Не знайдено." << endl;
    delete[] arr;
    return 0;
}
