#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class Complex {
private:
    float a, b;

public:
    // Конструктор за замовчуванням
    Complex() : a(0), b(0) {}

    // Конструктор зі значеннями
    Complex(float re, float im) : a(re), b(im) {}

    // Метод ініціалізації
    void Init(float re, float im) {
        a = re;
        b = im;
    }

    // Метод введення з клавіатури
    void Read() {
        cout << "Введіть дійсну частину: ";
        cin >> a;
        cout << "Введіть уявну частину: ";
        cin >> b;
    }

    // Метод виведення на екран
    void Display() {
        cout << "(" << a << ", " << b << ")";
    }

    // Метод перетворення в рядок
    string toString() {
        stringstream SS;
        if (b < 0){
            SS << a << b << "i";
        }else{
            SS << a << "+" << b << "i";
        }
        return SS.str();
    }

    // Операція додавання
    Complex add(const Complex& other) {
        return Complex(a + other.a, b + other.b);
    }

    // Операція віднімання
    Complex sub(const Complex& other) {
        return Complex(a - other.a, b - other.b);
    }

    // Операція множення
    Complex mul(const Complex& other) {
        return Complex(a * other.a - b * other.b, a * other.b + b * other.a);
    }

    // Операція ділення
    Complex div(const Complex& other) {
        return Complex((a * other.a + b * other.b) / (other.a * other.a + other.b * other.b), (b * other.a - a * other.b) / (other.a * other.a + other.b * other.b));
    }

    // Операція порівняння
    bool equ(const Complex& other) {
        return (a == other.a && b == other.b);
    }

    // Операція спряженого числа
    Complex conj() {
        return Complex(a, -b);
    }
};

int main() {
    // Створення об'єктів
    Complex n1, n2;
    
    // Введення першого комплексного числа
    cout << "Введіть перше комплексне число:\n";
    n1.Read();
    
    // Введення другого комплексного числа
    cout << "Введіть друге комплексне число:\n";
    n2.Read();

    cout << ". . . . . . . . . . . . . . . . . . ." << endl;
    // Виведення результатів
    cout << "Перше число: ";
    n1.Display();
    cout << endl;
    cout << "Друге число: ";
    n2.Display();
    cout << endl;

    cout << ". . . . . . . . . . . . . . . . . . ." << endl;
    // Операції
    cout << "Додавання: " << (n1.add(n2)).toString() << endl;

    cout << "Віднімання: " << (n1.sub(n2)).toString() << endl;

    cout << "Множення: " << (n1.mul(n2)).toString() << endl;

    cout << "Ділення: " << (n1.div(n2)).toString() << endl;

    cout << "Порівняння: " << (n1.equ(n2) ? "Рівні" : "Не рівні") << endl;

    cout << "Спряжене першого числа: " << (n1.conj()).toString() << endl;

    return 0;
}
