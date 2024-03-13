#ifndef VECTOR_H
#define VECTOR_H

#include "Point.h"

class Vector {
private:
    double cx, cy, cz;

public:
    Vector(double x = 0.0, double y = 0.0, double z = 0.0);

    void print();

    friend class Point;
};

#endif
