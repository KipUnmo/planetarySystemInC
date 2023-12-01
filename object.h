#ifndef OBJECT_H
#define OBJECT_H
#include "vector.h"

typedef struct{
    double mass;
    Vector position;
    Vector speedVec;
} Object;

Object newObj(double mass, Vector pos, Vector speed) {
    Object o;
    o.mass = mass;
    o.position = pos;
    o.speedVec = speed;
    return o;
}

#endif