#include <iostream>
#include <vector>
#include <string>


using namespace std;

class TSoundPlayer {
private:
    static const vector<string> notes;
    static const vector<int> freq;
    static const int t = 1024;

    string melody;
    vector<double> T;

public:
    TSoundPlayer();
    TSoundPlayer(const string& melody, const vector<double>& T);
    ~TSoundPlayer();

    void Play(const string& melody, const vector<double>& T);
    void CreateTrack(const string& melody, const vector<double>& T);
    void PlayTrack(const string& filename);

    void PrintState();
    void PrintCurrentNote();
    void ChangeKey(int shift);
    void FillRandom();
    void ReverseTrack();
    void TrimTrack(size_t position);
};