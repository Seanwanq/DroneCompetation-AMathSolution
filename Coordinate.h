#ifndef COORDINATE_H
#define COORDINATE_H

#include "iostream"
#include "vector"

using namespace std;

// 该类用于设定坐标系，创建飞机，改变飞机参数，获取飞机参数
class Coordinate {
private:
  double _height;
  double _width;

  int _blueid;  // 蓝方飞机编号 从0开始
  int _redid;   // 红方飞机编号 从0开始
  int _droneid; // 无人机编号 从0开始

public:
  Coordinate(double height, double width);

  Coordinate(double height);

  void AddBluePlane(double posX, double posY);

  void AddRedPlane(double posX, double posY);

  // bound是绑定到红方哪个飞机，posX和posY如果生成随机的话填-1，
  // ifRandom在不随机生成时填false，在随机生成时填true
  void AddDrone(int boundTo, double posX, double posY, bool ifRandom);

  // 设置飞机位置 传入参数：XXX.type, XXX.id, x坐标, y坐标
  void SetPlanePos(string type, int id, double posX, double posY);

  class _BluePlane {
  public:
    int id;
    string type;
    double posX;
    double posY;
  };

  class _RedPlane {
  public:
    int id;
    string type;
    double posX;
    double posY;
  };

  class _Drone {
  public:
    int id;
    string type;
    double posX;
    double posY;
    int BoundTo;
    bool ifRandom;
  };

  vector<_BluePlane> _blueplane;
  vector<_RedPlane> _redplane;
  vector<_Drone> _drone;

  // 获取飞机信息
  _BluePlane GetBluePlaneInfo(int id);
  _RedPlane GetRedPlaneInfo(int id);
  _Drone GetDroneInfo(int id);

  // 获取全局信息
  int BluePlaneQuan();
  int RedPlaneQuan();
  int DroneQuan();
};

#endif