#ifndef MERK_World
#define MERK_World

class CLASS_World
{
 public:
  typedef std::vector <unsigned char> TYPE_Map;
  typedef std::vector <unsigned char> TYPE_Barrier;
  typedef class CLASS_Mechanism
  {
   public:
    int X,Y,Offs;
  };
  typedef std::vector <CLASS_Mechanism> TYPE_Mechanism;
  TYPE_Map Map;
  TYPE_Barrier Bar;
  TYPE_Mechanism Mech;
  int Block,HalfBlock,MaxBl,MaxPx,StartX,StartY,BarSize;
  void Assign(int Block);
  int GetMapCell(int X,int Y);
  int GetBarCell(int X,int Y);
  int Find(int X,int Y);
};


#endif

















































