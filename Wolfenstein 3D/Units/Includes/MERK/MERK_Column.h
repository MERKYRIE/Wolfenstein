#ifndef MERK_Column
#define MERK_Column

class CLASS_Column
{
 public:
  typedef class CLASS_Stack
  {
   public:
    int X,Y,HitNum;
    double Dist;
    SDL_Rect Src,Dst;
  };
  typedef class CLASS_Sort
  {
   public:
    int CellCnt;
    double Dist;
  };
  typedef std::vector <CLASS_Stack> TYPE_Stack;
  typedef std::vector <CLASS_Sort> TYPE_Sort;
  TYPE_Stack Stack;
  TYPE_Sort Sort;
  enum ENUM_IntType
  {
   NORMAL,
   DOORWALK
  };
  int VerOffs,HorOffs,Offs,VerHitNum,HorHitNum,HitNum,BlockPlane,ImgOffs,VerIntType,HorIntType;
  double DgrToScr;
  SDL_Rect Src,Dst;
  void Assign(int Block,int Plane,int HalfWidth,double HalfFov,int ImgOffs);
  bool Find(int X,int Y);
};

#endif

















































