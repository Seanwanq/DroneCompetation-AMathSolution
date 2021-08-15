#ifndef RESTRAIN_H
#define RESTRAIN_H

#include "Coordinate.h"
#include "Displacement.h"
#include "iostream"
#include "vector"

using namespace std;

// 限制时间在360s内的
double TimeRestrain();
// 蓝方飞机速度
double BluePlaneV();
// 红方飞机速度
double RedPlaneV();
// 蓝方飞机最小转弯半径
double BluePlaneMinSwerveR();
// 红方飞机最小转弯半径
double RedPlaneMinSwerveR();
// 无人机飞行速度
double DroneV();
// 无人机最小转弯半径
double DroneMinSwerveR();
// 判断蓝方飞机与无人机距离是否小于300m
bool IsBlueDroneClose(Coordinate::_BluePlane _blueplane,
                      Coordinate::_Drone _drone);
// 判断红色运载机与无人机是否超过10km
bool IsRedDroneTooFar(Coordinate::_RedPlane _redplane,
                      Coordinate::_Drone _drone);
// 判断红色运载机与无人机是否小于100m
bool IsRedDroneTooClose(Coordinate::_RedPlane _redplane,
                        Coordinate::_Drone _drone);
// 判断红方运载机与所属无人机是否距离全部超过10km
bool IsRedDroneAllTooFar(Coordinate::_RedPlane _redplane,
                         vector<Coordinate::_Drone> _droneVector);
// 判断红方运载机与无人机是否距离*存在*小于100m的
bool IsRedDroneExistTooClose(Coordinate::_RedPlane _redplane,
                             vector<Coordinate::_Drone> _droneVector);
// 判断蓝方飞机是否被拦截
bool IsCaptured(Coordinate::_BluePlane _blueplane,
                vector<Coordinate::_Drone> _droneVector);

#endif