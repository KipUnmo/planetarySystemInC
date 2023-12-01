#ifndef GRAVMATH_H
#define GRAVMATH_H
#include "vector.h"
#include "object.h"

const double gConstant = 6.67e-11;

void getFres(Object *objArr, Vector *fresArr, int size ) {
    if (size > 1) {
        for (int i = 0; i < size; i++){
            fresArr[i] = newEmptyVector();
            //double force = 0;
            for (int j = 0; j < size; j++){
                if (j != i){
                    Vector pointVec = subtractVector(objArr[j].position, objArr[i].position);
                    double force = (gConstant * (objArr[i].mass * objArr[j].mass)) / (pointVec.length * pointVec.length);

                    fresArr[i] = addVector(fresArr[i], setDirection(newVector(force, 0), pointVec));
                }
            }
        }
    }
}

void updatePos(Object *obj, Vector *fres) {
    double accX = fres->x / obj->mass;
    double accY = fres->y / obj->mass;

    obj->speedVec.x += accX;
    obj->speedVec.y += accY;

    obj->position.x += obj->speedVec.x;
    obj->position.y += obj->speedVec.y;
}

#endif