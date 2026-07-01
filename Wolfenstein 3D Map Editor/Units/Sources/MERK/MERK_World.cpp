#include <vector>
#include <MERK/MERK_World.h>

void CLASS_World::Assign(int Block,int Height,int Offs)
{
 CLASS_World::Block=Block;
 CLASS_World::HalfBlock=CLASS_World::Block/2;
 CLASS_World::MapSize=64;
 CLASS_World::BarSizePx=20;
 CLASS_World::BarSizeBl=CLASS_World::BarSizePx/CLASS_World::Block;
	strcpy_s(CLASS_World::Name,sizeof(CLASS_World::Name),"E1M1");
 CLASS_World::X=0;
 CLASS_World::Y=0;
 CLASS_World::MinBl=0;
 CLASS_World::MaxBl=CLASS_World::MapSize-Height/CLASS_World::Block;
 CLASS_World::MinPx=CLASS_World::MinBl*CLASS_World::Block+CLASS_World::Block;
 CLASS_World::MaxPx=CLASS_World::MapSize*CLASS_World::Block-CLASS_World::Block;
	CLASS_World::MapCnt=CLASS_World::MapSize*CLASS_World::MapSize;
 CLASS_World::Map.resize(CLASS_World::MapCnt);
 CLASS_World::BarCnt=CLASS_World::MapCnt*CLASS_World::MapCnt;
 CLASS_World::Bar.resize(CLASS_World::BarCnt);
 CLASS_World::BarSize=CLASS_World::MapCnt;
 CLASS_World::Check.resize(CLASS_World::MapCnt);
 CLASS_World::StartX=0;
 CLASS_World::StartY=0;
 CLASS_World::Offs=Offs;
}

int CLASS_World::GetMapCell(int X,int Y)
{
 return Y*CLASS_World::MapSize+X;
}

int CLASS_World::GetBarCell(int X,int Y)
{
 return Y*CLASS_World::BarSize+X;
}

void CLASS_World::Add(int X,int Y)
{
 CLASS_World::Stack.resize(CLASS_World::Stack.size()+1);
 CLASS_World::Stack[CLASS_World::Stack.size()-1].X=X;
 CLASS_World::Stack[CLASS_World::Stack.size()-1].Y=Y;
}

void CLASS_World::Del(int X,int Y)
{
 int Cnt=0;
 while (CLASS_World::Stack[Cnt].X!=X || CLASS_World::Stack[Cnt].Y!=Y)
 {
  Cnt++;
 }
 CLASS_World::Stack.erase(CLASS_World::Stack.begin()+Cnt);
}

bool CLASS_World::IsMapClosed()
{
 int X,Y;
 bool Done=false;
 for (X=CLASS_World::MinBl;X<CLASS_World::MapSize;X++)
 {
  for (Y=CLASS_World::MinBl;Y<CLASS_World::MapSize;Y++)
  {
   CLASS_World::Check[CLASS_World::GetMapCell(X,Y)]=0;
  }
 }
 CLASS_World::Stack.clear();
 X=CLASS_World::StartX/CLASS_World::Block;
 Y=CLASS_World::StartY/CLASS_World::Block;
 CLASS_World::Add(X,Y);
 while (!Done)
 {
  CLASS_World::Check[CLASS_World::GetMapCell(X,Y)]=255;
  if (Y-1!=CLASS_World::MinBl)
  {
   if (CLASS_World::Map[CLASS_World::GetMapCell(X,Y-1)]==0 || CLASS_World::Map[CLASS_World::GetMapCell(X,Y-1)]>=200)
   {
    if (CLASS_World::Check[CLASS_World::GetMapCell(X,Y-1)]==0)
    {
     CLASS_World::Add(X,Y-1);
     CLASS_World::Check[CLASS_World::GetMapCell(X,Y-1)]=1;
    }
   }
   else
   {
    CLASS_World::Check[CLASS_World::GetMapCell(X,Y-1)]=255;
   }
  }
  else
  {
   if (CLASS_World::Map[CLASS_World::GetMapCell(X,Y-1)]!=0 && CLASS_World::Map[CLASS_World::GetMapCell(X,Y-1)]<200)
   {
    CLASS_World::Check[CLASS_World::GetMapCell(X,Y-1)]=255;
   }
   else
   { 
    return false;
   }
  }
  if (X-1!=CLASS_World::MinBl)
  {
   if (CLASS_World::Map[CLASS_World::GetMapCell(X-1,Y)]==0 || CLASS_World::Map[CLASS_World::GetMapCell(X-1,Y)]>=200)
   {
    if (CLASS_World::Check[CLASS_World::GetMapCell(X-1,Y)]==0)
    {
     CLASS_World::Add(X-1,Y);
     CLASS_World::Check[CLASS_World::GetMapCell(X-1,Y)]=1;
    }
   }
   else
   {
    CLASS_World::Check[CLASS_World::GetMapCell(X-1,Y)]=255;
   }
  }
  else
  {
   if (CLASS_World::Map[CLASS_World::GetMapCell(X-1,Y)]!=0 && CLASS_World::Map[CLASS_World::GetMapCell(X-1,Y)]<200)
   {
    CLASS_World::Check[CLASS_World::GetMapCell(X-1,Y)]=255;
   }
   else
   { 
    return false;
   }
  }
  if (Y+1!=CLASS_World::MapSize-1)
  {
   if (CLASS_World::Map[CLASS_World::GetMapCell(X,Y+1)]==0 || CLASS_World::Map[CLASS_World::GetMapCell(X,Y+1)]>=200)
   {
    if (CLASS_World::Check[CLASS_World::GetMapCell(X,Y+1)]==0)
    {
     CLASS_World::Add(X,Y+1);
     CLASS_World::Check[CLASS_World::GetMapCell(X,Y+1)]=1;
    }
   }
   else
   {
    CLASS_World::Check[CLASS_World::GetMapCell(X,Y+1)]=255;
   }
  }
  else
  {
   if (CLASS_World::Map[CLASS_World::GetMapCell(X,Y+1)]!=0 && CLASS_World::Map[CLASS_World::GetMapCell(X,Y+1)]<200)
   {
    CLASS_World::Check[CLASS_World::GetMapCell(X,Y+1)]=255;
   }
   else
   { 
    return false;
   }
  }
  if (X+1!=CLASS_World::MapSize-1)
  {
   if (CLASS_World::Map[CLASS_World::GetMapCell(X+1,Y)]==0 || CLASS_World::Map[CLASS_World::GetMapCell(X+1,Y)]>=200)
   {
    if (CLASS_World::Check[CLASS_World::GetMapCell(X+1,Y)]==0)
    {
     CLASS_World::Add(X+1,Y);
     CLASS_World::Check[CLASS_World::GetMapCell(X+1,Y)]=1;
    }
   }
   else
   {
    CLASS_World::Check[CLASS_World::GetMapCell(X+1,Y)]=255;
   }
  }
  else
  {
   if (CLASS_World::Map[CLASS_World::GetMapCell(X+1,Y)]!=0 && CLASS_World::Map[CLASS_World::GetMapCell(X+1,Y)]<200)
   {
    CLASS_World::Check[CLASS_World::GetMapCell(X+1,Y)]=255;
   }
   else
   { 
    return false;
   }
  }
  if (CLASS_World::Check[CLASS_World::GetMapCell(X,Y-1)]==1)
  {
   CLASS_World::Del(X,Y);
   Y--;
  }
  else
  {
   if (CLASS_World::Check[CLASS_World::GetMapCell(X-1,Y)]==1)
   {
    CLASS_World::Del(X,Y);
    X--;
   }
   else
   {
    if (CLASS_World::Check[CLASS_World::GetMapCell(X,Y+1)]==1)
    {
     CLASS_World::Del(X,Y);
     Y++;
    }
    else
    {
     if (CLASS_World::Check[CLASS_World::GetMapCell(X+1,Y)]==1)
     {
      CLASS_World::Del(X,Y);
      X++;
     }
     else
     {
      CLASS_World::Del(X,Y);
      if (CLASS_World::Stack.size()==0)
      {
       Done=true;
      }
      else
      {
       X=CLASS_World::Stack[0].X;
       Y=CLASS_World::Stack[0].Y;
      }
     }
    }
   }
  }
 }
 return true;
}

//eof

















































