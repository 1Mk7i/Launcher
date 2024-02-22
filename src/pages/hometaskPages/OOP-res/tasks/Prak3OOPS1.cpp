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

class Queue {
private:
    struct Request {
        int userCode;
        double payment;
    };
    static const int MAX_SIZE = 100; // Максимальна кількість запитів
    Request requests[MAX_SIZE];
    int count;

public:
    Queue() : count(0) {}

    // Додавання запиту в чергу
    void add(int userCode, double payment) {
        if (count < MAX_SIZE) {
            requests[count].userCode = userCode;
            requests[count].payment = payment;
            count++;
        } else {
            cout << red << "Черга переповнена, не вдалося додати запит." << reset << endl;
        }
    }

    // Виконання (вилучення) запиту з черги
    void deleted() {
        if (count > 0) {
            for (int i = 0; i < count - 1; i++) {
                requests[i] = requests[i + 1];
            }
            count--;
        } else {
            cout << red << "Черга порожня, немає запитів для виконання." << reset << endl;
        }
    }

    // Виведення всіх запитів черги
    void display() {
        if (count == 0) {
            cout << magenta << "Черга порожня." << reset << endl;
        } else {
            cout << magenta << "Запити в черзі:" << reset << endl;
            for (int i = 0; i < count; i++) {
                cout << blue << "Код користувача: " << yellow << requests[i].userCode << blue << ", Сума оплати: " << yellow << requests[i].payment << reset << endl;
            }
        }
    }

    // Повертає кількість запитів у черзі
    int getCount() {
        return count;
    }
};

// Створення масиву черг, ініціалізація та сортування за зростанням кількості запитів
int main() {
    Queue queues[3]; // Масив з трьох черг

    // Ініціалізація черг
    queues[0].add(123, 50.0);
    queues[0].add(456, 30.0);
    queues[1].add(789, 70.0);
    queues[2].add(321, 20.0);
    queues[2].add(654, 40.0);

    // Сортування черг за зростанням кількості запитів
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2 - i; j++) {
            if (queues[j].getCount() > queues[j + 1].getCount()) {
                Queue temp = queues[j];
                queues[j] = queues[j + 1];
                queues[j + 1] = temp;
            }
        }
    }

    // Виведення всіх черг
    for (int i = 0; i < 3; i++) {
        cout << green << "Черга " << i + 1 << reset << endl;
        queues[i].display();
        cout << endl;
    }

    return 0;
}
