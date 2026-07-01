#ifndef MERK_Polygon
#define MERK_Polygon

class CLASS_Polygon
{
 public:
  int OffsBl,OffsPx,MinAtlas,MaxAtlas,CurAtlas,CurTex;
  SDL_Rect Src,Dst;
  void Assign(int MaxAtlas,int OffsPx);
};

#endif

















































