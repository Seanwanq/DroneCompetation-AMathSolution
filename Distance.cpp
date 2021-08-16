#include "Distance.h"

double CalDistance(double posX1, double posY1, double posX2, double posY2) {
  double distance;
  distance = sqrt(pow(posX1 - posX2, 2) + pow(posY1 - posY2, 2));
  return distance;
}

double BlueDroneDistance(Coordinate::_BluePlane blueplane,
                         Coordinate::_Drone drone) {
  return CalDistance(blueplane.posX, blueplane.posY, drone.posX, drone.posY);
}

double RedDroneDistance(Coordinate::_RedPlane redplane,
                        Coordinate::_Drone drone) {
  return CalDistance(redplane.posX, redplane.posY, drone.posX, drone.posY);
}

double BlueRedDistance(Coordinate::_BluePlane blueplane,
                       Coordinate::_RedPlane redplane) {
  return CalDistance(blueplane.posX, blueplane.posY, redplane.posX,
                     redplane.posY);
}