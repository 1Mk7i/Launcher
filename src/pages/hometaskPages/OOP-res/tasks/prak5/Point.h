#ifndef POINT_H
#define POINT_H

#include "Vector.h"

class Point {
private:
    double cx, cy, cz;

public:
    Point(double x = 0.0, double y = 0.0, double z = 0.0) : cx(x), cy(y), cz(z) {}

    void print();

    friend void moveByVector(Point &p, const Vector &v);

    void moveByVector(const Vector& v) {
        cx += v.cx;
        cy += v.cy;
        cz += v.cz;
    }
};

#endif