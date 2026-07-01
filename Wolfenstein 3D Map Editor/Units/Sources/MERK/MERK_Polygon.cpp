#include <SDL/SDL.h>
#include <MERK/MERK_Polygon.h>

void CLASS_Polygon::Assign(int MaxAtlas,int OffsPx)
{
 CLASS_Polygon::OffsBl=1;
 CLASS_Polygon::OffsPx=OffsPx;
 CLASS_Polygon::MinAtlas=2;
 CLASS_Polygon::MaxAtlas=MaxAtlas;
 CLASS_Polygon::CurAtlas=CLASS_Polygon::MinAtlas;
 CLASS_Polygon::CurTex=0;
 CLASS_Polygon::Src.x=0;
 CLASS_Polygon::Src.y=0;
 CLASS_Polygon::Src.w=CLASS_Polygon::OffsPx;
 CLASS_Polygon::Src.h=CLASS_Polygon::OffsPx;
 CLASS_Polygon::Dst.w=CLASS_Polygon::OffsPx;
 CLASS_Polygon::Dst.h=CLASS_Polygon::OffsPx;
}

//eof

















































