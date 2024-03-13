#include "Point.h"
#include <iostream>

using namespace std;

Point::Point(double x, double y, double z) : cx(x), cy(y), cz(z) {}

void Point::print() {
    cout << "\nPoint(" << cx << " , " << cy << " , " << cz << ")";
}

void Point::moveByVector(const Vector &v) {
    cx += v.cx;
    cy += v.cy;
    cz += v.cz;
}
