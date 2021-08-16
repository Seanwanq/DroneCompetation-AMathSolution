#include "Displacement.h"

void BlueDisplacement(Coordinate::_BluePlane blueplane, double posX,
                      double posY) {
  blueplane.posX = posX;
  blueplane.posY = posY;
}

void RedDisplacement(Coordinate::_RedPlane redplane, double posX, double posY) {
  redplane.posX = posX;
  redplane.posY = posY;
}

void DroneDisplacement(Coordinate::_Drone drone, double posX, double posY) {
  drone.posX = posX;
  drone.posY = posY;
}
