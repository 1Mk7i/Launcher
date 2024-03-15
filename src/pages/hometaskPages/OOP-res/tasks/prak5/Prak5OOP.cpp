#include "Point.h"
#include "Vector.h"
#include <iostream>

using namespace std;

void moveByVector(Point &p, const Vector &v) {
    p.cx += v.cx;
    p.cy += v.cy;
    p.cz += v.cz;
}

int main() {
    cout << "Program start\n";
    Point p(7.0, 8.0, 9.0);
    Vector v(1.0, 2.0, 3.0);
    p.print();
    moveByVector(p,Vector(1.0, 2.0, 3.0));
    p.print();
    p.moveByVector(Vector(1.0, 2.0, 3.0));
    p.print();
    cout << "\nProgram end\n";
    return 0;
}
