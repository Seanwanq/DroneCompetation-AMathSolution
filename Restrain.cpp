#include "Restrain.h"

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

UniVector VerticalVector2Point(UniVector previousVector, double currentPosX,
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
    // TODO
  }
  return verticalUniVector;
}