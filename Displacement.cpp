#include "Displacement.h"
#include <algorithm>
#include <vector>

void BlueDisplacementSimple(Coordinate::_BluePlane blueplane, double posX,
                            double posY) {
  blueplane.posX = posX;
  blueplane.posY = posY;
}

void RedDisplacementSimple(Coordinate::_RedPlane redplane, double posX,
                           double posY) {
  redplane.posX = posX;
  redplane.posY = posY;
}

void DroneDisplacementSimple(Coordinate::_Drone drone, double posX,
                             double posY) {
  drone.posX = posX;
  drone.posY = posY;
}

PositionAndVector BlueAutoJudgement(Coordinate::_BluePlane bluePlane,
                                    vector<Coordinate::_Drone> drone,
                                    UniVector currentUniVector, double radius,
                                    double velocity, double timerStep) {
  Position currentPosition = {
      currentPosition.posX = bluePlane.posX,
      currentPosition.posY = bluePlane.posY,
  };
  PositionAndVector nextPosition;

  Position rightTop = {
      rightTop.posX = Coordinate::CoordinateWidth(),
      rightTop.posY = Coordinate::CoordinateHeight(),
  };
  Position rightButtom = {
      rightButtom.posX = Coordinate::CoordinateWidth(),
      rightButtom.posY = 0,
  };

  Position tempPosition1; // 用于矫正过下或过上的坐标点 若值为(-10,
                          // -10)则忽略该坐标点
  Position tempPosition2; // 用于存储计算后无人机空隙坐标

  Position destPos;

  tempPosition1.posX = -10;
  tempPosition1.posY = -10;

  // 制定规则
  if (bluePlane.posY < BluePlaneV()) {
    tempPosition1.posX = Coordinate::CoordinateWidth();
    tempPosition1.posY = BluePlaneV();
  } else if (bluePlane.posY > Coordinate::CoordinateHeight() - BluePlaneV()) {
    tempPosition1.posX = Coordinate::CoordinateWidth();
    tempPosition1.posY = Coordinate::CoordinateHeight() - BluePlaneV();
  }

  vector<Position> dronePosition;
  vector<Coordinate::_Drone>::iterator i;
  for (i = drone.begin(); i != drone.end(); i++) {
    Position iPos;
    iPos.posX = i->posX;
    iPos.posY = i->posY;
    dronePosition.push_back(iPos);
  }

  dronePosition.push_back(rightButtom);
  dronePosition.push_back(rightTop);

  int dronePositionLength = dronePosition.size();

  vector<Position> sortedPosY = posCountingSort(dronePosition);

  vector<double> differenceY;

  // 迭代器
  vector<Position>::iterator m;

  for (m = sortedPosY.begin(); m != sortedPosY.end() - 1; m++) {
    differenceY.push_back((m + 1)->posY - m->posY);
  }

  double maxDifferenceY = *max_element(differenceY.begin(), differenceY.end());

  int maxDifferenceNo = 0;

  // double 迭代器
  vector<double>::iterator n;

  for (n = differenceY.begin(); n != differenceY.end(); n++) {
    if (*n == maxDifferenceY) {
      break;
    }
    maxDifferenceNo++;
  }

  tempPosition2.posX = Coordinate::CoordinateWidth();
  tempPosition2.posY = sortedPosY[maxDifferenceNo].posY + maxDifferenceY / 2;

  if (tempPosition1.posX != -10 && tempPosition1.posY != -10) {
    destPos.posY = (tempPosition1.posY + tempPosition2.posY) / 2;
    destPos.posX = tempPosition2.posX;
    UniVector nextUniVector = TwoPoint2UniVector(
        currentPosition.posX, currentPosition.posY, destPos.posX, destPos.posY);
    Position tempNextPos =
        GetNextPosition(currentPosition, currentUniVector, destPos, radius,
                        velocity, timerStep);
    nextPosition.uniVector = nextUniVector;
    nextPosition.posX = tempNextPos.posX;
    nextPosition.posY = tempNextPos.posY;
    return nextPosition;
  }

  // 如果tempPosition1不生效
  destPos.posY = tempPosition2.posY;
  destPos.posX = tempPosition2.posX;
  UniVector nextUniVector = TwoPoint2UniVector(
      currentPosition.posX, currentPosition.posY, destPos.posX, destPos.posY);
  Position tempNextPos = GetNextPosition(currentPosition, currentUniVector,
                                         destPos, radius, velocity, timerStep);
  nextPosition.uniVector = nextUniVector;
  nextPosition.posX = tempNextPos.posX;
  nextPosition.posY = tempNextPos.posY;

  return nextPosition;
}

PositionAndVector BlueDisplacement(Coordinate::_BluePlane bluePlane,
                                   PositionAndVector posAndVec,
                                   vector<Coordinate::_Drone> drone,
                                   double radius, double velocity,
                                   double timerStep) {
  PositionAndVector nextPosAndVec;

  nextPosAndVec = BlueAutoJudgement(bluePlane, drone, posAndVec.uniVector,
                                    radius, velocity, timerStep);
  BlueDisplacementSimple(bluePlane, nextPosAndVec.posX, nextPosAndVec.posY);

  return nextPosAndVec;
}

PositionAndVector DroneAutoJudgement(Coordinate::_Drone drone,
                                     PositionAndVector dronePosAndVec,
                                     vector<Coordinate::_BluePlane> blueVec,
                                     vector<Coordinate::_RedPlane> redVec,
                                     vector<Coordinate::_Drone> droneVec,
                                     double radius, double velocity,
                                     double timerStep) {
  PositionAndVector nextPosAndVec;

  // TODO
  Position tempPos1; // 用于判断无人机是否会碰撞的temp
  tempPos1 = IsDroneTooClose(drone, droneVec, velocity, timerStep);

  Position tempPos2; // 用于获得蓝方飞机位置
  // tempPos2.posX = redVec;

  return nextPosAndVec;
}