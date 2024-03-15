#include <iostream>
#include "Point.h"
#include "Vector.h"

void Point::print() {
    std::cout << "\nPoint(" << cx << " , " << cy << " , " << cz << ")";
}

void Point::moveByVector(const Vector &v) {
    cx += v.cx;
    cy += v.cy;
    cz += v.cz;
}