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

/* 思路
 *  位移是通过x轴和y轴两个分量进行位移
 * 对于直线的实现比较容易，对于圆弧的实现，由于每一次步长都会重新计算终点
 * 所以没有必要考虑圆弧的终点
 * 每次位移通过cosθ和sinθ来计算x和y分量
 * 就会方便很多
 */

// TODO

#endif
