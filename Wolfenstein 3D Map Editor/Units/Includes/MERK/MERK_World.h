#ifndef MERK_World
#define MERK_World

class CLASS_World
{
 public:
  typedef std::vector <unsigned char> TYPE_Map;
  typedef std::vector <unsigned char> TYPE_Barrier;
  typedef std::vector <unsigned char> TYPE_Check;
  typedef class CLASS_Cell
  {
   public:
    int X,Y;
  };
  typedef std::vector <CLASS_Cell> TYPE_Stack;
  typedef std::vector <CLASS_Cell> TYPE_Mechanism;
  TYPE_Map Map;               
  TYPE_Barrier Bar;
  TYPE_Check Check;
  TYPE_Stack Stack;
  TYPE_Mechanism Mech;
  int Block,HalfBlock,X,Y,MinBl,MaxBl,MinPx,MaxPx,MapCnt,BarCnt,MapSize,BarSize,BarSizeBl,BarSizePx,StartX,StartY,TotalX,TotalY,Offs;
  char Name[256+1];
  void Assign(int Block,int Height,int Offs);
  int GetMapCell(int X,int Y);
  int GetBarCell(int X,int Y);
  void Add(int X,int Y);
  void Del(int X,int Y);
  bool IsMapClosed();
};


#endif

















































