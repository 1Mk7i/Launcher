#include "lab3.h"
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
                        }
                        else {
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

int main() {
    string melody = "E E E E E E E E E E E E G E E E G E E E E E E A B C2 B A B";
    vector<double> T = {0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 1.0, 0.5, 0.5, 0.5, 0.5, 0.5, 1.0, 0.5, 0.5, 0.5, 1.0, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 1.0, 0.5, 0.5, 0.5, 0.5, 0.5, 1.0, 0.5, 0.5, 0.5, 1.0, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 1.0};
    TSoundPlayer player(melody, T);
    player.CreateTrack(melody, T);
    player.PlayTrack("track.txt");
    return 0;
}
