#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class TSoundPlayer {
private:
    static const vector<string> notes;
    static const vector<int> freq;
    static const int t = 1024;

public:
    TSoundPlayer();
    TSoundPlayer(const string& melody, const vector<double>& T);
    ~TSoundPlayer();

    void Play(const string& melody, const vector<double>& T);
    void CreateTrack(const string& melody, const vector<double>& T);
    void PlayTrack(const string& filename);
};