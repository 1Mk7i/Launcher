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
    void Init(float re, float im) {
        data.a = re;
        data.b = im;
    }

    void Read() {
        cout << "Введіть дійсну частину: ";
        cin >> data.a;
        cout << "Введіть уявну частину: ";
        cin >> data.b;
    }

    void Display() {
        cout << "(" << data.a << ", " << data.b << ")";
    }

    string toString() {
        stringstream SS;
        if (data.b < 0){
            SS << data.a << data.b << "i";
        }else{
            SS << data.a << "+" << data.b << "i";
        }
        return SS.str();
    } 

    friend Complex add(const Complex& c1, const Complex& c2);
    friend Complex sub(const Complex& c1, const Complex& c2);
    friend Complex mul(const Complex& c1, const Complex& c2);
    friend Complex div(const Complex& c1, const Complex& c2);
    friend bool equ(const Complex& c1, const Complex& c2);
    friend Complex conj(const Complex& c);
};

Complex add(const Complex& c1, const Complex& c2) {
    Complex result;
    result.Init(c1.data.a + c2.data.a, c1.data.b + c2.data.b);
    return result;
}

Complex sub(const Complex& c1, const Complex& c2) {
    Complex result;
    result.Init(c1.data.a - c2.data.a, c1.data.b - c2.data.b);
    return result;
}

Complex mul(const Complex& c1, const Complex& c2) {
    Complex result;
    result.Init(c1.data.a * c2.data.a - c1.data.b * c2.data.b, c1.data.a * c2.data.b + c1.data.b * c2.data.a);
    return result;
}

Complex div(const Complex& c1, const Complex& c2) {
    Complex result;
    result.Init((c1.data.a * c2.data.a + c1.data.b * c2.data.b) / (c2.data.a * c2.data.a + c2.data.b * c2.data.b), (c1.data.b * c2.data.a - c1.data.a * c2.data.b) / (c2.data.a * c2.data.a + c2.data.b * c2.data.b));
    return result;
}

bool equ(const Complex& c1, const Complex& c2) {
    return (c1.data.a == c2.data.a && c1.data.b == c2.data.b);
}

Complex conj(const Complex& c) {
    Complex result;
    result.Init(c.data.a, -c.data.b);
    return result;
}

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
    cout << "Додавання: " << add(n1, n2).toString() << endl;

    cout << "Віднімання: " << sub(n1, n2).toString() << endl;

    cout << "Множення: " << mul(n1, n2).toString() << endl;

    cout << "Ділення: " << div(n1, n2).toString() << endl;

    cout << "Порівняння: " << (equ(n1, n2) ? "Рівні" : "Не рівні") << endl;

    cout << "Спряжене першого числа: " << conj(n1).toString() << endl;

    return 0;
}