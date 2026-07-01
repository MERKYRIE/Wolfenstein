#include <MERK/MERK_Ray.h>

void CLASS_Ray::Assign(double HalfFov,int HalfWidth)
{
 CLASS_Ray::ExtAngle=HalfFov/double(HalfWidth);
 CLASS_Ray::MinAngle=CLASS_Ray::ExtAngle;
 CLASS_Ray::MaxAngle=360;
}

//eof

















































