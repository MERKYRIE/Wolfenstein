#ifndef MERK_Misc
#define MERK_Misc

#include <MERK/MERK_World.h>

class CLASS_Misc
{
 public:
  void ErrorHandle(const char* Text);
  void LoadMap(const char* Path,int &MapSize,int &BarSize,int &StartX,int &StartY,CLASS_World::TYPE_Map &Map,CLASS_World::TYPE_Barrier &Barrier,CLASS_World::TYPE_Mechanism &Mechanism);
};

extern CLASS_Misc Misc;

#endif

















































