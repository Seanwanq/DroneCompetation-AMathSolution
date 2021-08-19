#ifndef RESTRAIN_H
#define RESTRAIN_H

#include "Coordinate.h"
#include "Distance.h"
#include "cmath"
#include "cstdlib"
#include "iostream"
#include "vector"

#define PI 3.14159

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

// 普通向量
struct NormVector {
public:
  double VectorX;
  double VectorY;
};

// 两点获得单位向量
UniVector TwoPoint2UniVector(double posX1, double posY1, double posX2,
                             double posY2);

// 普通向量转化单位向量
UniVector Norm2UniVector(NormVector normVector);

// 获得与指定向量向指定方向的垂直单位向量
UniVector VerticalUniVector(UniVector previousVector, double currentPosX,
                            double currentPosY, double destinationPosX,
                            double destinationPosY);

// 圆心
struct CircleCenter {
public:
  double posX;
  double posY;
};

// 获取切线圆的圆心
CircleCenter GetCircleCenter(UniVector previousVector, double currentPosX,
                             double currentPosY, double destinationPosX,
                             double destinationPosY, double radious);

// 获取在某长度时间内在某个半径圆上旋转角度（弧度）
double GetSpinDegree(double radius, double velocity, double timer);

// 某坐标点
struct Position {
public:
  double posX;
  double posY;
};

// 获取当前坐标点切线方向向量与x轴夹角...单位向量版
double GetTheta(UniVector uniVector);

// 获取当前坐标点切线方向向量与x轴夹角...普通向量版
double GetTheta(NormVector normVector);

// 在进行转向时，判断下一个位置...返回Position类
Position GetNextPositionWhenSwerve(Position currentPos,
                                   UniVector currentUniVector, Position destPos,
                                   double radius, double velocity,
                                   double timerStep);

// TODO
#endif