#include <iostream>
#include <cmath>

using namespace std;

struct Point {
    float x, y;
};

struct Shape {
    string name = "Triangle";
    int points;
    Point p1,p2,p3;

    void print(){
        cout << "\033[1;32mEnter 3 points of triangle: \033[0m" << endl;
        cout << "\033[1;34mEnter point 1 : \033[1;33m" << endl;
        cin >> p1.x >> p1.y;
        cout << "\033[1;34mEnter point 2 : \033[1;33m" << endl;
        cin >> p2.x >> p2.y;
        cout << "\033[1;34mEnter point 3 : \033[1;33m" << endl;
        cin >> p3.x >> p3.y;
            
        cout << "\033[1;32mShape: \033[1;33m" << name << "\033[0m" << endl;
        
        // периметр
        float perimetr = sqrt(pow((p2.x - p1.x), 2) + pow((p2.y - p1.y), 2)) + sqrt(pow((p3.x - p2.x), 2) + pow((p3.y - p2.y), 2)) + sqrt(pow((p3.x - p1.x), 2) + pow((p3.y - p1.y), 2));
        cout << "\033[1;34mP: \033[1;33m" << perimetr << endl;
        // площа
        float S = 0.5 * abs((p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y));
        cout << "\033[1;34mS: \033[1;33m" << S << "\033[0m" << endl;
        // радіус вписаного кола
        float r = S / (perimetr / 2);
        cout << "\033[1;34mr: \033[1;33m" << r << "\033[0m" << endl;
        // радіус описаного кола
        float R = (sqrt(pow((p2.x - p1.x), 2) + pow((p2.y - p1.y), 2)) * sqrt(pow((p3.x - p2.x), 2) + pow((p3.y - p2.y), 2)) * sqrt(pow((p3.x - p1.x), 2) + pow((p3.y - p1.y), 2))) / (4 * S);
        cout << "\033[1;34mR: \033[1;33m" << R << "\033[0m" << endl;
    }
};

int main() {
    Shape triangle;
    triangle.print();
    return 0;
}