#include <iostream>

using namespace std;

struct Note {
    string name;
    string phone;
    int bday[3];
};

void information() {
    
    const int N = 10;
    Note BLOCKNOTE[N];

    // Вводимо дані про людей
    for (int i = 0; i < N; i++) {
        cout << "Enter name: ";
        cin >> BLOCKNOTE[i].name;
        cout << "Enter phone: ";
        cin >> BLOCKNOTE[i].phone;
        cout << "Enter birthday (day month year): ";
        cin >> BLOCKNOTE[i].bday[0] >> BLOCKNOTE[i].bday[1] >> BLOCKNOTE[i].bday[2];
    }

    // Виводимо дані про людей в яких співпадають місяці
    cout << "Enter month: " << endl;
    int month;
    cin >> month;
    for (int i = 0; i < N; i++){
        if (month == BLOCKNOTE[i].bday[1]) {
            cout << BLOCKNOTE[i].name << " " << BLOCKNOTE[i].phone << " " << BLOCKNOTE[i].bday[0] << " " << BLOCKNOTE[i].bday[1] << " " << BLOCKNOTE[i].bday[2] << endl;
        }
    }
}

int main() {
    information();
    return 0;
}
