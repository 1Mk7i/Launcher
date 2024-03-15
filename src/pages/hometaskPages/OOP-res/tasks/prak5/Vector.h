#ifndef VECTOR_H
#define VECTOR_H

class Point;

class Vector {
private:
    double cx, cy, cz;

public:
    Vector(double x = 0.0, double y = 0.0, double z = 0.0) : cx(x), cy(y), cz(z) {}

    void print();
    friend void moveByVector(Point &p, const Vector &v);

    friend class Point;
    
};

#endif