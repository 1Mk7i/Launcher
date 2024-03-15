#ifndef POINT_H
#define POINT_H

class Vector;

class Point {
private:
    double cx, cy, cz;

public:
    Point(double x = 0.0, double y = 0.0, double z = 0.0) : cx(x), cy(y), cz(z) {}

    void print();

    void moveByVector(const Vector &v);
};

#endif