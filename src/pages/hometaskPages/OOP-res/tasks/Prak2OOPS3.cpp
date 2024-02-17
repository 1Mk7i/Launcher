#include <iostream>
#include <string>
#include <sstream>

using namespace std;

struct MultComplexData {
    float a, b;

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
};

class MultComplex : public MultComplexData{
private:
        MultComplexData data;
    public:
    // Операція додавання
    void add(MultComplex n1, MultComplex n2) {
        MultComplex result;
        result.Init(n1.a + n2.a, n1.b + n2.b);
        cout << result.toString(); 
    }

    // Операція віднімання
    void sub(MultComplex n1, MultComplex n2) {
        MultComplex result;
        result.Init(n1.a - n2.a, n1.b - n2.b);
        cout << result.toString();
    }

    // Операція множення
    void mul(MultComplex n1, MultComplex n2) {
        MultComplex result;
        result.Init(n1.a * n2.a - n1.b * n2.b, n1.a * n2.b + n1.b * n2.a);
        cout << result.toString();
    }

    // Операція ділення
    void div(MultComplex n1, MultComplex n2) {
        MultComplex result;
        result.Init((n1.a * n2.a + n1.b * n2.b) / (n2.a * n2.a + n2.b * n2.b), (n1.b * n2.a - n1.a * n2.b) / (n2.a * n2.a + n2.b * n2.b));
        cout << result.toString();
    }

    // Операція порівняння
    void equ(MultComplex n1, MultComplex n2){
        if (n1.a == n2.a && n1.b == n2.b) {
            cout << "Рівні";
        } else {
            cout << "Не рівні";
        }
    }

    // Операція спряженого числа
    void conj(MultComplex n1) {
        MultComplex result;
        result.Init(n1.a, -n1.b);
        cout << result.toString();
    }
};

int main() {
    MultComplex n1, n2;

    cout << "Введіть перше комплексне число:\n";
    n1.Read();

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
    cout << "Додавання: ";
    n1.add(n1, n2);
    cout << endl;

    cout << "Віднімання: ";
    n1.sub(n1, n2);
    cout << endl;

    cout << "Множення: ";
    n1.mul(n1, n2);
    cout << endl;

    cout << "Ділення: ";
    n1.div(n1, n2);
    cout << endl;

    cout << "Порівняння: ";
    n1.equ(n1, n2);
    cout << endl;

    cout << "Спряжене першого числа: ";
    n1.conj(n1);
    cout << endl;

    return 0;
}
