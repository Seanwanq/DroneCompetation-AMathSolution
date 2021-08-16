#ifndef RESTRAIN_H
#define RESTRAIN_H

#include "Coordinate.h"
#include "Distance.h"
#include "iostream"
#include "vector"

using namespace std;

// 限制时间在设定时间内的
double TimeRestrain(double timer);
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
bool IsBlueDroneClose(Coordinate::_BluePlane blueplane,
                      Coordinate::_Drone drone);
// 判断红色运载机与无人机是否超过10km
bool IsRedDroneTooFar(Coordinate::_RedPlane redplane, Coordinate::_Drone drone);
// 判断红色运载机与无人机是否小于100m
bool IsRedDroneTooClose(Coordinate::_RedPlane redplane,
                        Coordinate::_Drone drone);
// 判断红方运载机与所属无人机是否距离全部超过10km
bool IsRedDroneAllTooFar(Coordinate::_RedPlane redplane,
                         vector<Coordinate::_Drone> droneVector);
// 判断红方运载机与无人机是否距离*存在*小于100m的
bool IsRedDroneExistTooClose(Coordinate::_RedPlane redplane,
                             vector<Coordinate::_Drone> droneVector);
// 判断蓝方飞机是否被拦截
bool IsCaptured(Coordinate::_BluePlane blueplane,
                vector<Coordinate::_Drone> droneVector);

// 单位向量
struct UniVector {
public:
  double unitVectorX;
  double unitVectorY;
};

// 两点获得单位向量
UniVector TwoPoint2UniVector(double posX1, double posY1, double posX2,
                             double posY2);

// 获得与指定向量向指定方向的垂直单位向量
UniVector VerticalVector2Point(UniVector previousVector, double currentPosX,
                               double currentPosY, double destinationPosX,
                               double destinationPosY);

#endif