#include <iostream>
#include <cmath>

using namespace std;

class Rectangle {
    private:
        double x1, y1, x2, y2, x3, y3, x4, y4;
    public:
        Rectangle(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) {
            this->x1 = x1;
            this->y1 = y1;
            this->x2 = x2;
            this->y2 = y2;
            this->x3 = x3;
            this->y3 = y3;
            this->x4 = x4;
            this->y4 = y4;
        }

        // функція для знаходження довжини сторони прямокутника.
        double segment_length() {
            return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
        }

        friend class Rectangle1;
        friend void intersection(Rectangle& r);
};

//функція для знаходження координати перетину діагоналей прямокутника.
void intersection(Rectangle& r) {
    double x, y;
    x = (r.x1 + r.x3) / 2;
    y = (r.y1 + r.y3) / 2;
    cout << "Intersection: (" << x << ", " << y << ")" << endl;
}

class Rectangle1 {
    public:
        double perimeter(Rectangle& r) {
            return 2 * (sqrt(pow(r.x2 - r.x1, 2) + pow(r.y2 - r.y1, 2)) + sqrt(pow(r.x3 - r.x2, 2) + pow(r.y3 - r.y2, 2))); 
        }
        double area(Rectangle& r){
            return sqrt(pow(r.x2 - r.x1, 2) + pow(r.y2 - r.y1, 2)) * sqrt(pow(r.x3 - r.x2, 2) + pow(r.y3 - r.y2, 2)); 
        }
};

int main() {
    Rectangle r(0, 0, 0, 2, 3, 2, 3, 0);
    cout << "Length: " << r.segment_length() << endl;

    Rectangle1 r1;
    cout << "Perimeter: " << r1.perimeter(r) << endl;
    cout << "Area: " << r1.area(r) << endl;

    intersection(r);
    return 0;
}