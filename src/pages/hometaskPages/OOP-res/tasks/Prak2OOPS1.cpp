#include <iostream>
#include <string>
#include <sstream>

using namespace std;

struct ComplexData {
    float a, b;
};

class Complex {
private:
    ComplexData data;

public:
    // Метод ініціалізації
    void Init(float re, float im) {
        data.a = re;
        data.b = im;
    }

    // Метод введення з клавіатури
    void Read() {
        cout << "Введіть дійсну частину: ";
        cin >> data.a;
        cout << "Введіть уявну частину: ";
        cin >> data.b;
    }

    // Метод виведення на екран
    void Display() {
        cout << "(" << data.a << ", " << data.b << ")";
    }

    // Метод перетворення в рядок
    string toString() {
        stringstream SS;
        if (data.b < 0){
            SS << data.a << data.b << "i";
        }else{
            SS << data.a << "+" << data.b << "i";
        }
        return SS.str();
    }

    // Операція додавання
    Complex add(const Complex& other) {
        Complex result;
        result.Init(data.a + other.data.a, data.b + other.data.b);
        return result;
    }

    // Операція віднімання
    Complex sub(const Complex& other) {
        Complex result;
        result.Init(data.a - other.data.a, data.b - other.data.b);
        return result;
    }

    // Операція множення
    Complex mul(const Complex& other) {
        Complex result;
        result.Init(data.a * other.data.a - data.b * other.data.b, data.a * other.data.b + data.b * other.data.a);
        return result;
    }

    // Операція ділення
    Complex div(const Complex& other) {
        Complex result;
        result.Init((data.a * other.data.a + data.b * other.data.b) / (other.data.a * other.data.a + other.data.b * other.data.b), (data.b * other.data.a - data.a * other.data.b) / (other.data.a * other.data.a + other.data.b * other.data.b));
        return result;
    }

    // Операція порівняння
    bool equ(const Complex& other) {
        return (data.a == other.data.a && data.b == other.data.b);
    }

    // Операція спряженого числа
    Complex conj() {
        Complex result;
        result.Init(data.a, -data.b);
        return result;
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
