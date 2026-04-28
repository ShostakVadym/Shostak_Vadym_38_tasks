#include <iostream>
#include <cmath>
using namespace std;

// Функція обчислення відстані між двома точками
double distance(double x1, double y1, double x2, double y2) {
    return sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));
}

// Функція обчислення площі трикутника за формулою Герона
double heronArea(double a, double b, double c) {
    double p = (a + b + c) / 2.0;
    return sqrt(p * (p-a) * (p-b) * (p-c));
}

// Функція обчислення площі п'ятикутника
// Розбиваємо на 3 трикутники від вершини M1:
// T1: M1-M2-M3,  T2: M1-M3-M4,  T3: M1-M4-M5
double pentagonArea(double x[], double y[]) {
    double total = 0.0;
    for (int i = 1; i <= 3; i++) {
        double a = distance(x[0], y[0], x[i],   y[i]);
        double b = distance(x[i], y[i], x[i+1], y[i+1]);
        double c = distance(x[0], y[0], x[i+1], y[i+1]);
        total += heronArea(a, b, c);
    }
    return total;
}

int main() {
    double x[] = { 0, 1, 3, 5, 4 };
    double y[] = { 0, 2, 2, 0, -2 };

    cout << "Вершини п'ятикутника:\n";
    for (int i = 0; i < 5; i++)
        cout << "M" << i+1 << "(" << x[i] << ";" << y[i] << ") ";
    cout << endl;

    double area = pentagonArea(x, y);
    cout << "\nПлоща п'ятикутника = " << area << endl;

    return 0;
}
