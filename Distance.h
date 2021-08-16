#ifndef DISTANCE_H
#define DISTANCE_H

#include "Coordinate.h"
#include "cmath"
#include "iostream"

using namespace std;

// 计算两点距离
double CalDistance(double posX1, double posY1, double posX2, double posY2);
// 计算蓝方和无人机距离
double BlueDroneDistance(Coordinate::_BluePlane blueplane,
                         Coordinate::_Drone drone);
// 计算红方和无人机距离
double RedDroneDistance(Coordinate::_RedPlane redplane,
                        Coordinate::_Drone drone);
// 计算蓝方和红方距离
double BlueRedDistance(Coordinate::_BluePlane blueplane,
                       Coordinate::_RedPlane redplane);

#endif
