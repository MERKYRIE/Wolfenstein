#ifndef MERK_Screen
#define MERK_Screen

class CLASS_Screen
{
 public:
  typedef std::vector <double> TYPE_Dist;
  TYPE_Dist Dist;
  int Width,HalfWidth,Height,HalfHeight,MaxHeight,MaxHalfHeight,Plane;
  SDL_Rect UpPart,DnPart,HUD,Face,Tool,Health,Hand;
  void Assign(int Width,int Height,double HalfFov);
};

#endif

















































