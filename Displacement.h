#ifndef DISPLACEMENT_H
#define DISPLACEMENT_H

#include "Restrain.h"
#include "iostream"
#include "vector"

using namespace std;

void BlueDisplacementSimple(Coordinate::_BluePlane blueplane, double posX,
                            double posY);
void RedDisplacementSimple(Coordinate::_RedPlane redplane, double posX,
                           double posY);

void DroneDisplacementSimple(Coordinate::_Drone drone, double posX,
                             double posY);

/* 思路
 *  位移是通过x轴和y轴两个分量进行位移
 * 对于直线的实现比较容易，对于圆弧的实现，由于每一次步长都会重新计算终点
 * 所以没有必要考虑圆弧的终点
 * 每次位移通过cosθ和sinθ来计算x和y分量
 * 就会方便很多
 */

// 蓝方飞机移动...添加约束限制...自动判断终点...返回PositionAndVector类
PositionAndVector BlueAutoJudgement(Coordinate::_BluePlane bluePlane,
                                    vector<Coordinate::_Drone> drone,
                                    UniVector currentUniVector, double radius,
                                    double velocity, double timerStep);

// 蓝方飞机位移封装
PositionAndVector BlueDisplacement(Coordinate::_BluePlane bluePlane,
                                   PositionAndVector posAndVec,
                                   vector<Coordinate::_Drone> drone,
                                   double radius, double velocity,
                                   double timerStep);

// 无人机移动...添加约束条件...自动判断终点...返回PositionAndVector类
PositionAndVector DroneAutoJudgement(Coordinate::_Drone drone,
                                     PositionAndVector dronePosAndVec,
                                     vector<Coordinate::_BluePlane> blueVec,
                                     vector<Coordinate::_RedPlane> redVec,
                                     vector<Coordinate::_Drone> droneVec,
                                     double radius, double velocity,
                                     double timerStep);

#endif
