#include "Point.h"
#include "Vector.h"
#include <iostream>

using namespace std;

int main() {
    cout << "Program start\n";
    Point p(7.0, 8.0, 9.0);
    p.print();
    p.moveByVector(Vector(5.0, 5.0, -4.0));
    p.print();
    cout << "\nProgram end\n";
    return 0;
}
