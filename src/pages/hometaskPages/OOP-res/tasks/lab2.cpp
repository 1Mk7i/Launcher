#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

using namespace std;

struct MyStruct {
    const int zeroAfterComma = 2;
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
            if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' || str[i] == '%') {
                numbers.push_back(stoi(temp));
                temp = "";
                signs.push_back(str[i]);
            } else {
                temp += str[i];
            }
        }
        numbers.push_back(stoi(temp));
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
            if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' || str[i] == '%') {
                numbers.push_back(stoi(temp));
                temp = "";
                signs.push_back(str[i]);
            } else {
                temp += str[i];
            }
        }
        numbers.push_back(stoi(temp));
        for (int i = 0; i < signs.size(); i++) {
            if (signs[i] == '*') {
                numbers[i] = numbers[i] * numbers[i + 1];
                numbers.erase(numbers.begin() + i + 1);
                signs.erase(signs.begin() + i);
                i--;
            } else if (signs[i] == '/') {
                if (numbers[i + 1] != 0 && numbers[i] != 0) {
                    numbers[i] = numbers[i] / numbers[i + 1];
                    numbers.erase(numbers.begin() + i + 1);
                    signs.erase(signs.begin() + i);
                    i--;
                } else {
                    cout << "Error: Не можна ділити на нуль!" << endl;
                    return;
                }
            } else if (signs[i] == '%' && numbers[i] != 0) {
                if (numbers[i + 1] != 0) {
                    numbers[i] = static_cast<int>(numbers[i]) % static_cast<int>(numbers[i + 1]);
                    numbers.erase(numbers.begin() + i + 1);
                    signs.erase(signs.begin() + i);
                    i--;
                } else {
                    cout << "Error: Не можна ділити на нуль!" << endl;
                    return;
                }
            }
        }
        for (int i = 0; i < signs.size(); i++) {
            if (signs[i] == '+') {
                numbers[i] = numbers[i] + numbers[i + 1];
            } else if (signs[i] == '-') {
                numbers[i] = numbers[i] - numbers[i + 1];
            }
        }
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
            TParcer parcer;
            parcer.setString(tasks[i]);
            parcer.parse();
            parcer.Display();
            parcer.calculate();
        }
    } else if (n == 2) {
        TParcer parcer;
        parcer.parse();
        parcer.Display();
        parcer.calculate();
    } else {
        cout << "Error: Невірний ввід!" << endl;
    }

    return 0;
}
