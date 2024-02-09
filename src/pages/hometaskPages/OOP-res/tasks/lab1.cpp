#include <iostream>

using namespace std;

struct Angle {
    int degrees;
    int minutes;

    void entered() {
        cout << "Enter degrees: " << endl;
        cin >> degrees;
        cout << "Enter minutes: " << endl;
        cin >> minutes;
    }

    void print(const Angle& inf) {
        cout << inf.degrees << "°" << inf.minutes << "'" << endl;
    }

    void summAngles(const Angle& angle1, const Angle& angle2) {
        int summDegrees = angle1.degrees + angle2.degrees;
        int summMinutes = angle1.minutes + angle2.minutes;
        if (summMinutes >= 60) {
            summDegrees++;
            summMinutes -= 60;
        }
        cout << "Summ of angles: " << summDegrees << "°" << summMinutes << "'" << endl;
    }
};

struct journal{
    string nameJournal;
    int readerId;
    string readerName;
    
    void entered(int number) {
        journal Array[number];
        for (int i = 0; i < number; ++i){
            cout << "Enter the information about the journal: " << endl;
            cout << "Format: ";
            cout << "Name of the journal |" << "Reader's id |" << "Reader's name |" << endl;
            cin >> Array[i].nameJournal >> Array[i].readerId >> Array[i].readerName;
        }

        for (int i = 0; i < number; ++i){
            cout << "Journals name: " <<Array[i].nameJournal << endl << "ReaderID: " << Array[i].readerId << endl << "ReaderName: " << Array[i].readerName << endl;
        }

        cout << "Search the journal: " << endl;
        cout << "Enter the name of the journal: " << endl;
        string name;
        cin >> name;
        for (int i = 0; i < number; ++i){
            if (name == Array[i].nameJournal){
                cout << "Journal's name: " << Array[i].nameJournal << " ReaderID: " << Array[i].readerId << " ReaderName: " << Array[i].readerName << endl;
            }
        }

        cout << "Enter the ReadersID: " << endl;
        int id;
        cin >> id;
        for (int i = 0; i < number; ++i){
            if (id == Array[i].readerId){
                cout << "Number of issues: " << i << endl;
            }
        }

        cout << "Enter the reader's name: " << endl;
        string reader;
        cin >> reader;
        if (reader == Array[0].readerName){
            cout << "Yes, he is a reader" << endl;
            for (int i = 0; i < number; ++i){
                if (reader == Array[i].readerName){
                    cout << "Journal's name: " << Array[i].nameJournal << endl;
                }
            }
        }else{
            cout << "No, he is not a reader" << endl;
        }
    }
};



int main(){
    cout << "Enter the number of tasks: " << endl;

    int task;
    int number;
    cin >> task;

    if (task == 1){
        cout << "Enter the number of degrees and minutes (d m): " << endl;
        cin >> number;
        for (int i = 0; i < number; ++i){
            Angle angle1;
            Angle angle2;
            angle1.entered();
            angle1.print(angle1);
            angle2.entered();
            angle2.print(angle2);
            angle1.summAngles(angle1, angle2);
        } 
    }else if (task == 2){

        cout << "Enter the numbers of journals: " << endl;
        cin >> number;
        journal j;
        j.entered(number);
    }

    return 0;
}