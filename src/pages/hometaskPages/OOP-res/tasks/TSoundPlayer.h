#pragma once
#include <iostream>
#include <string>

class TSoundPlayer {
private:
    static const std::string notes[14];
    static const int freq[14];

public:
    TSoundPlayer();
    TSoundPlayer(int *T);
    TSoundPlayer(const std::string& melody, int *T);
    ~TSoundPlayer();

    void Play(const std::string& melody, int *T);
};