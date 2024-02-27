#include "TSoundPlayer.h"
#include <iostream>
#include <windows.h>

using namespace std;

const std::string TSoundPlayer::notes[14] = {"C", "D", "E", "F", "G", "A", "B", "C2", "D2", "E2", "F2", "G2", "A2", "B2"};
const int TSoundPlayer::freq[14] = {262, 294, 330, 349, 392, 440, 494, 523, 587, 659, 698, 784, 880, 988};

TSoundPlayer::TSoundPlayer() {
    std::cout << "TSoundPlayer конструктор без параметрів" << std::endl;
}

TSoundPlayer::TSoundPlayer(int *T) {
    std::cout << "TSoundPlayer конструктор з одним параметром" << std::endl;
    Play("C2", T);
}

TSoundPlayer::TSoundPlayer(const std::string& melody, int *T) {
    std::cout << "TSoundPlayer конструктор з двома параметрами" << std::endl;
    Play(melody, T);
}

TSoundPlayer::~TSoundPlayer() {
    std::cout << "TSoundPlayer деструктор" << std::endl;
}

void TSoundPlayer::Play(const std::string& melody, int *T) {
    if (!melody.empty() && T != nullptr) {
        int j = 0; // Змінна для індексування значень з T[]
        for (size_t i = 0; i < melody.length(); i++) {
            // Перевірка на пробіл, якщо так, просто переходимо до наступного символу
            if (melody[i] == ' ') 
                continue;

            for (size_t k = 0; k < 14; k++) {
                if (melody[i] == notes[k][0]) {
                    if (i + 1 < melody.length() && melody[i + 1] == '2') {
                        Beep(freq[k + 7], T[j]);
                        i++;
                    }
                    else {
                        Beep(freq[k], T[j]);
                    }
                    j++;
                    break; // Вихід з циклу, якщо знайдено відповідну ноту
                }
            }
        }
    }
}


int main() {
    int D[] = {500};
    TSoundPlayer play(D);
    TSoundPlayer player;
    string melody = "E E E E E E E E E E E E G E E E G E E E E E E A B C2 B A B";
    int T[] = {500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 600, 500, 500, 500, 500, 500, 500, 600, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 800, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 800, 500, 500, 500, 500};
    player.Play(melody, T);
    string melody2 = "C2 E E E B E E E B E E E A E E E2 E C2 E E E B E E E B E E E A E2 C2";
    int T2[] = {500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 400, 500, 500, 400, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500};
    player.Play(melody2, T2);
    string melody3 = "B A B C2 E E E C2 E E E C2 E E E B E2 C2 B A B C2 E E E C2 E E E";
    int T3[] = {500, 500, 500, 450, 500, 500, 500, 450, 500, 500, 500, 500, 500, 500, 500, 500, 500, 450, 500, 500, 500, 450, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 450, 500, 500, 500, 450};
    player.Play(melody3, T3);
    string melody4 = "E2 E E E A B C2 B A C2 B A G A B G B A G A B G A C2 B D2 C2 A B G A C2 B D2 C2 D2 B A G B";
    int T4[] = {450, 500, 500, 500, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400};
    player.Play(melody4, T4);
    string melody5 = "B A G A B G B A G E2 B G A B C2 B A C2 B A G A B G B A G E2 B G A C2 B D2 C2 A B G A C2 B D2";
    int T5[] = {400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400, 400};
    player.Play(melody5, T5);
    return 0;
}
