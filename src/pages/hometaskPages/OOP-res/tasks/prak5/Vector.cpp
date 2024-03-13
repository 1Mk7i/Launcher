#include "Vector.h"
#include "Point.h"
#include <iostream>

using namespace std;

Vector::Vector(double x, double y, double z) : cx(x), cy(y), cz(z) {}

void Vector::print() {
    cout << "\nVector(" << cx << " , " << cy << " , " << cz << ")";
}
