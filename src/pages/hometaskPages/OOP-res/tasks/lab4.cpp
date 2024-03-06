#include "lab4.h"
#include <fstream>
#include <algorithm>
#define WIN32_LEAN_AND_MEAN
#define RPC_NO_WINDOWS_H
#include <windows.h>

using namespace std;


const vector<string> TSoundPlayer::notes = {"C", "D", "E", "F", "G", "A", "B", "C2", "D2", "E2", "F2", "G2", "A2", "B2"};
const vector<int> TSoundPlayer::freq = {262, 294, 330, 349, 392, 440, 494, 523, 587, 659, 698, 784, 880, 988};

TSoundPlayer::TSoundPlayer() {
    cout << "TSoundPlayer конструктор без параметрів" << endl;
}

TSoundPlayer::TSoundPlayer(const string& melody, const vector<double>& T) {
    cout << "TSoundPlayer конструктор з двома параметрами" << endl;
    Play(melody, T);
}

TSoundPlayer::~TSoundPlayer() {
    cout << "TSoundPlayer деструктор" << endl;
}

void TSoundPlayer::Play(const string& melody, const vector<double>& T) {
    if (!melody.empty()) {
        this->melody = melody;
        this->T = T;

        size_t j = 0; // Змінна для індексування значень з T[]
        for (size_t i = 0; i < melody.length(); i++) {
            // Перевірка на пробіл, якщо так, просто переходимо до наступного символу
            if (melody[i] == ' ')
                continue;

            for (size_t k = 0; k < notes.size(); k++) {
                if (melody[i] == notes[k][0]) {
                    // Перевірка, чи не вийшов індекс j за межі вектора T
                    if (j < T.size()) {
                        double duration = T[j] * t; // Множимо значення на константу t
                        if (i + 1 < melody.length() && melody[i + 1] == '2') {
                            Beep(freq[k + 7], static_cast<int>(duration));
                            i++;
                        } else {
                            Beep(freq[k], static_cast<int>(duration));
                        }
                        j++;
                    }
                    break; // Вихід з циклу, якщо знайдено відповідну ноту
                }
            }
        }
    }
}

void TSoundPlayer::CreateTrack(const string& melody, const vector<double>& T) {
    ofstream file("track.txt");
    if (file.is_open()) {
        file << melody << endl;
        for (size_t i = 0; i < T.size(); i++) {
            file << T[i] << " ";
        }
        file.close();
        cout << "Трек створено та збережено в файлі track.txt" << endl;
    } else {
        cerr << "Не вдалося відкрити файл для запису треку." << endl;
    }
}

void TSoundPlayer::PlayTrack(const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        string melody;
        vector<double> T;
        file >> melody;
        double temp;
        while (file >> temp) {
            T.push_back(temp);
        }
        TSoundPlayer player;
        player.Play(melody, T);
        file.close();
        cout << "Трек відтворено" << endl;
    } else {
        cerr << "Не вдалося відкрити файл для відтворення треку." << endl;
    }
}

void TSoundPlayer::PrintState() {
    cout << "Назва треку: " << melody << endl;
    cout << "Тривалість треку: " << T.size() << " нот" << endl;
    cout << "Тональність: " << melody[0] << endl;
    cout << "Темп відтворення: " << T[0] << endl;
}

void TSoundPlayer::PrintCurrentNote() {
    if (!melody.empty()) {
        size_t j = 0; // Змінна для індексування значень з T[]
        for (size_t i = 0; i < melody.length(); i++) {
            // Перевірка на пробіл, якщо так, просто переходимо до наступного символу
            if (melody[i] == ' ')
                continue;

            for (size_t k = 0; k < notes.size(); k++) {
                if (melody[i] == notes[k][0]) {
                    // Перевірка, чи не вийшов індекс j за межі вектора T
                    if (j < T.size()) {
                        cout << "Поточна нота: " << notes[k] << endl;
                        return;
                    }
                    break; // Вихід з циклу, якщо знайдено відповідну ноту
                }
            }
        }
    }
}

void TSoundPlayer::ChangeKey(int shift) {
    if (!melody.empty()) {
        for (size_t i = 0; i < melody.length(); i++) {
            // Перевірка на пробіл, якщо так, просто переходимо до наступного символу
            if (melody[i] == ' ')
                continue;

            for (size_t k = 0; k < notes.size(); k++) {
                if (melody[i] == notes[k][0]) {
                    int newIndex = (k + shift) % notes.size();
                    melody[i] = notes[newIndex][0];
                    break; // Вихід з циклу, якщо знайдено відповідну ноту
                }
            }
        }
    }
}

void TSoundPlayer::FillRandom() {
    if (!melody.empty()) {
        srand(time(NULL));
        for (size_t i = 0; i < melody.length(); i++) {
            // Перевірка на пробіл, якщо так, просто переходимо до наступного символу
            if (melody[i] == ' ')
                continue;

            int randomIndex = rand() % notes.size();
            melody[i] = notes[randomIndex][0];
        }
    }
}

void TSoundPlayer::ReverseTrack() {
    if (!melody.empty()) {
        reverse(melody.begin(), melody.end());
        reverse(T.begin(), T.end());
    }
}

void TSoundPlayer::TrimTrack(size_t position) {
    if (!melody.empty() && position < T.size()) {
        melody = melody.substr(position);
        T.erase(T.begin(), T.begin() + position);

        cout << "Трек обрізано" << endl;
        Play(melody, T);
    }
}

void Interface(){
    TSoundPlayer player;
    cout << "1. Відтворити мелодію" << endl;
    cout << "2. Додати трек у файл" << endl;
    cout << "3. Відтворити трек" << endl;
    cout << "4. Вивести стан" << endl;
    cout << "5. Вивести поточну ноту" << endl;
    cout << "6. Змінити тон" << endl;
    cout << "7. Заповнити випадковими нотами" << endl;
    cout << "8. Реверс треку" << endl;
    cout << "9. Обрізати трек" << endl;
    cout << "0. Вихід" << endl;

    cout << "Виберіть дію: ";
    int choice;
    string melody;
    cin >> choice;
    melody = "E E E E E E E E E E E E G E E E G E E E E E E A B C2 B A B";
    vector<double> T = {0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 1.0, 0.5, 0.5, 0.5, 0.5, 0.5, 1.0, 0.5, 0.5, 0.5, 1.0, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 1.0, 0.5, 0.5, 0.5, 0.5, 0.5, 1.0, 0.5, 0.5, 0.5, 1.0, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 1.0};
            
    if (choice == 1) {
        TSoundPlayer player(melody, T);
    } else if (choice == 2) {
        player.CreateTrack(melody, T);
    } else if (choice == 3) {
        string filename;
        cout << "Введіть назву файлу: ";
        cin >> filename;
        player.PlayTrack(filename);
    } else if (choice == 4) {
        player.PrintState();
    } else if (choice == 5) {
        player.PrintCurrentNote();
    } else if (choice == 6) {
        int shift;
        cout << "Введіть зсув: ";
        cin >> shift;
        player.ChangeKey(shift);
        player.Play(melody, T);
    } else if (choice == 7) {
        player.FillRandom();
        player.Play(melody, T);
    } else if (choice == 8) {
        player.ReverseTrack();
        player.Play(melody, T);
    } else if (choice == 9) {
        size_t position;
        cout << "Введіть позицію: ";
        cin >> position;
        player.TrimTrack(position);
    } else if (choice == 0) {
        return;

    }
    Interface();
}

int main() {
    Interface();
    return 0;
}