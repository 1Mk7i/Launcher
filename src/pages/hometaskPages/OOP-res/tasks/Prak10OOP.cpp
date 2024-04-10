#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Task 1
class String {
private:
    string str;
public:
    String(string str) { this->str = str; }
    string operator()(int index, int length) { return str.substr(index, length); }
};

// Task 2
class Letter {
private:
    char letter;
    int count;
public:
    Letter(char letter, int count) : letter(letter), count(count) {}
    char getLetter() { return letter; }
    void increaseCount() { count++; }
    int getCount() { return count; }
};

class LetterMap {
private:
    vector<Letter> l_map;
public:
    LetterMap(){};
    Letter& operator[](char letter) {
        for (Letter &l : l_map) {
            if (l.getLetter() == letter) {
                return l;
            }
        }
        l_map.push_back(Letter(letter, 0));
        return l_map.back();
    }
    void print() {
        for (Letter l : l_map) {
            cout << l.getLetter() << " - " << l.getCount() << endl;
        }
    }
};

int main() {
    cout << "Task 1: " << endl;
    String str("Hello, World!");
    cout << str(7, 5) << endl;

    cout << "Task 2: " << endl;
    LetterMap l_map;
    string s = "Hello, World!";
    for (char c : s) {
        if (isalpha(c)) {
            l_map[c].increaseCount();
        }
    }
    l_map.print();
    // вивід вибраної літери та її кількості входжень
    cout << "Enter a letter: ";
    char letter;
    cin >> letter;
    cout << "Count of letter " << letter << " is " << l_map[letter].getCount() << endl;

    return 0;
}