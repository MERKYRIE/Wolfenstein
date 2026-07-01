#ifndef MERK_Ray
#define MERK_Ray

class CLASS_Ray
{
 public:
  double MinAngle,MaxAngle,CurAngle,ExtAngle,VerX,HorX,VerY,HorY,VerStepX,HorStepX,VerStepY,HorStepY,VerDist,HorDist,Dist,DirectDist;
  bool VerError,HorError;
  void Assign(double HalfFov,int HalfWidth);
};

#endif

















































