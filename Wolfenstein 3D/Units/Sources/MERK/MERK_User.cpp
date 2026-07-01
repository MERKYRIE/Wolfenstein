#include <MERK/MERK_User.h>

void CLASS_User::NON_Assign(double X,double Y,double Fov,double Pov,double MovSpd)
{
 CLASS_User::X=X;
 CLASS_User::Y=Y;
 CLASS_User::Fov=Fov;
 CLASS_User::HalfFov=CLASS_User::Fov/2;
 CLASS_User::Pov=Pov;
 CLASS_User::MovSpd=MovSpd;
 CLASS_User::Tool=0;
 CLASS_User::Face=0;
 CLASS_User::Health=100;
 CLASS_User::HandPhase=0;
 CLASS_User::StepPhase=0;
 CLASS_User::WerewolfPhase=0;
}

void CLASS_User::ADD_Assign(int HalfWidth,double ExtAngle)
{
 CLASS_User::MouseX=HalfWidth;
 CLASS_User::RotSpd=ExtAngle;
}

//eof

















































