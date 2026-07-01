#include <vector>
#include <SDL/SDL.h>
#include <MERK/MERK_Math.h>
#include <MERK/MERK_Screen.h>

void CLASS_Screen::Assign(int Width,int Height,double HalfFov)
{
 CLASS_Screen::Width=Width;
 CLASS_Screen::Dist.resize(CLASS_Screen::Width);
 CLASS_Screen::Height=Height;
 CLASS_Screen::HalfWidth=CLASS_Screen::Width/2;
 CLASS_Screen::HalfHeight=CLASS_Screen::Height/2;
 CLASS_Screen::Plane=int(CLASS_Screen::HalfWidth/Math.Tan(HalfFov));
 CLASS_Screen::HUD={0,0,CLASS_Screen::Width,80};
 CLASS_Screen::MaxHeight=CLASS_Screen::Height-CLASS_Screen::HUD.h;
 CLASS_Screen::MaxHalfHeight=CLASS_Screen::MaxHeight/2;
 CLASS_Screen::HUD={0,400,CLASS_Screen::HUD.w,CLASS_Screen::HUD.h};
 CLASS_Screen::Face={321,421,72,52};
 CLASS_Screen::Tool={546,421,72,52};
 CLASS_Screen::Health={440,431,16,32};
 CLASS_Screen::Hand={256,16,384,384};
 CLASS_Screen::UpPart={0,0,CLASS_Screen::Width,CLASS_Screen::MaxHalfHeight};
 CLASS_Screen::DnPart={0,CLASS_Screen::MaxHalfHeight+1,CLASS_Screen::Width,CLASS_Screen::MaxHalfHeight};
}

//eof

















































