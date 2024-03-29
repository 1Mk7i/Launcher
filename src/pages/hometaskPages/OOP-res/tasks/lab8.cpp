// 1. Розробити і реалізувати програмно клас, згідно варіанту. 
// 2. Реалізувати перевантаження зазначених операцій. Перевантажте (на вибір) по дві операції як звичайні функції, як функції, що належать класу, та як дружні функції.
//  3. Продемонструвати роботу створеного класу та його функцій в основній частині програми. 
// . Скласти опис класу комплексне число і реалізувати його програмно. Дані класу повинні бути в закритій частині.
// 2. Клас має містити конструктор і деструктор, а також усі функції-оператори, необхідні для реалізації класу. 
// 3. Надати користувачу можливість введення даних у вигляді текстового рядка, наприклад для комплексних чисел - у форматі “-3+7і”, для дробів - “2/3”. 
// 4. Реалізувати виведення інформації про об’єкт класу в стандартизованому вигляді, наприклад для часу - 14:23:05, для многочлена - 4x^3+x+1.
// 5. Реалізувати дружні функції, що перевантажують визначені операції.
// 6. Реалізувати зовнішні функції, що перевантажують певні операції.
// 7. Реалізувати методи класу, що перевантажують окремі операції.
// 6. В головній програмі перевірити всі основні функції, створені у програмі. 
// 7. Продемонструвати роботу створеної програми. 

// Клас Сurrency (гроші) - зазначається величина та тип, а також - двомірний масив з курсами валют
// Операції: +,  %,  >.  ==,  =,  -=
// для того щоб додати наприклад гривні до доларів, потрібно перетворити гривні в долари за курсом, а потім додати їх
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class Currency {
    private:
        double value;
        string type;
        vector<vector<double>> currencyRates;
    public:
        Currency(double value, string type, vector<vector<double>> currencyRates) {
            this->value = value;
            this->type = type;
            this->currencyRates = currencyRates;
        }
        ~Currency() {
            cout << "Currency object was deleted" << endl;
        }
        // конвертор валют :)
        double convertTo(string type) {
            int index1 = 0;
            int index2 = 0;
            if (this->type == "UAH") {
                index1 = 0;
            } else if (this->type == "USD") {
                index1 = 1;
            } else if (this->type == "EUR") {
                index1 = 2;
            } else if (this->type == "GBP") {
                index1 = 3;
            }
            if (type == "UAH") {
                index2 = 0;
            } else if (type == "USD") {
                index2 = 1;
            } else if (type == "EUR") {
                index2 = 2;
            } else if (type == "GBP") {
                index2 = 3;
            }
            return this->value * this->currencyRates[index1][index2];
        }
        // оператор віднімання
        Currency operator-=(Currency currency) {
            this->value -= currency.convertTo(this->type);
            return *this;
        }
        // оператор присвоєння
        Currency operator=(Currency currency) {
            this->value = currency.convertTo(this->type);
            return *this;
        }
        void print() {
            cout << this->value << " " << this->type << endl;
        }

        friend Currency operator+(Currency currency1, Currency currency2);
        friend Currency operator%(Currency currency1, Currency currency2);

        double getValue() {
            return value;
        }
        string getType() {
            return type;
        }
};
// дружня функція для додавання
Currency operator+(Currency currency1, Currency currency2) {
    double newValue = currency1.convertTo(currency2.type) + currency2.value;
    return Currency(newValue, currency2.type, currency2.currencyRates);
}
// дружня функція для ділення націло
Currency operator%(Currency currency1, Currency currency2) {
    double newValue = currency1.value / currency2.convertTo(currency1.type);
    return Currency(newValue, currency1.type, currency1.currencyRates);
}
// зовнішня функція для порівняння
bool operator==(Currency currency1, Currency currency2) {
    return currency1.getValue() == currency2.convertTo(currency1.getType());
}
// зовнішня функція для порівняння (більше)
bool operator>(Currency currency1, Currency currency2) {
    return currency1.getValue() > currency2.convertTo(currency1.getType());
}

int main(){
    // 1 USD = 27.5 UAH
    // 1 USD = 0.85 EUR
    // 1 USD = 0.75 GBP
    vector<vector<double>> currencyRates = {{27.5, 0.85, 0.75}, {1/27.5, 1/0.85, 1/0.75}};
    Currency currency1 = Currency(100, "USD", currencyRates);
    Currency currency2 = Currency(100, "UAH", currencyRates);
    Currency currency3 = Currency(100, "EUR", currencyRates);
    Currency currency4 = Currency(100, "GBP", currencyRates);
    currency1.print();
    currency2.print();
    currency3.print();
    currency4.print();
    cout << "currency1 + currency2" << endl;
    Currency currency5 = currency1 + currency2;
    currency5.print();
    cout << "currency1 % currency2" << endl;
    Currency currency6 = currency1 % currency2;
    currency6.print();
    cout << "currency1 > currency2" << endl;
    if (currency1 > currency2) {
        cout << "True" << endl;
    } else {
        cout << "False" << endl;
    }
    cout << "currency1 == currency2" << endl;
    if (currency1 == currency2) {
        cout << "True" << endl;
    } else {
        cout << "False" << endl;
    }
    cout << "currency1 = currency2" << endl;
    currency1 = currency2;
    currency1.print();
    cout << "currency1 -= currency2" << endl;
    currency1 -= currency2;
    currency1.print();
    return 0;
}