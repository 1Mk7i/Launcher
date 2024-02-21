#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <cctype>
#include <cmath>

using namespace std;

struct MyStruct {
    const int zeroAfterComma = 2;

    // функція піднесення в степінь
    void performExponentiation(vector<double>& numbers, vector<char>& signs, int priority) {
        for (int i = 0; i < signs.size(); i++) {
            if (signs[i] == '^' && priority == 0) {
                numbers[i] = pow(numbers[i], numbers[i + 1]);
                numbers.erase(numbers.begin() + i + 1);
                signs.erase(signs.begin() + i);
                i--;
            }
        }
    }

    // функція ділення, множення, ділення націло
    void performMultiplicationAndDivision(vector<double>& numbers, vector<char>& signs, int priority) {
        for (int i = 0; i < signs.size(); i++) {
            if (signs[i] == '*' && priority == 1) {
                numbers[i] = numbers[i] * numbers[i + 1];
                numbers.erase(numbers.begin() + i + 1);
                signs.erase(signs.begin() + i);
                i--;
            } else if (signs[i] == '/' && priority == 1) {
                if (numbers[i + 1] != 0 && numbers[i] != 0) {
                    numbers[i] = numbers[i] / numbers[i + 1];
                    numbers.erase(numbers.begin() + i + 1);
                    signs.erase(signs.begin() + i);
                    i--;
                } else {
                    cout << "\033[1;31m" << "Error: Не можна ділити на нуль!" << "\033[0m" << endl;
                    return;
                }
            } else if (signs[i] == '%' && numbers[i] != 0 && priority == 1) {
                if (numbers[i + 1] != 0) {
                    numbers[i] = static_cast<int>(numbers[i]) % static_cast<int>(numbers[i + 1]);
                    numbers.erase(numbers.begin() + i + 1);
                    signs.erase(signs.begin() + i);
                    i--;
                } else {
                    cout << "\033[1;31m" << "Error: Не можна ділити на нуль!" << "\033[0m" << endl;
                    return;
                }
            }
        }
    }
    // функція додавання та віднімання
    void performAdditionAndSubtraction(vector<double>& numbers, vector<char>& signs) {
        for (int i = 0; i < signs.size(); i++) {
            if (signs[i] == '+') {
                numbers[i] = numbers[i] + numbers[i + 1];
            } else if (signs[i] == '-') {
                numbers[i] = numbers[i] - numbers[i + 1];
            }
        }
    }
};

class TParcer : public MyStruct{
private:
    string str;
public:    
    TParcer() {
        cout << "Введіть рядок: ";
        cin >> str;
    }

    TParcer(string str) {
        this->str = str;
    }

    bool isValidInput() const {
        for (int i = 0; i < str.length(); i++) {
            if (!isdigit(str[i]) && str[i] != '+' && str[i] != '-' && str[i] != '*' && str[i] != '/' && str[i] != '%' && str[i] != '^' && str[i] != ' ') {
                cout << "\033[1;31m" << "Error: Недопустимий символ '" << str[i] << "'!" << "\033[0m" << endl;
                return false;
            }
        }
        return true;
    }

    void setString(string str) {
        this->str = str;
    }

    string getString() const {
        return str;
    }

    void Display() const {
        cout << "\033[1;34m" << "Вираз: " << getString() << "\033[0m" << endl;
    }

    void parse() {
        vector<int> numbers;
        vector<char> signs;
        string temp = "";
        for (int i = 0; i < str.length(); i++) {
            if (isdigit(str[i])) {
                temp += str[i];
            } else if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' || str[i] == '%' || str[i] == '^') {
                if (!temp.empty()) {
                    numbers.push_back(stoi(temp));
                    temp = "";
                }
                signs.push_back(str[i]);
            } else {
                cout << "\033[1;31m" << "Error: Недопустимий символ '" << str[i] << "'!" << "\033[0m" << endl;
                return;
            }
        }
        if (!temp.empty()) {
            numbers.push_back(stoi(temp));
        }

        // Продовжуємо обробку, якщо є оператори та числа
        if (numbers.size() != signs.size() + 1) {
            cout << "\033[1;31m" << "Error: Невірна кількість операторів або чисел!" << "\033[0m" << endl;
            return;
        }

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
        vector<double> numbers;
        vector<char> signs;
        string temp = "";
        for (int i = 0; i < str.length(); i++) {
            if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' || str[i] == '%' || str[i] == '^') {
                numbers.push_back(stod(temp));
                temp = "";
                signs.push_back(str[i]);
            } else {
                temp += str[i];
            }
        }
        numbers.push_back(stod(temp));
        calculate(numbers, signs);
    }

    void calculate(vector<double>& numbers, vector<char>& signs) {
        performExponentiation(numbers, signs, 0); // 0 - найвищий приорітет виконання
        performMultiplicationAndDivision(numbers, signs, 1);
        performAdditionAndSubtraction(numbers, signs);
        cout << fixed << setprecision(zeroAfterComma) << "\033[1;32m" << "Результат: " <<  "\033[1;33m" << numbers[0] << "\033[0m" << endl;
    }

};

// Гетери та сетери поза класом
void setTParcerString(TParcer& parcer, const string& str) {
    parcer.setString(str);
}

string getTParcerString(const TParcer& parcer) {
    return parcer.getString();
}

int main() {
    vector<string> tasks = {"2+2", "2-2", "2*2", "2/2", "2%2", "2+2*2", "2*2+2", "2+2/2", "2/2+2", "2+2%2", "2%2+2", "2-2*2", "2*2-2", "2-2/2", "2/2-2", "2-2%2", "2%2-2"};

    cout << "\033[1;32m" << "Введіть:" << endl << "1 - для відправки масиву на обробку " << endl << "2 - для ручного вводу" << "\033[0m" << endl;
    int n;
    cin >> n;
    if (n == 1) {
        for (int i = 0; i < tasks.size(); i++) {
            TParcer parcer(tasks[i]);
            if (!parcer.isValidInput()) {
                continue;
            }
            parcer.parse();
            parcer.Display();
            parcer.calculate();
        }
    } else if (n == 2) {
        TParcer parcer;
        if (!parcer.isValidInput()) {
            return 1;
        }
        parcer.parse();
        parcer.Display();
        parcer.calculate();
    } else {
        cout << "\033[1;31m" << "Error: Невірний ввід!" << "\033[0m" << endl;
    }

    return 0;
}
