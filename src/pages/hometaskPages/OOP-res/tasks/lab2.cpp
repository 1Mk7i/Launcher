// Спроектувати клас, що описує задану сутність. Всі властивості класу повинні бути описаними в закритій частині. Деякі з властивостей мають бути структурами.
// Реалізувати конструктор без аргументів та один чи декілька конструкторів ініціалізації з параметрами. 
// Створити методи для зміни властивостей класу (сетери) та отримання значення властивостей (гетери). Частина методів повинна мати реалізацію поза класом.
// Реалізувати метод(и), що в якості параметру приймає об’єкт даного класу. 
// В програмі обов’язково слід продемонструвати різні способи створення об’єктів - екземплярів класу та масиву об’єктів, їх ініціалізації та використання всіх методів класу.

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class TParcer {
    private:
        string str = "2 % 5";
    public:
        // розбиття рядка на числа та знаки
        void parse() {
            vector<int> numbers;
            vector<char> signs;
            string temp = "";
            for (int i = 0; i < str.length(); i++) {
                if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' || str[i] == '%') {
                    numbers.push_back(stoi(temp));
                    temp = "";
                    signs.push_back(str[i]);
                } else {
                    temp += str[i];
                }
            }
            numbers.push_back(stoi(temp));
            for (int i = 0; i < numbers.size(); i++) {
                cout << numbers[i] << " ";
            }
            cout << endl;
            for (int i = 0; i < signs.size(); i++) {
                cout << signs[i] << " ";
            }
            cout << endl;
        }

        void calculate() {
            vector<int> numbers;
            vector<char> signs;
            string temp = "";
            for (int i = 0; i < str.length(); i++) {
                if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' || str[i] == '%') {
                    numbers.push_back(stoi(temp));
                    temp = "";
                    signs.push_back(str[i]);
                } else {
                    temp += str[i];
                }
                cout << temp << endl;
            }
            numbers.push_back(stoi(temp));
            for (int i = 0; i < signs.size(); i++) {
                if (signs[i] == '*') {
                    numbers[i] *= numbers[i + 1];
                    numbers.erase(numbers.begin() + i + 1);
                    signs.erase(signs.begin() + i);
                    i--;
                } else if (signs[i] == '/') {
                    numbers[i] /= numbers[i + 1];
                    numbers.erase(numbers.begin() + i + 1);
                    signs.erase(signs.begin() + i);
                    i--;
                }
            }
            for (int i = 0; i < numbers.size(); i++) {
                if (signs[i] == '%') {
                    numbers[i] %= numbers[i + 1];
                    numbers.erase(numbers.begin() + i + 1);
                    signs.erase(signs.begin() + i);
                    i--;
                }
            }
            for (int i = 0; i < signs.size(); i++) {
                if (signs[i] == '+') {
                    numbers[i] += numbers[i + 1];
                } else if (signs[i] == '-') {
                    numbers[i] -= numbers[i + 1];
                }
            }
            cout << numbers[0] << endl;
        }
};

int main() {
    TParcer parcer;
    parcer.parse();
    parcer.calculate();

    return 0;
}