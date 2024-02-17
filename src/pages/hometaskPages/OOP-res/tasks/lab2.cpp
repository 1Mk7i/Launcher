// Спроектувати клас, що описує задану сутність. Всі властивості класу повинні бути описаними в закритій частині. Деякі з властивостей мають бути структурами.
// Реалізувати конструктор без аргументів та один чи декілька конструкторів ініціалізації з параметрами. 
// Створити методи для зміни властивостей класу (сетери) та отримання значення властивостей (гетери). Частина методів повинна мати реалізацію поза класом.
// Реалізувати метод(и), що в якості параметру приймає об’єкт даного класу. 
// В програмі обов’язково слід продемонструвати різні способи створення об’єктів - екземплярів класу та масиву об’єктів, їх ініціалізації та використання всіх методів класу.

#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct ParserData {
    string v = "5 7";
    string operations;
};

class Parser{
private:
    ParserData data;
public:
    Parser() {}

    Parser(string v, string operations) {
        data.v = v;
        data.operations = operations;
    }

    // розбиваємо рядок на числа
    vector<int> parse() {
        vector<int> result;
        string temp = "";
        for (int i = 0; i < data.v.length(); i++) {
            if (data.v[i] == ' '){
                result.push_back(stoi(temp));
                temp = "";
            } else {
                temp += data.v[i];
            }
        }
        result.push_back(stoi(temp));
        return result;
    }

    // Метод введення з клавіатури
    void Read() {
        cout << "Введіть операцію: ";
        cin >> data.operations;
    }

    // Метод визначення операцій
    void operations(){
        double result;
        for (int i = 0; i < data.operations.length(); i++) {
            if (data.operations[i] == '*') {
                cout << "Множення" << endl;
                vector<int> num = parse();
                for (int i = 0; i < num.size(); i++) {
                    result *= num[i];
                }
            } else if (data.operations[i] == '+') {
                cout << "Сума" << endl;
                vector<int> num = parse();
                for (int i = 0; i < num.size(); i++) {
                    result += num[i];
                }
            } else if (data.operations[i] == '/') {
                cout << "Ділення" << endl;
                vector<int> num = parse();
                for (int i = 0; i < num.size(); i++) {
                    result /= num[i];
                }
            } else if (data.operations[i] == '-') {
                cout << "Віднімання" << endl;
                vector<int> num = parse();
                for (int i = 0; i < num.size(); i++) {
                    result -= num[i];
                }
            } else if (data.operations[i] == '%') {
                cout << "Остача від ділення" << endl;
                vector<int> num = parse();
                for (int i = 0; i < num.size(); i++) {
                    result %= num[i];
                }
            }
        }
    }
};
    

int main() {
    Parser parser1;
    parser1.Read();
    vector<int> result = parser1.parse();
    for (int i = 0; i < result.size(); i++) {
        cout << result[i] << " ";
    }
    cout << endl;
    parser1.operations();

    return 0;
}