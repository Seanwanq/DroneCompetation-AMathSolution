#include "Coordinate.h"

Coordinate::Coordinate(double height, double width) {
  _height = height;
  _width = width;
  _blueid = 0;
  _redid = 0;
  _droneid = 0;

  _blueplane.resize(1);
  _redplane.resize(1);
  _drone.resize(1);
}

Coordinate::Coordinate(double height) {
  _height = height;
  _width = 50.0;
  _blueid = 0;
  _redid = 0;
  _droneid = 0;

  _blueplane.resize(1);
  _redplane.resize(1);
  _drone.resize(1);
}

void Coordinate::AddBluePlane(double posX, double posY) {
  _BluePlane bp{};
  bp.id = _blueid;
  bp.type = "blue";
  bp.posX = posX;
  bp.posY = posY;

  if (_blueid == 0) {
    _blueplane[bp.id] = bp;
  } else {
    _blueplane.push_back(bp);
  }

  _blueid++;
}

void Coordinate::AddRedPlane(double posX, double posY) {
  _RedPlane rp{};
  rp.id = _redid;
  rp.type = "red";
  rp.posX = posX;
  rp.posY = posY;

  if (_redid == 0) {
    _redplane[rp.id] = rp;
  } else {
    _redplane.push_back(rp);
  }

  _redid++;
}

void Coordinate::AddDrone(int boundTo, double posX, double posY,
                          bool ifRandom) {
  _Drone dr{};
  dr.id = _droneid;
  dr.type = "drone";
  if (ifRandom) {
    dr.posX = -1;
    dr.posY = -1;
    dr.ifRandom = true;
  } else {
    dr.posX = posX;
    dr.posY = posY;
    dr.ifRandom = false;
  }
  dr.BoundTo = boundTo;

  _droneid++;
}

void Coordinate::SetPlanePos(string type, int id, double posX, double posY) {
  if (type == "blue") {
    _blueplane[id].posX = posX;
    _blueplane[id].posY = posY;
  } else if (type == "red") {
    _redplane[id].posX = posX;
    _redplane[id].posY = posY;
  } else if (type == "drone") {
    _drone[id].posX = posX;
    _drone[id].posY = posY;
  }
}

Coordinate::_BluePlane Coordinate::GetBluePlaneInfo(int id) {
  return _blueplane[id];
}

Coordinate::_RedPlane Coordinate::GetRedPlaneInfo(int id) {
  return _redplane[id];
}

Coordinate::_Drone Coordinate::GetDroneInfo(int id) { return _drone[id]; }

int Coordinate::BluePlaneQuan() { return _blueid; }

int Coordinate::RedPlaneQuan() { return _redid; }

int Coordinate::DroneQuan() { return _droneid; }

double Coordinate::CoordinateHeight() { return _height; }

double Coordinate::CoordinateWidth() { return _width; }