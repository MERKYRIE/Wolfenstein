#ifndef MERK_User
#define MERK_User

class CLASS_User
{
 public:
  int MouseX,Tool,Face,Health,HandPhase,StepPhase,WerewolfPhase;
  double X,Y,Fov,HalfFov,Pov,PovSide,MovSpd,RotSpd;
  void NON_Assign(double X,double Y,double Fov,double Pov,double MovSpd);
  void ADD_Assign(int HalfWidth,double ExtAngle);
};

#endif

















































