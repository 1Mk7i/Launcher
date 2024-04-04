#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <limits>

using namespace std;

class Currency {
    private:
        double value;
        string type;
        vector<vector<double>> currencyRates;
    public:

        Currency() {
            this->value = 0;
            this->type = "UAH";
            this->currencyRates = {
                {1, 27.5, 0.85, 0.75},
                {0.036, 1, 0.85, 0.75},
                {1.18, 1.18, 1, 0.89},
                {1.33, 1.33, 1.12, 1}
            };
        }

        Currency(double value, string type, vector<vector<double>> currencyRates) {
            this->value = value;
            this->type = type;
            this->currencyRates = currencyRates;
        }
        ~Currency() {
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

        friend ostream& operator<<(ostream& os, const Currency& c);
        friend istream& operator>>(istream& input, Currency& currency);

        friend Currency operator++(Currency& currency, int);
        friend Currency operator--(Currency& currency, int);

        // перевантаження префіксної інкрементації ++
        Currency operator++() {
            this->value++;
            return *this;
        }

        // перевантаження оператора не !
        bool operator!() {
            return this->value == 0;
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

// лабораторна 9

// перевантаження операторів виведення та введення
ostream& operator<<(ostream& os, const Currency& c) {
    os << c.value << " " << c.type;
    return os;
}
istream& operator>>(istream& input, Currency& currency) {
    cout << "Введіть значення: ";
    while (!(input >> currency.value)) {
        cout << "Неправильне значення. Будь ласка, введіть числове значення: ";
        input.clear();
        input.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Введіть тип: ";
    while (!(input >> currency.type)) {
        cout << "Неправильне значення. Будь ласка, введіть коректний тип: ";
        input.clear();
        input.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    return input;
}

// перевантаження постфіксоної інкрементації ++
Currency operator++(Currency& currency, int) {
    Currency temp = currency;
    currency.value++;
    return temp;
}
// перевантаження постфіксоної інкрементації --
Currency operator--(Currency& currency, int) {
    Currency temp = currency;
    currency.value--;
    return temp;
}

int main(){
    // 1 UAH = 1 UAH
    // 1 USD = 1 USD
    // 1 EUR = 1 EUR
    // 1 USD = 27.5 UAH
    // 1 USD = 0.85 EUR
    // 1 USD = 0.75 GBP
    vector<vector<double>> currencyRates = {
        {1, 27.5, 0.85, 0.75},
        {0.036, 1, 0.85, 0.75},
        {1.18, 1.18, 1, 0.89},
        {1.33, 1.33, 1.12, 1}
    };
    double value;
    string type;
    cout << "currency1" << endl;
    cout << "Введіть значення: ";
    cin >> value;
    cout << "Введіть тип: ";
    cin >> type;
    Currency currency1 = Currency(value, type, currencyRates);
    if (!currency1) {
        cout << "Значення валюти дорівнює 0" << endl;
        return 0;
    }
    Currency currency2 = Currency(100, "UAH", currencyRates);
    // Currency currency3 = Currency(100, "EUR", currencyRates);
    // Currency currency4 = Currency(100, "GBP", currencyRates);
    // виведення значення валюти та типу через перевантажений оператор <<
    cout << currency1 << endl;
    cout << currency2 << endl;
    // cout << currency3 << endl;
    // cout << currency4 << endl;


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

    cout << "Введіть кількість об'єктів: ";
    int n;
    cin >> n;
    vector<Currency> currencies;
    for (int i = 0; i < n; i++) {
        Currency currency;
        cin >> currency;
        currencies.push_back(currency);
    }
    for (int i = 0; i < n; i++) {
        currencies[i].print();
    }
    
    cout << "Виберіть операцію: " << endl;
    cout << "1. Додавання" << endl;
    cout << "2. Віднімання" << endl;
    cout << "3. Порівняння" << endl;
    cout << "4. Ділення націло" << endl;
    cout << "5. Присвоєння" << endl;
    cout << "6. Постфіксна інкрементація ++" << endl;
    cout << "7. Префіксна інкрементація ++" << endl;
    cout << "8. Постфіксна інкрементація --" << endl;
    int operation;
    cin >> operation;
    if (operation == 1) {
        Currency currency1 = currencies[0];
        Currency currency2 = currencies[1];
        Currency currency3 = currency1 + currency2;
        currency3.print();
    } else if (operation == 2) {
        Currency currency1 = currencies[0];
        Currency currency2 = currencies[1];
        currency1 -= currency2;
        currency1.print();
    } else if (operation == 3) {
        Currency currency1 = currencies[0];
        Currency currency2 = currencies[1];
        if (currency1 == currency2) {
            cout << "True" << endl;
        } else {
            cout << "False" << endl;
        }
    } else if (operation == 4) {
        Currency currency1 = currencies[0];
        Currency currency2 = currencies[1];
        Currency currency3 = currency1 % currency2;
        currency3.print();
    } else if (operation == 5) {
        Currency currency1 = currencies[0];
        Currency currency2 = currencies[1];
        currency1 = currency2;
        currency1.print();
    } else if (operation == 6) {
        Currency currency1 = currencies[0];
        currency1.print();
        cout << "Скільки разів ви хочете збільшити значення на 1: ";
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            currency1++;
        }
        currency1.print();
    } else if (operation == 7) {
        Currency currency1 = currencies[0];
        currency1.print();
        cout << "Скільки разів ви хочете збільшити значення на 1: ";
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            ++currency1;
        }
        currency1.print();
    } else if (operation == 8) {
        Currency currency1 = currencies[0];
        currency1.print();
        cout << "Скільки разів ви хочете зменшити значення на 1: ";
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            currency1--;
        }
        currency1.print();
    }

    return 0;
}