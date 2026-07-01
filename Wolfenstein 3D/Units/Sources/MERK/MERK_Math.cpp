#include <iostream>
#include <MERK/MERK_Math.h>

CLASS_Math Math;

double CLASS_Math::Sin(double Angle)
{
 return sin(Angle*CLASS_Math::DgrToRdn);
}

double CLASS_Math::Cos(double Angle)
{
 return cos(Angle*CLASS_Math::DgrToRdn);
}

double CLASS_Math::Tan(double Angle)
{
 return tan(Angle*CLASS_Math::DgrToRdn);
}

double CLASS_Math::ASin(double Angle)
{
 return asin(Angle)*CLASS_Math::RdnToDgr;
}

double CLASS_Math::ACos(double Angle)
{
 return acos(Angle)*CLASS_Math::RdnToDgr;
}

double CLASS_Math::ATan(double Angle)
{
 return atan(Angle)*CLASS_Math::RdnToDgr;
}

double CLASS_Math::TenShift(double Num,int Ext)
{
 int Cnt;
 if (Ext>0)
 {
  for (Cnt=1;Cnt<Ext;Cnt++)
  {
   Num*=10;
  }
 }
 else 
 {
  for (Cnt=Ext;Cnt<-1;Cnt++)
  {
   Num/=10;
  }
 }
 return Num;
}

double CLASS_Math::CutReal(double Num,int Acc)
{
 Num=Num*Math.TenShift(10,Acc);
 Num=int(Num);
 Num=Num/Math.TenShift(10,Acc);
 if (Num==0)
 {
  Num=Math.TenShift(0.1,-Acc);
 }
 return Num;
}

//eof

















































