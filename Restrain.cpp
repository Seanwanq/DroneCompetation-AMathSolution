#include "Restrain.h"
#include <corecrt_math.h>
#include <utility>
#include <vector>

double TimeRestrain(double timer) { return timer; }

double BluePlaneV() { return 0.25; }

double RedPlaneV() { return 0.3; }

double BluePlaneMinSwerveR() { return 0.5; }

double RedPlaneMinSwerveR() { return 1.0; }

double DroneV() { return 0.2; }

double DroneMinSwerveR() { return 0.35; }

bool IsBlueDroneClose(Coordinate::_BluePlane blueplane,
                      Coordinate::_Drone drone) {
  if (BlueDroneDistance(blueplane, drone) < 0.3) {
    return true;
  }
  return false;
}

bool IsRedDroneTooFar(Coordinate::_RedPlane redplane,
                      Coordinate::_Drone drone) {
  if (RedDroneDistance(redplane, drone) > 10) {
    return true;
  }
  return false;
}

bool IsRedDroneTooClose(Coordinate::_RedPlane redplane,
                        Coordinate::_Drone drone) {
  if (RedDroneDistance(redplane, drone) < 0.1) {
    return true;
  }
  return false;
}

bool IsRedDroneAllTooFar(Coordinate::_RedPlane redplane,
                         vector<Coordinate::_Drone> droneVector) {
  int redid = redplane.id;
  int size = droneVector.size();
  bool result = true;
  // 迭代器
  vector<Coordinate::_Drone>::iterator i;
  for (i = droneVector.begin(); i != droneVector.end(); i++) {
    if (i->BoundTo == redid) {
      result = result && IsRedDroneTooFar(redplane, *i);
    }
  }
  return result;
}

bool IsRedDroneExistTooClose(Coordinate::_RedPlane redplane,
                             vector<Coordinate::_Drone> droneVector) {
  bool result = false;
  // 迭代器
  vector<Coordinate::_Drone>::iterator i;
  for (i = droneVector.begin(); i != droneVector.end(); i++) {
    if (IsRedDroneTooClose(redplane, *i)) {
      result = result || true;
    }
  }
  return result;
}

bool IsCaptured(Coordinate::_BluePlane blueplane,
                vector<Coordinate::_Drone> droneVector) {
  int counter = 0;
  // 迭代器
  vector<Coordinate::_Drone>::iterator i;
  for (i = droneVector.begin(); i != droneVector.end(); i++) {
    if (IsBlueDroneClose(blueplane, *i)) {
      counter++;
    }
  }
  if (counter >= 2) {
    return true;
  }
  // 如果counter<2则返回false
  return false;
}

UniVector TwoPoint2UniVector(double posX1, double posY1, double posX2,
                             double posY2) {
  UniVector univector;
  if (((posX1 - posX2) == 0) && ((posY1 - posY2) == 0)) {
    univector.unitVectorX = 0;
    univector.unitVectorY = 0;
    return univector;
  }
  double length = CalDistance(posX1, posY1, posX2, posY2);
  univector.unitVectorX = (posX2 - posX1) / length;
  univector.unitVectorY = (posY2 - posY1) / length;
  return univector;
}

UniVector Norm2UniVector(NormVector normVector) {
  UniVector uniVector;
  double length = CalDistance(0, 0, normVector.VectorX, normVector.VectorY);
  uniVector.unitVectorX = normVector.VectorX / length;
  uniVector.unitVectorY = normVector.VectorY / length;
  return uniVector;
}

UniVector VerticalUniVector(UniVector previousVector, double currentPosX,
                            double currentPosY, double destinationPosX,
                            double destinationPosY) {
  UniVector verticalUniVector;
  if (previousVector.unitVectorX == 0 && previousVector.unitVectorY == 0) {
    double length =
        CalDistance(currentPosX, currentPosY, destinationPosX, destinationPosY);
    verticalUniVector.unitVectorX = (destinationPosX - currentPosX) / length;
    verticalUniVector.unitVectorY = (destinationPosY - currentPosY) / length;
    return verticalUniVector;
  } else if (previousVector.unitVectorX == 0) {
    if (destinationPosX - currentPosX >= 0) {
      verticalUniVector.unitVectorX = 1;
      verticalUniVector.unitVectorY = 0;
    } else if (destinationPosX - currentPosX < 0) {
      verticalUniVector.unitVectorX = -1;
      verticalUniVector.unitVectorY = 0;
    }
  } else if (previousVector.unitVectorY == 0) {
    if (destinationPosY - currentPosY >= 0) {
      verticalUniVector.unitVectorX = 0;
      verticalUniVector.unitVectorY = 1;
    } else if (destinationPosY - currentPosY < 0) {
      verticalUniVector.unitVectorX = 0;
      verticalUniVector.unitVectorY = -1;
    }
  } else {
    if (destinationPosX - currentPosX >= 0) {
      UniVector tempVector = {
          tempVector.unitVectorX = abs(1 / previousVector.unitVectorX),
          tempVector.unitVectorY = -abs(1 / previousVector.unitVectorY),
      };
      double length =
          CalDistance(0, 0, tempVector.unitVectorX, tempVector.unitVectorY);
      verticalUniVector.unitVectorX = tempVector.unitVectorX / length;
      verticalUniVector.unitVectorY = tempVector.unitVectorY / length;
    } else if (destinationPosX - currentPosX < 0) {
      UniVector tempVector = {
          tempVector.unitVectorX = -abs(1 / previousVector.unitVectorX),
          tempVector.unitVectorY = abs(1 / previousVector.unitVectorY),
      };
      double length =
          CalDistance(0, 0, tempVector.unitVectorX, tempVector.unitVectorY);
      verticalUniVector.unitVectorX = tempVector.unitVectorX / length;
      verticalUniVector.unitVectorY = tempVector.unitVectorY / length;
    }
  }
  return verticalUniVector;
}

CircleCenter GetCircleCenter(UniVector previousVector, double currentPosX,
                             double currentPosY, double destinationPosX,
                             double destinationPosY, double radious) {
  CircleCenter circleCenter;
  UniVector verticalUniVector =
      VerticalUniVector(previousVector, currentPosX, currentPosY,
                        destinationPosX, destinationPosY);
  UniVector lengthVector = {
      lengthVector.unitVectorX = verticalUniVector.unitVectorX * radious,
      lengthVector.unitVectorY = verticalUniVector.unitVectorY * radious,
  };
  circleCenter.posX = currentPosX + lengthVector.unitVectorX;
  circleCenter.posY = currentPosY + lengthVector.unitVectorY;
  return circleCenter;
}

double GetSpinDegree(double radius, double velocity, double timer) {
  return velocity * timer / radius;
}

double GetTheta(UniVector uniVector) {
  double angle;
  if (uniVector.unitVectorX == 0 && uniVector.unitVectorY >= 0) {
    return angle = PI / 2;
  } else if (uniVector.unitVectorX == 0 && uniVector.unitVectorY < 0) {
    return angle = -PI / 2;
  }

  if (uniVector.unitVectorX >= 0) {
    angle = atan(uniVector.unitVectorY / uniVector.unitVectorX);
  } else if (uniVector.unitVectorX < 0) {
    angle = PI / 2 + atan(uniVector.unitVectorY / uniVector.unitVectorX);
  }
  return angle;
}

double GetTheta(NormVector normVector) {
  UniVector uniVector = Norm2UniVector(normVector);
  return GetTheta(uniVector);
}

Position GetNextPositionWhenSwerve(Position currentPos,
                                   UniVector currentUniVector, Position destPos,
                                   double radius, double velocity,
                                   double timerStep) {
  Position nextPosition;
  // 获得步长角∠
  double tempAngle = GetSpinDegree(radius, velocity, timerStep);
  double theta = GetTheta(currentUniVector);
  double nextThetaPlus, nextThetaMinus;

  nextThetaPlus = theta + tempAngle;
  nextThetaMinus = theta - tempAngle;

  NormVector tempVectorPlus, tempVectorMinus;

  tempVectorPlus.VectorX = cos(nextThetaPlus);
  tempVectorPlus.VectorY = sin(nextThetaPlus);

  tempVectorMinus.VectorX = cos(nextThetaMinus);
  tempVectorMinus.VectorY = sin(nextThetaMinus);

  Position tempPosPlus, tempPosMinus;

  tempPosPlus.posX =
      currentPos.posX + velocity * timerStep * tempVectorPlus.VectorX;
  tempPosPlus.posY =
      currentPos.posY + velocity * timerStep * tempVectorPlus.VectorY;

  tempPosMinus.posX =
      currentPos.posX + velocity * timerStep * tempVectorMinus.VectorX;
  tempPosMinus.posY =
      currentPos.posY + velocity * timerStep * tempVectorMinus.VectorY;

  double distancePlus, distanceMinus;

  distancePlus = CalDistance(tempPosPlus.posX, tempPosPlus.posY, destPos.posX,
                             destPos.posY);

  distanceMinus = CalDistance(tempPosMinus.posX, tempPosMinus.posY,
                              destPos.posX, destPos.posY);

  if (distancePlus <= distanceMinus) {
    nextPosition = tempPosPlus;
  } else {
    nextPosition = tempPosMinus;
  }

  return nextPosition;
}

Position GetNextPositionWhenSwerve(Position currentPos,
                                   NormVector currentNormVector,
                                   Position destPos, double radius,
                                   double velocity, double timerStep) {
  UniVector currentUniVector = Norm2UniVector(currentNormVector);
  return GetNextPositionWhenSwerve(currentPos, currentUniVector, destPos,
                                   radius, velocity, timerStep);
}

Position GetNextPositionWhenLine(Position currentPos, Position destPos,
                                 double velocity, double timerStep) {
  Position nextPosition;
  UniVector nextUniVector = TwoPoint2UniVector(currentPos.posX, currentPos.posY,
                                               destPos.posX, destPos.posY);
  nextPosition.posX =
      currentPos.posX + velocity * timerStep * nextUniVector.unitVectorX;
  nextPosition.posY =
      currentPos.posY + velocity * timerStep * nextUniVector.unitVectorY;

  return nextPosition;
}

Position GetNextPosition(Position currentPos, UniVector currentUniVector,
                         Position destPos, double radius, double velocity,
                         double timerStep) {
  Position nextPosition;

  UniVector current2DestUniVector = TwoPoint2UniVector(
      currentPos.posX, currentPos.posY, destPos.posX, destPos.posY);

  if (currentUniVector.unitVectorX == current2DestUniVector.unitVectorX &&
      currentUniVector.unitVectorY == current2DestUniVector.unitVectorY) {
    nextPosition =
        GetNextPositionWhenLine(currentPos, destPos, velocity, timerStep);
    return nextPosition;
  }

  nextPosition = GetNextPositionWhenSwerve(
      currentPos, currentUniVector, destPos, radius, velocity, timerStep);

  return nextPosition;
}

vector<Position> posCountingSort(vector<Position> posVec) {
  int len = posVec.size();
  for (int i = 0; i < len - 1; i++) {
    for (int j = 0; j < len - 1 - i; j++) {
      if (posVec[j].posY > posVec[j + 1].posY) { // 相邻元素两两对比
        double temp = posVec[j + 1].posY;        // 元素交换
        posVec[j + 1].posY = posVec[j].posY;
        posVec[j].posY = temp;
      }
    }
  }
  return posVec;
}

Position IsDroneTooClose(Coordinate::_Drone drone,
                         vector<Coordinate::_Drone> droneVec, double velocity,
                         double timerStep) {
  Position nextPosition = {
      nextPosition.posX = 0,
      nextPosition.posY = 0,
  };

  vector<double> distanceVec;

  vector<Coordinate::_Drone>::iterator i;
  for (i = droneVec.begin(); i != droneVec.end(); i++) {
    if (drone.id == i->id) {
      continue;
    }
    double distance = CalDistance(drone.posX, drone.posY, i->posX, i->posY);
    if (distance < 0.3) {
      distanceVec.push_back(distance);
      UniVector uniVector =
          TwoPoint2UniVector(drone.posX, drone.posY, i->posX, i->posY);
      UniVector reversed = {
          reversed.unitVectorX = -uniVector.unitVectorX,
          reversed.unitVectorY = -uniVector.unitVectorY,
      };
      nextPosition.posX =
          nextPosition.posX + reversed.unitVectorX * velocity * 0.5 * timerStep;
      nextPosition.posY =
          nextPosition.posY + reversed.unitVectorY * velocity * 0.5 * timerStep;
    }
  }

  nextPosition.posX = nextPosition.posX / distanceVec.size() + drone.posX;
  nextPosition.posY = nextPosition.posY / distanceVec.size() + drone.posY;

  return nextPosition;
}