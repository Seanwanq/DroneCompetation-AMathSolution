#ifndef DISPLACEMENT_H
#define DISPLACEMENT_H

#include "Restrain.h"
#include "iostream"
#include "vector"

using namespace std;

void BlueDisplacement(Coordinate::_BluePlane blueplane, double posX,
                      double posY);
void RedDisplacement(Coordinate::_RedPlane redplane, double posX, double posY);

void DroneDisplacement(Coordinate::_Drone drone, double posX, double posY);

#endif
