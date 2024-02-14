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
        cout << "Enter 3 points of triangle: " << endl;
        cout << "Enter point 1 : " << endl;
        cin >> p1.x >> p1.y;
        cout << "Enter point 2 : " << endl;
        cin >> p2.x >> p2.y;
        cout << "Enter point 3 : " << endl;
        cin >> p3.x >> p3.y;
            
        cout << "Shape: " << name << endl;
        for (int i = 0; i < points; ++i) {
        }
        
        // периметр
        float perimetr = sqrt(pow((p2.x - p1.x), 2) + pow((p2.y - p1.y), 2)) + sqrt(pow((p3.x - p2.x), 2) + pow((p3.y - p2.y), 2)) + sqrt(pow((p3.x - p1.x), 2) + pow((p3.y - p1.y), 2));
        cout << "P: " << perimetr << endl;
        // площа
        float S = 0.5 * abs((p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y));
        cout << "S: " << S << endl;
        // радіус вписаного кола
        float r = S / (perimetr / 2);
        cout << "r: " << r << endl;
        // радіус описаного кола
        float R = (sqrt(pow((p2.x - p1.x), 2) + pow((p2.y - p1.y), 2)) * sqrt(pow((p3.x - p2.x), 2) + pow((p3.y - p2.y), 2)) * sqrt(pow((p3.x - p1.x), 2) + pow((p3.y - p1.y), 2))) / (4 * S);
        cout << "R: " << R << endl;
    }
};

int main() {
    Shape triangle;
    triangle.print();
    return 0;
}