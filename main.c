#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "vector.h"
#include "object.h"
#include "gravMath.h"
#include "time.h"

#define GRIDSIZE 40
#define SECONDS_PER_PRINT 10000

char** gridInit(int size) {
    char** grid = (char**)malloc(size * sizeof(char*));
    for (int i = 0; i < size; i++){
        grid[i] = (char*)malloc(size * sizeof(char));
        for (int j = 0; j < size; j++){
            grid[i][j] = '.';
        } 
    }
    return grid;
}

void setGrid(char** grid, char character, double xPos, double yPos, Vector mpu, Vector centre) {
    double factor;
    if (mpu.x >= mpu.y) {
        factor = mpu.x * 1.6 / 1;
    }
    else {
        factor = mpu.y * 1.6 / 1;
    }
    int x = xPos / factor;
    int y = yPos / factor;

    centre.x /= (mpu.x + 1);
    centre.y /= (mpu.y + 1);

    x += centre.x;
    y += centre.y;
    if (x >= 0 && x < GRIDSIZE && y >= 0 && y < GRIDSIZE)
    {
        grid[x][y+10] = character; 
    }
}

void printGrid(char** grid) {
    for (int i = GRIDSIZE -1; i >= 0; i--){
        for (int j = 0; j < GRIDSIZE; j++){
            printf("%c ", grid[j][i]);
        }
        printf("\n");
    }
}


void freeGrid(char** grid) {
    for (int i = 0; i < GRIDSIZE; i++){
        free(grid[i]);
    }
    free(grid);
}

Vector getScale(Object objects[], int size, Vector *centre) {
    double smallestX = objects[0].position.x;
    double biggestX = objects[0].position.x;
    double smallestY = objects[0].position.y;
    double biggestY = objects[0].position.y;

    for (int i = 1; i < size; i++){
        double x = objects[i].position.x;
        double y = objects[i].position.y;

        centre->x += x;
        centre->y += y;

        if (x < smallestX) {
            smallestX = x;
        }
        if (x > biggestX) {
            biggestX = x;
        }   
        if (y < smallestY) {
            smallestY = y;
        }
        if (y > biggestY) {
            biggestY = y;
        }
    }

    centre->x /= size;
    centre->y /= size;

    Vector vec = newVector((biggestX - smallestX) * 1.2 / GRIDSIZE, (biggestY - smallestY) * 1.2 / GRIDSIZE);
    return vec;
}

int main() {
    /*
    #pragma region sateliteAndEarth
    int objsSize = 3;
    Object objects[objsSize];
    Vector fresArray[objsSize];

    Vector earthPos = newVector(0, 0);
    objects[0] = newObj(5.972e24, earthPos, newEmptyVector());
    Vector mePos = newVector(8372000, 0);
    objects[1] = newObj(100, mePos, newVector(0, 7896));
    Vector meePos = newVector(0, 6372000);
    objects[2] = newObj(100, meePos, newVector(7896, 0));
    #pragma endregion
    */
    #pragma region solarSystem
    int objsSize = 9;
    Object objects[objsSize];
    Vector fresArray[objsSize];

    Vector sunPos = newVector(0, 0);
    objects[0] = newObj(1.989e30, sunPos, newEmptyVector());
    Vector pln1Pos = newVector(57.9e9, 0);
    objects[1] = newObj(0.33e24, pln1Pos, newVector(0, 47.4e3));
    Vector pln2Pos = newVector(108.2e9, 0);
    objects[2] = newObj(4.87e24, pln2Pos, newVector(0, 35e3));    
    Vector pln3Pos = newVector(149.6e9, 0);
    objects[3] = newObj(5.97e24, pln3Pos, newVector(0, 29.8e3));
    Vector pln4Pos = newVector(288e9, 0);
    objects[4] = newObj(0.642e24, pln4Pos, newVector(0, 24.1e3));    
    Vector pln5Pos = newVector(778.5e9, 0);
    objects[5] = newObj(1898e24, pln5Pos, newVector(0, 13.1e3));
    Vector pln6Pos = newVector(1432e9, 0);
    objects[6] = newObj(568e24, pln6Pos, newVector(0, 9.7e3));    
    Vector pln7Pos = newVector(2867e9, 0);
    objects[7] = newObj(86.8e24, pln7Pos, newVector(0, 6.8e3));
    Vector pln8Pos = newVector(4515e9, 0);
    objects[8] = newObj(102e24, pln8Pos, newVector(0, 5.4e3));    
    #pragma endregion


    char** grid = gridInit(GRIDSIZE);

    Vector centre = newEmptyVector();
    Vector metersPerUnits = getScale(objects, objsSize, &centre);

    int count = 0;

    clock_t start, end;
    double cpuTime = 0;

    while (1 == 1)
    {
        for (int i = 0; i < objsSize; i++)
        {
            setGrid(grid, '.', objects[i].position.x, objects[i].position.y, metersPerUnits, centre);     
        }

        start = clock();
        for (int i = 0; i < SECONDS_PER_PRINT; i++)
        {
            count += 1;
            
            getFres(objects, fresArray, objsSize);

            for (int i = 0; i < objsSize; i++)
            {
                updatePos(&objects[i], &fresArray[i]);   
            }
        }
        end = clock();

        for (int i = 0; i < objsSize; i++)
        {
            setGrid(grid, '0', objects[i].position.x, objects[i].position.y, metersPerUnits, centre);    
        }


        printGrid(grid);
        printf("Count: %d | ", count);
        printf("Centre: %f, %f | ", centre.x/(metersPerUnits.x+1), centre.y/(metersPerUnits.y+1));
        cpuTime += ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("Average time per %d ticks is %f", SECONDS_PER_PRINT, cpuTime / (count / SECONDS_PER_PRINT));
        for (int i = 0; i < objsSize; i++)
        {
            //printf("%f %f ", fresArray[i].x, fresArray[i].y);
        }
        printf("\033[%dA\033[0G", GRIDSIZE);

        usleep(1);
    }
    

    freeGrid(grid);

    Vector vec1 = newVector(10, 5);
    normalize(&vec1);
    Vector vec2 = newVector(3, 2);

    return 0;
}
