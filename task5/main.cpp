#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Phone {
    string name;
    int memory;
    double price;
    int camera;
    string producer;
};

void addPhone(Phone*& phones, int& size) {
    Phone p;
    cout << "Назва: "; cin.ignore(); getline(cin, p.name);
    cout << "Пам'ять (GB): "; cin >> p.memory;
    cout << "Ціна (грн): "; cin >> p.price;
    cout << "Камера (Мп): "; cin >> p.camera;
    cout << "Виробник: "; cin.ignore(); getline(cin, p.producer);
    Phone* tmp = new Phone[size + 1];
    for (int i = 0; i < size; i++) tmp[i] = phones[i];
    tmp[size] = p;
    delete[] phones; phones = tmp; size++;
    cout << "Телефон додано!\n";
}

void showAll(Phone* phones, int size) {
    if (!size) { cout << "Список порожній.\n"; return; }
    for (int i = 0; i < size; i++) {
        cout << "\n" << i+1 << ". " << phones[i].name << endl;
        cout << "   Пам'ять: " << phones[i].memory << " GB\n";
        cout << "   Ціна: " << phones[i].price << " грн\n";
        cout << "   Камера: " << phones[i].camera << " Мп\n";
        cout << "   Виробник: " << phones[i].producer << endl;
    }
}

void showSamsungApple(Phone* phones, int size) {
    cout << "\n=== Телефони Samsung та Apple ===\n";
    bool found = false;
    for (int i = 0; i < size; i++) {
        if (phones[i].producer == "Samsung" || phones[i].producer == "Apple") {
            cout << phones[i].name << " (" << phones[i].producer
                 << ") - " << phones[i].price << " грн\n";
            found = true;
        }
    }
    if (!found) cout << "Телефонів Samsung/Apple не знайдено.\n";
}

void saveToFile(Phone* phones, int size) {
    ofstream f("phones.txt");
    for (int i = 0; i < size; i++)
        f << phones[i].name << "\n" << phones[i].memory << "\n"
          << phones[i].price << "\n" << phones[i].camera << "\n"
          << phones[i].producer << "\n";
    f.close(); cout << "Збережено!\n";
}

void loadFromFile(Phone*& phones, int& size) {
    ifstream f("phones.txt"); if (!f) return;
    Phone p;
    while (getline(f, p.name)) {
        f >> p.memory >> p.price >> p.camera; f.ignore();
        getline(f, p.producer);
        Phone* tmp = new Phone[size + 1];
        for (int i = 0; i < size; i++) tmp[i] = phones[i];
        tmp[size] = p;
        delete[] phones; phones = tmp; size++;
    }
    f.close();
}

void removePhone(Phone*& phones, int& size) {
    if (!size) { cout << "Список порожній.\n"; return; }
    showAll(phones, size);
    int idx; cout << "Номер для видалення: "; cin >> idx;
    if (idx < 1 || idx > size) return;
    Phone* tmp = new Phone[size - 1];
    for (int i = 0, j = 0; i < size; i++)
        if (i != idx - 1) tmp[j++] = phones[i];
    delete[] phones; phones = tmp; size--;
    cout << "Видалено!\n";
}

int main() {
    Phone* phones = nullptr; int size = 0;
    loadFromFile(phones, size);
    int ch;
    do {
        cout << "\n1.Додати\n2.Переглянути\n3.Samsung/Apple\n";
        cout << "4.Видалити\n5.Зберегти\n0.Вихід\nВибір: ";
        cin >> ch;
        switch(ch) {
            case 1: addPhone(phones, size); break;
            case 2: showAll(phones, size); break;
            case 3: showSamsungApple(phones, size); break;
            case 4: removePhone(phones, size); break;
            case 5: saveToFile(phones, size); break;
            case 0: break;
            default: cout << "Невірний вибір!\n";
        }
    } while (ch != 0);
    delete[] phones;
    return 0;
}
