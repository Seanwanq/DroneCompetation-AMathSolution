#include "Displacement.h"

double CalDistance(double posX1, double posY1, double posX2, double posY2) {
  double distance;
  distance = sqrt(pow(posX1 - posX2, 2) + pow(posY1 - posY2, 2));
  return distance;
}

double BlueDroneDistance(Coordinate::_BluePlane _blueplane,
                         Coordinate::_Drone _drone) {
  return CalDistance(_blueplane.posX, _blueplane.posY, _drone.posX,
                     _drone.posY);
}

double RedDroneDistance(Coordinate::_RedPlane _redplane,
                        Coordinate::_Drone _drone) {
  return CalDistance(_redplane.posX, _redplane.posY, _drone.posX, _drone.posY);
}

double BlueRedDistance(Coordinate::_BluePlane _blueplane,
                       Coordinate::_RedPlane _redplane) {
  return CalDistance(_blueplane.posX, _blueplane.posY, _redplane.posX,
                     _redplane.posY);
}