#include "Restrain.h"

double BluePlaneV() { return 0.25; }

double RedPlaneV() { return 0.3; }

double BluePlaneMinSwerveR() { return 0.5; }

double RedPlaneMinSwerveR() { return 1.0; }

double DroneV() { return 0.2; }

double DroneMinSwerveR() { return 0.35; }

bool IsBlueDroneClose(Coordinate::_BluePlane _blueplane,
                      Coordinate::_Drone _drone) {
  if (BlueDroneDistance(_blueplane, _drone) < 0.3) {
    return true;
  }
  return false;
}

bool IsRedDroneTooFar(Coordinate::_RedPlane _redplane,
                      Coordinate::_Drone _drone) {
  if (RedDroneDistance(_redplane, _drone) > 10) {
    return true;
  }
  return false;
}

bool IsRedDroneTooClose(Coordinate::_RedPlane _redplane,
                        Coordinate::_Drone _drone) {
  if (RedDroneDistance(_redplane, _drone) < 0.1) {
    return true;
  }
  return false;
}

bool IsRedDroneAllTooFar(Coordinate::_RedPlane _redplane,
                         vector<Coordinate::_Drone> _droneVector) {
  int redid = _redplane.id;
  int size = _droneVector.size();
  bool result = true;
  // 迭代器
  vector<Coordinate::_Drone>::iterator i;
  for (i = _droneVector.begin(); i != _droneVector.end(); i++) {
    if (i->BoundTo == redid) {
      result = result && IsRedDroneTooFar(_redplane, *i);
    }
  }
  return result;
}

bool IsRedDroneExistTooClose(Coordinate::_RedPlane _redplane,
                             vector<Coordinate::_Drone> _droneVector) {
  bool result = false;
  // 迭代器
  vector<Coordinate::_Drone>::iterator i;
  for (i = _droneVector.begin(); i != _droneVector.end(); i++) {
    if (IsRedDroneTooClose(_redplane, *i)) {
      result = result || true;
    }
  }
  return result;
}

bool IsCaptured(Coordinate::_BluePlane _blueplane,
                vector<Coordinate::_Drone> _droneVector) {
  int counter = 0;
  // 迭代器
  vector<Coordinate::_Drone>::iterator i;
  for (i = _droneVector.begin(); i != _droneVector.end(); i++) {
    if (IsBlueDroneClose(_blueplane, *i)) {
      counter++;
    }
  }
  if (counter >= 2) {
    return true;
  }
  // 如果counter<2则返回false
  return false;
}