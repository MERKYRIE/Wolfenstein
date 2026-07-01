#ifndef MERK_Math
#define MERK_Math

class CLASS_Math
{
 public:
  double DgrToRdn=0.01745329251994329576923690768489;
  double RdnToDgr=57.295779513082320876798154814105;
  double Sin(double Angle);
  double Cos(double Angle);
  double Tan(double Angle);
  double ASin(double Angle);
  double ACos(double Angle);
  double ATan(double Angle);
  double TenShift(double Num,int Ext);
  double CutReal(double Num,int Acc);
};

extern CLASS_Math Math;

#endif

















































