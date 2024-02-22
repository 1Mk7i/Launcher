#include <iostream>
#include <string>

using namespace std;

string red = "\033[1;31m";
string green = "\033[1;32m";
string yellow = "\033[1;33m";
string blue = "\033[1;34m";
string magenta = "\033[1;35m";
string cyan = "\033[1;36m";
string reset = "\033[0m";

class History {
private:
    struct Action {
        int layerCode;
        string operation;
    };
    Action* actions; // Динамічний масив
    int count;
    int capacity;

public:

    History() : count(0), capacity(10) {
        actions = new Action[capacity];
    }

    ~History() {
        delete[] actions;
    }

    // Додавання дії в історію
    void add(int layerCode, string operation) {
        if (count < capacity) {
            actions[count].layerCode = layerCode;
            actions[count].operation = operation;
            count++;
        } else {
            cout << red << "Історія переповнена, не вдалося додати дію." << reset << endl;
        }
    }

    // Відміна (вилучення) дії з історії
    void deleted() {
        if (count > 0) {
            count--;
        } else {
            cout << red << "Історія порожня, немає дій для відміни." << reset << endl;
        }
    }

    // Виведення всіх дій історії
    void display() {
        if (count == 0) {
            cout << magenta << "Історія порожня." << reset << endl;
        } else {
            cout << magenta << "Дії в історії:" << reset << endl;
            for (int i = count - 1; i >= 0; i--) {
                cout << blue << "Код шару: " << yellow << actions[i].layerCode << blue << ", Операція: " << yellow << actions[i].operation << reset << endl;
            }
        }
    }
};

void printHistory(History history) {
    history.display();
}

int main() {
    History history1;
    history1.add(1, "Зміна розміру");
    history1.add(2, "Зміна кольору");
    history1.add(3, "Зміна прозорості");
    history1.add(4, "Зміна розміру");
    history1.add(5, "Зміна кольору");
    history1.add(6, "Зміна прозорості");
    history1.display();
    history1.deleted();
    history1.display();
    history1.deleted();
    history1.display();
    history1.deleted();
    history1.display();
}