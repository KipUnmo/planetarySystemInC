#ifndef VECTOR_H
#define VECTOR_H
#include <math.h>

typedef struct {
    double x;
    double y;
    double length;
} Vector;

Vector newVector(double x, double y) {
    Vector v;
    v.x = x;
    v.y = y;
    v.length = sqrt(v.x * v.x + v.y * v.y);
    return v;
}

Vector newEmptyVector() {
    Vector v;
    v.x = 0;
    v.y = 0;
    v.length = 0;
    return v;
}

Vector addVector(Vector v1, Vector v2) {
    v1.x += v2.x;
    v1.y += v2.y;
    v1.length = sqrt(v1.x * v1.x + v1.y *v1.y);
    return v1;
}

Vector subtractVector(Vector v1, Vector v2) {
    v1.x -= v2.x;
    v1.y -= v2.y;
    v1.length = sqrt(v1.x * v1.x + v1.y *v1.y);
    return v1;
}

double vectorLength(Vector v1) {
    return v1.length;
}

void normalize(Vector *v) {
    if (v->length != 0) {
        v->x /= v->length;
        v->y /= v->length;
    }
}

Vector setDirection(Vector v1, Vector targetRotationVec) {
    if (v1.length != 0) {
        double lenghtFactor = v1.length / targetRotationVec.length;
        double newX = targetRotationVec.x * lenghtFactor;
        double newY = targetRotationVec.y * lenghtFactor;

        Vector v;
        v.x = newX;
        v.y = newY;
        v.length = sqrt(v.x * v.x + v.y *v.y);

        return v;
    }
}



#endif