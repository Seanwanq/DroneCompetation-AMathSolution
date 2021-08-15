#ifndef DISPLACEMENT_H
#define DISPLACEMENT_H

#include "Coordinate.h"
#include "cmath"
#include "iostream"

using namespace std;

double CalDistance(double posX1, double posY1, double posX2, double posY2);
double BlueDroneDistance(Coordinate::_BluePlane _blueplane,
                         Coordinate::_Drone _drone);
double RedDroneDistance(Coordinate::_RedPlane _redplane,
                        Coordinate::_Drone _drone);
double BlueRedDistance(Coordinate::_BluePlane _blueplane,
                       Coordinate::_RedPlane _redplane);

#endif
