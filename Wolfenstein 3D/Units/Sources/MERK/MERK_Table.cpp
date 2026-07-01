#include <vector>
#include <MERK/MERK_Math.h>
#include <MERK/MERK_Table.h>

void CLASS_Table::Assign(double MinAngle,double MaxAngle)
{
 CLASS_Table::ExtAngle=MinAngle;
 int Mnt,Cnt;
 double CurAngle;
 bool Done;
 Mnt=int(MaxAngle/MinAngle)+1;
 CLASS_Table::Sin.resize(Mnt);
 CLASS_Table::Cos.resize(Mnt);
 CLASS_Table::Tan.resize(Mnt);
 Cnt=1;
 CurAngle=MinAngle;
 Done=false;
 while (!Done)
 {
  CLASS_Table::Sin[Cnt]=Math.Sin(CurAngle);
  CLASS_Table::Cos[Cnt]=Math.Cos(CurAngle);
  CLASS_Table::Tan[Cnt]=Math.Tan(CurAngle);
  CLASS_Table::Sin[Cnt]=Math.CutReal(CLASS_Table::Sin[Cnt],4);
  CLASS_Table::Cos[Cnt]=Math.CutReal(CLASS_Table::Cos[Cnt],4);
  CLASS_Table::Tan[Cnt]=Math.CutReal(CLASS_Table::Tan[Cnt],4);
  if (CurAngle+MinAngle<=MaxAngle)
  {
   Cnt++;
   CurAngle+=MinAngle;
  }
  else 
  {
   Done=true;
  }
 }
}

double CLASS_Table::GetSin(double Angle)
{
 if (Angle!=0)
 {
  return CLASS_Table::Sin[int(abs(Angle/CLASS_Table::ExtAngle))];
 }
 else
 {
  return 0;
 }
}

double CLASS_Table::GetCos(double Angle)
{
 if (Angle!=0)
 {
  return CLASS_Table::Cos[int(abs(Angle/CLASS_Table::ExtAngle))];
 }
 else
 {
  return 1;
 }
}

double CLASS_Table::GetTan(double Angle)
{
 if (Angle!=0)
 {
  return CLASS_Table::Tan[int(abs(Angle/CLASS_Table::ExtAngle))];
 }
 else
 {
  return 0;
 }
}

//eof

















































