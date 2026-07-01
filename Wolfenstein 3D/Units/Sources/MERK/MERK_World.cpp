#include <vector>
#include <MERK/MERK_Misc.h>
#include <MERK/MERK_World.h>

void CLASS_World::Assign(int Block)
{
 CLASS_World::Block=Block;
 CLASS_World::HalfBlock=CLASS_World::Block/2;
 Misc.LoadMap("E1M1",CLASS_World::MaxBl,CLASS_World::BarSize,CLASS_World::StartX,CLASS_World::StartY,CLASS_World::Map,CLASS_World::Bar,CLASS_World::Mech);
 CLASS_World::MaxPx=CLASS_World::MaxBl*CLASS_World::Block-1;
}

int CLASS_World::GetMapCell(int X,int Y)
{
 return Y*CLASS_World::MaxBl+X;
}

int CLASS_World::GetBarCell(int X,int Y)
{
 return Y*CLASS_World::BarSize+X;
}

int CLASS_World::Find(int X,int Y)
{
 unsigned int Cnt;
 for(Cnt=0;Cnt<CLASS_World::Mech.size();Cnt++)
 {
  if (CLASS_World::Mech[Cnt].X==X && CLASS_World::Mech[Cnt].Y==Y)
  {
   return CLASS_World::Mech[Cnt].Offs;
  }
 }
 return 0;
}

//eof

















































