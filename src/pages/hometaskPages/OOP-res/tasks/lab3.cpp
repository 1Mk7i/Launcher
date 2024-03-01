#include <iostream>
#include <fstream>
#include <vector>
#include <windows.h>

class TSoundPlayer {
private:
    static const std::vector<std::string> notes;
    static const std::vector<int> freq;
    static const int t = 1000;

public:
    TSoundPlayer();
    TSoundPlayer(const std::string& melody, const std::vector<double>& T);
    ~TSoundPlayer();

    void Play(const std::string& melody, const std::vector<double>& T);
    void CreateTrack(const std::string& melody, const std::vector<double>& T);
    void PlayTrack(const std::string& filename);
};

const std::vector<std::string> TSoundPlayer::notes = {"C", "D", "E", "F", "G", "A", "B", "C2", "D2", "E2", "F2", "G2", "A2", "B2"};
const std::vector<int> TSoundPlayer::freq = {262, 294, 330, 349, 392, 440, 494, 523, 587, 659, 698, 784, 880, 988};

TSoundPlayer::TSoundPlayer() {
    std::cout << "TSoundPlayer конструктор без параметрів" << std::endl;
}

TSoundPlayer::TSoundPlayer(const std::string& melody, const std::vector<double>& T) {
    std::cout << "TSoundPlayer конструктор з двома параметрами" << std::endl;
    Play(melody, T);
}

TSoundPlayer::~TSoundPlayer() {
    std::cout << "TSoundPlayer деструктор" << std::endl;
}

void TSoundPlayer::Play(const std::string& melody, const std::vector<double>& T) {
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


void TSoundPlayer::CreateTrack(const std::string& melody, const std::vector<double>& T) {
    std::ofstream file("track.txt");
    if (file.is_open()) {
        file << melody << std::endl;
        for (size_t i = 0; i < T.size(); i++) {
            file << T[i] << " ";
        }
        file.close();
        std::cout << "Трек створено та збережено в файлі track.txt" << std::endl;
    } else {
        std::cerr << "Не вдалося відкрити файл для запису треку." << std::endl;
    }
}

void TSoundPlayer::PlayTrack(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string melody;
        std::vector<double> T;
        file >> melody;
        double temp;
        while (file >> temp) {
            T.push_back(temp);
        }
        TSoundPlayer player;
        player.Play(melody, T);
        file.close();
        std::cout << "Трек відтворено" << std::endl;
    } else {
        std::cerr << "Не вдалося відкрити файл для відтворення треку." << std::endl;
    }
}

int main() {
    std::string melody = "E E E E E E E E E E E E G E E E G E E E E E E A B C2 B A B";
    std::vector<double> T = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1.5, 1, 1, 1, 1, 1, 1, 1.5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1.6, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1.6, 1, 1, 1, 1};
    TSoundPlayer player(melody, T);
    player.CreateTrack(melody, T);
    player.PlayTrack("track.txt");
    return 0;
}
