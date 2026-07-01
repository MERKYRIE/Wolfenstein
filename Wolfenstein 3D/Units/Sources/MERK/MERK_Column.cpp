#include <vector>
#include <SDL/SDL.h>
#include <MERK/MERK_Column.h>

void CLASS_Column::Assign(int Block,int Plane,int HalfWidth,double HalfFov,int ImgOffs)
{
 CLASS_Column::BlockPlane=Block*Plane;
 CLASS_Column::DgrToScr=double(HalfWidth)/HalfFov;
 CLASS_Column::Src.w=1;
 CLASS_Column::Src.h=ImgOffs;
 CLASS_Column::Dst.w=1;
 CLASS_Column::ImgOffs=ImgOffs;
}

bool CLASS_Column::Find(int X,int Y)
{
 unsigned int Cnt;
 for(Cnt=0;Cnt<CLASS_Column::Stack.size();Cnt++)
 {
  if (CLASS_Column::Stack[Cnt].X==X && CLASS_Column::Stack[Cnt].Y==Y)
  {
   return true;
  }
 }
 return false;
}

//eof

















































