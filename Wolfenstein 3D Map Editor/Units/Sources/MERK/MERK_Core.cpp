#pragma comment (lib,"SDL/SDL2main")
#pragma comment (lib,"SDL/SDL2test")
#pragma comment (lib,"SDL/SDL2")
#pragma comment (lib,"SDL_ttf/SDL2_ttf")

#include <vector>
#include <SDL/SDL.h>
#include <SDL_ttf/SDL_ttf.h>
#include <MERK/MERK_Graph.h>
#include <MERK/MERK_Misc.h>
#include <MERK/MERK_Polygon.h>
#include <MERK/MERK_Screen.h> 
#include <MERK/MERK_Text.h>
#include <MERK/MERK_User.h>
#include <MERK/MERK_World.h>
#include <MERK/MERK_Core.h>

CLASS_Core Core;
CLASS_Graph Graph;
//CLASS_Misc//ADDITIONAL MODULE
CLASS_Polygon Polygon;
CLASS_Screen Screen;
CLASS_Text Text;
CLASS_User User;
CLASS_World World;

void CLASS_Core::Assign()
{
 Screen.Assign(640,480);//No addiction
 World.Assign(64,Screen.Height,1);//Screen addiction
 Text.Init("Graphics/Fonts/Arial.ttf",12,20);//No addiction
 User.Assign(1,Screen.Height,World.Block);//Screen and World addiction
 Graph.Init(
            "Wolfenstein 3D",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            Screen.Width,
            Screen.Height,
            SDL_WINDOW_SHOWN
            //|SDL_WINDOW_FULLSCREEN
            ,
            SDL_RENDERER_ACCELERATED
            |SDL_RENDERER_PRESENTVSYNC
            ,
            SDL_DISABLE
           );//Screen addiction
}

void CLASS_Core::Load()
{
 Graph.LoadAtlas("Graphics/Atlases/BJ.bmp",1);
 Graph.LoadAtlas("Graphics/Atlases/Walls.bmp",49); 
 Graph.LoadAtlas("Graphics/Atlases/Mechanisms.bmp",6);
 Graph.LoadAtlas("Graphics/Atlases/Objects.bmp",50);
 Polygon.Assign(Graph.GetAtlasCnt(),64);
}

void CLASS_Core::Init()
{
 Core.Assign();
 Core.Load();
}

void CLASS_Core::Destroy()
{
 Text.Destroy();
 Graph.Destroy();
}

void CLASS_Core::FillScreen()
{
 SDL_SetRenderDrawColor(Graph.Renderer,0,0,0,255);
 SDL_RenderClear(Graph.Renderer);
}

void CLASS_Core::FlipBuffer()
{
 SDL_RenderPresent(Graph.Renderer);
}

void CLASS_Core::DrawMap()
{
 int X,Y,XMin,YMin,XMax,YMax;
 XMin=World.X;
 XMax=World.X+User.MaxBl;
 YMin=World.Y;
 YMax=World.Y+User.MaxBl;
 for (X=XMin;X<=XMax;X++)
 {
  for (Y=YMin;Y<=YMax;Y++)
  {
   if ((Polygon.Src.y=World.Map[World.GetMapCell(X,Y)])!=0)
   {
    Polygon.Dst.x=(X-World.X)*World.Block;
	   Polygon.Dst.y=(Y-World.Y)*World.Block;
    if (Polygon.Src.y!=255)
	   {
     if (Polygon.Src.y<100)
     {
      Polygon.Src.y*=Polygon.OffsPx;
   	  SDL_RenderCopy(Graph.Renderer,Graph.Atlas[2].Data,&Polygon.Src,&Polygon.Dst);
     }
     else
     {
      if (Polygon.Src.y<200)
      {
       Polygon.Src.y-=100;
       Polygon.Src.y*=Polygon.OffsPx;
   	   SDL_RenderCopy(Graph.Renderer,Graph.Atlas[3].Data,&Polygon.Src,&Polygon.Dst);
      }
      else
      {
       Polygon.Src.y-=200;
       Polygon.Src.y*=Polygon.OffsPx;
   	   SDL_RenderCopy(Graph.Renderer,Graph.Atlas[4].Data,&Polygon.Src,&Polygon.Dst);
      }
     }
   	}
	   else
	   {
   	 SDL_RenderCopy(Graph.Renderer,Graph.Atlas[1].Data,NULL,&Polygon.Dst);
	   }
   }
  }
 }
}

void CLASS_Core::DrawCursor()
{
 Polygon.Dst.x=User.X*World.Block;
 Polygon.Dst.y=User.Y*World.Block;
 SDL_SetRenderDrawColor(Graph.Renderer,255,255,255,255);
 SDL_RenderDrawRect(Graph.Renderer,&Polygon.Dst);
}

void CLASS_Core::DrawBorder()
{
 SDL_SetRenderDrawColor(Graph.Renderer,255,255,255,255);
 SDL_RenderDrawLine(Graph.Renderer,User.MaxPx,0,User.MaxPx,Screen.Height-1);
 SDL_RenderDrawLine(Graph.Renderer,0,User.MaxPx,Screen.Width-1,User.MaxPx);
}

void CLASS_Core::OutInfo()
{
 Text.SetColor(255,255,255);
 Text.Out("F1-help",500,455,Graph.Renderer);
 Polygon.Src.y=Polygon.CurTex*Polygon.OffsPx;
 Text.OutNum("WorldX=",World.X,500,20,Graph.Renderer);
 Text.OutNum("WorldY=",World.Y,500,40,Graph.Renderer);
 Text.OutNum("UserX=",User.X,500,60,Graph.Renderer);
 Text.OutNum("UserY=",User.Y,500,80,Graph.Renderer);
 World.TotalX=World.X+User.X;
 World.TotalY=World.Y+User.Y;
 Text.OutNum("TotalX=",World.TotalX,500,100,Graph.Renderer);
 Text.OutNum("TotalY=",World.TotalY,500,120,Graph.Renderer);
 Text.OutNum("CurAtlas=",Polygon.CurAtlas,500,140,Graph.Renderer);
 Text.OutNum("CurTex=",Polygon.CurTex,500,160,Graph.Renderer);
 Polygon.Dst.x=500;
 Polygon.Dst.y=200;
 SDL_RenderCopy(Graph.Renderer,Graph.Atlas[Polygon.CurAtlas].Data,&Polygon.Src,&Polygon.Dst);
}

void CLASS_Core::Draw()
{                              
 Core.DrawMap();
 Core.DrawCursor();
 Core.DrawBorder();
	Core.OutInfo();
}

void CLASS_Core::UpdateState()
{
 SDL_PollEvent(&Graph.Event);
 Graph.Keys=SDL_GetKeyboardState(NULL);
}

int CLASS_Core::CheckEscape()
{
 if (Graph.Keys[SDL_SCANCODE_ESCAPE])
 {
  return 1;
 }
 return 0;
}

void CLASS_Core::CheckSpace()
{
 if (Graph.Event.key.keysym.sym==SDLK_SPACE)
 {
  if (World.Map[World.GetMapCell(World.TotalX,World.TotalY)]==0)
  {
   switch (Polygon.CurAtlas)
   {
    case 2:
     World.Map[World.GetMapCell(World.TotalX,World.TotalY)]=Polygon.CurTex;
     break;
    case 3:
     World.Map[World.GetMapCell(World.TotalX,World.TotalY)]=Polygon.CurTex+100;
     break;
    case 4:
     World.Map[World.GetMapCell(World.TotalX,World.TotalY)]=Polygon.CurTex+200;
     break;
   }
  }
  else
  {
   Misc.ShowError("Can't write the cell","The cell is already filled",Graph.Renderer,Graph.Event);
  }
 }
}

void CLASS_Core::CheckTab()
{
 if (Graph.Event.key.keysym.sym==SDLK_TAB)
 {
  World.Map[World.GetMapCell(World.TotalX,World.TotalY)]=0;
 }
}

void CLASS_Core::CheckAlt()
{
 static int AltCoef=3,AltCnt=AltCoef;
 if (Graph.Event.key.keysym.sym==SDLK_LALT)
 {
  if (AltCnt==0)
  {
   if (World.Map[World.GetMapCell(World.TotalX,World.TotalY)]==0)
   {
    if (World.Map[World.GetMapCell(World.StartX/World.Block,World.StartY/World.Block)]==255)
    {
   	 World.Map[World.GetMapCell(World.StartX/World.Block,World.StartY/World.Block)]=0;
    }
    World.StartX=(World.TotalX)*World.Block+World.HalfBlock;
    World.StartY=(World.TotalY)*World.Block+World.HalfBlock;
    World.Map[World.GetMapCell(World.TotalX,World.TotalY)]=255;
   }
   else
   {
    Misc.ShowError("Can't write the cell","The cell is already filled",Graph.Renderer,Graph.Event);
   }
   AltCnt=AltCoef;
  }
  else
  {
   AltCnt--;
  }
 }
 else
 {
  AltCnt=AltCoef;
 }
}

void CLASS_Core::CheckF1()
{
 if (Graph.Event.key.keysym.sym==SDLK_F1)
 {                                        
  Misc.ShowHelp(Graph.Renderer,Graph.Event);
 }
}

void CLASS_Core::FillBase(unsigned char Num,int XCnt,int YCnt)
{
 int X,Y,XMin,YMin,XMax,YMax;
 XMin=XCnt*World.Block;
 XMax=XMin+World.Block;
 YMin=YCnt*World.Block;
 YMax=YMin+World.Block;
 for (X=XMin;X<XMax;X++)
 {
  for (Y=YMin;Y<YMax;Y++)
  {
   World.Bar[World.GetBarCell(X,Y)]=Num;
  }
 }
}

void CLASS_Core::FillUp(unsigned char Num,int XCnt,int YCnt)
{
 int X,Y,XMin,YMin,XMax,YMax;
 if (YCnt!=World.MinBl)
 {
  if (YCnt-World.BarSizeBl-1>=World.MinBl)
  {
   XMin=XCnt*World.Block;
   XMax=XMin+World.Block;
   YMin=YCnt*World.Block-World.BarSizePx;
   YMax=YMin+World.BarSizePx;
   for (X=XMin;X<XMax;X++)
   {
    for (Y=YMin;Y<YMax;Y++)
    {
     World.Bar[World.GetBarCell(X,Y)]=Num;
    }
   }
  }
 }
}

void CLASS_Core::FillUpLeft(unsigned char Num,int XCnt,int YCnt)
{
 int X,Y,XMin,YMin,XMax,YMax;
 if (YCnt!=World.MinBl && XCnt!=World.MinBl)
 {
  if (YCnt-World.BarSizeBl-1>=World.MinBl && XCnt-World.BarSizeBl-1>=World.MinBl)
  {
   XMin=XCnt*World.Block-World.BarSizePx;
   XMax=XMin+World.BarSizePx;
   YMin=YCnt*World.Block-World.BarSizePx;
   YMax=YMin+World.BarSizePx;
   for (X=XMin;X<XMax;X++)
   {
    for (Y=YMin;Y<YMax;Y++)
    {
     World.Bar[World.GetBarCell(X,Y)]=Num;
    }
   }
  }
 }
}

void CLASS_Core::FillLeft(unsigned char Num,int XCnt,int YCnt)
{
 int X,Y,XMin,YMin,XMax,YMax;
 if (XCnt!=World.MinBl)
 {
  if (XCnt-World.BarSizeBl-1>=World.MinBl)
  {
   YMin=YCnt*World.Block;
   YMax=YMin+World.Block;
   XMin=XCnt*World.Block-World.BarSizePx;
   XMax=XMin+World.BarSizePx;
   for (X=XMin;X<XMax;X++)
   {
    for (Y=YMin;Y<YMax;Y++)
    {
     World.Bar[World.GetBarCell(X,Y)]=Num;
    }
   }
  }
 }
}

void CLASS_Core::FillDownLeft(unsigned char Num,int XCnt,int YCnt)
{
 int X,Y,XMin,YMin,XMax,YMax;
 if (XCnt!=World.MinBl && YCnt!=World.MapSize)
 {
  if (XCnt-World.BarSizeBl-1>=World.MinBl && YCnt+World.BarSizeBl+1<World.MapSize)
  {
   YMin=YCnt*World.Block+World.Block;
   YMax=YMin+World.BarSizePx;
   XMin=XCnt*World.Block-World.BarSizePx;
   XMax=XMin+World.BarSizePx;
   for (X=XMin;X<XMax;X++)
   {
    for (Y=YMin;Y<YMax;Y++)
    {
     World.Bar[World.GetBarCell(X,Y)]=Num;
    }
   }
  }
 }
}

void CLASS_Core::FillDown(unsigned char Num,int XCnt,int YCnt)
{
 int X,Y,XMin,YMin,XMax,YMax;
 if (YCnt!=World.MapSize)
 {
  if (YCnt+World.BarSizeBl+1<World.MapSize)
  {
   XMin=XCnt*World.Block;
   XMax=XMin+World.Block;
   YMin=YCnt*World.Block+World.Block;
   YMax=YMin+World.BarSizePx;
   for (X=XMin;X<XMax;X++)
   {
    for (Y=YMin;Y<YMax;Y++)
    {
     World.Bar[World.GetBarCell(X,Y)]=Num;
    }
   }
  }
 }
}

void CLASS_Core::FillDownRight(unsigned char Num,int XCnt,int YCnt)
{
 int X,Y,XMin,YMin,XMax,YMax;
 if (YCnt!=World.MapSize && XCnt!=World.MapSize)
 {
  if (YCnt+World.BarSizeBl+1<World.MapSize && XCnt+World.BarSizeBl+1<World.MapSize)
  {
   XMin=XCnt*World.Block+World.Block;
   XMax=XMin+World.BarSizePx;
   YMin=YCnt*World.Block+World.Block;
   YMax=YMin+World.BarSizePx;
   for (X=XMin;X<XMax;X++)
   {
    for (Y=YMin;Y<YMax;Y++)
    {
     World.Bar[World.GetBarCell(X,Y)]=Num;
    }
   }
  }
 }
}

void CLASS_Core::FillRight(unsigned char Num,int XCnt,int YCnt)
{
 int X,Y,XMin,YMin,XMax,YMax;
 if (XCnt!=World.MapSize)
 {
  if (XCnt+World.BarSizeBl+1<World.MapSize)
  {
   YMin=YCnt*World.Block;
   YMax=YMin+World.Block;
   XMin=XCnt*World.Block+World.Block;
   XMax=XMin+World.BarSizePx;
   for (X=XMin;X<XMax;X++)
   {
    for (Y=YMin;Y<YMax;Y++)
    {
     World.Bar[World.GetBarCell(X,Y)]=Num;
    }
   }
  }
 }
}

void CLASS_Core::FillUpRight(unsigned char Num,int XCnt,int YCnt)
{
 int X,Y,XMin,YMin,XMax,YMax;
 if (XCnt!=World.MapSize && YCnt!=World.MinBl)
 {
  if (XCnt+World.BarSizeBl+1<World.MapSize && YCnt-World.BarSizeBl-1>=World.MinBl)
  {
   YMin=YCnt*World.Block-World.BarSizePx;
   YMax=YMin+World.BarSizePx;
   XMin=XCnt*World.Block+World.Block;
   XMax=XMin+World.BarSizePx;
   for (X=XMin;X<XMax;X++)
   {
    for (Y=YMin;Y<YMax;Y++)
    {
     World.Bar[World.GetBarCell(X,Y)]=Num;
    }
   }
  }
 }
}

void CLASS_Core::FillBar(unsigned char Num)
{
 int XCnt,YCnt;
 for (XCnt=World.MinBl;XCnt<World.MapSize;XCnt++)
 {
  for (YCnt=World.MinBl;YCnt<World.MapSize;YCnt++)
  {
   if (World.Map[World.GetMapCell(XCnt,YCnt)]!=0)
   {
    Core.FillBase(Num,XCnt,YCnt);
    Core.FillUp(Num,XCnt,YCnt);
    Core.FillUpLeft(Num,XCnt,YCnt);
    Core.FillLeft(Num,XCnt,YCnt);
    Core.FillDownLeft(Num,XCnt,YCnt);
    Core.FillDown(Num,XCnt,YCnt);
    Core.FillDownRight(Num,XCnt,YCnt);
    Core.FillRight(Num,XCnt,YCnt);
    Core.FillUpRight(Num,XCnt,YCnt);
   }
  }
 }
}

void CLASS_Core::FillMech()
{
 int X,Y;
 World.Mech.clear();
 for (X=World.MinBl;X<World.MapSize;X++)
 {
  for (Y=World.MinBl;Y<World.MapSize;Y++)
  {
   if (World.Map[World.GetMapCell(X,Y)]>=100 && World.Map[World.GetMapCell(X,Y)]<200)
   {
    World.Mech.resize(World.Mech.size()+1);
    World.Mech[World.Mech.size()-1].X=X;
    World.Mech[World.Mech.size()-1].Y=Y;
   }
  }
 }  
}

void CLASS_Core::CheckF2()
{
 if (Graph.Event.key.keysym.sym==SDLK_F2)
 {
		if (World.StartX<World.MinPx ||
      World.StartY<World.MinPx ||
      World.StartX>World.MaxPx || 
      World.StartY>World.MaxPx || 
      World.Bar[World.GetBarCell(World.StartX,World.StartY)]==1 || 
      !World.IsMapClosed())
		{
			Misc.ShowError("Can't save the map","The starting coordinate is invalid",Graph.Renderer,Graph.Event);
		}
		else
		{
   World.Map[World.GetMapCell(World.StartX/World.Block,World.StartY/World.Block)]=0;
   Core.FillBar(1);
   Core.FillMech();
   Misc.SaveMap(World.Name,World.MapSize,World.StartX,World.StartY,World.Map,World.Bar,World.Mech);
   Core.FillBar(0);
   World.Map[World.GetMapCell(World.StartX/World.Block,World.StartY/World.Block)]=255;
   Misc.ShowSuccess("Map is successfully saved",Graph.Renderer,Graph.Event);
  }
	}
}

void CLASS_Core::CheckUp()
{
 static int ArrowCoef=5,ArrowCnt=ArrowCoef;
 if (Graph.Event.key.keysym.sym==SDLK_UP)
 {
  if (ArrowCnt==0)
  {
   if (Polygon.CurTex!=0)
   {
   	Polygon.CurTex-=Polygon.OffsBl;
   }
   ArrowCnt=ArrowCoef;
  }
  else
  {
   ArrowCnt--;
  }
 }
 else
 {
  ArrowCnt=ArrowCoef;
 }
}

void CLASS_Core::CheckLeft()
{
 static int ArrowCoef=5,ArrowCnt=ArrowCoef;
 if (Graph.Event.key.keysym.sym==SDLK_LEFT)
 {
  if (ArrowCnt==0)
  {
   if (Polygon.CurAtlas!=Polygon.MinAtlas)
   {
   	Polygon.CurAtlas-=Polygon.OffsBl;
    Polygon.CurTex=0;
   }
   ArrowCnt=ArrowCoef;
  }
  else
  {
   ArrowCnt--;
  }
 }
 else
 {
  ArrowCnt=ArrowCoef;
 }
}

void CLASS_Core::CheckDown()
{
 static int ArrowCoef=5,ArrowCnt=ArrowCoef;
 if (Graph.Event.key.keysym.sym==SDLK_DOWN)
 {
  if (ArrowCnt==0)
  {
   if (Polygon.CurTex!=Graph.Atlas[Polygon.CurAtlas].MaxTex)
   {
   	Polygon.CurTex+=Polygon.OffsBl;
   }
   ArrowCnt=ArrowCoef;
  }
  else
  {
   ArrowCnt--;
  }
 }
 else
 {
  ArrowCnt=ArrowCoef;
 }
}

void CLASS_Core::CheckRight()
{
 static int ArrowCoef=5,ArrowCnt=ArrowCoef;
 if (Graph.Event.key.keysym.sym==SDLK_RIGHT)
 {
  if (ArrowCnt==0)
  {
   if (Polygon.CurAtlas!=Polygon.MaxAtlas)
   {
   	Polygon.CurAtlas+=Polygon.OffsBl;
    Polygon.CurTex=0;
   }
   ArrowCnt=ArrowCoef;
  }
  else
  {
   ArrowCnt--;
  }
 }
 else
 {
  ArrowCnt=ArrowCoef;
 }
}

void CLASS_Core::CheckW()
{
 if (Graph.Event.key.keysym.sym==SDLK_w)
 {
  if (World.Y==World.MinBl)
  {
   if (User.Y!=0)
   {
    User.Y-=User.MovSpd;
   }
  }
  else
  {
   if (User.Y==0)
   {
    World.Y-=World.Offs;
   }
   else
   {
   	User.Y-=User.MovSpd;
   }
  }
 }
}

void CLASS_Core::CheckA()
{
 if (Graph.Event.key.keysym.sym==SDLK_a)
 {							  
  if (World.X==World.MinBl)
  {
   if (User.X!=0)
   {
    User.X-=User.MovSpd;
   }
  }
  else
  {
   if (User.X==0)
   {
    World.X-=World.Offs;
   }
   else
   {
    User.X-=User.MovSpd;
   }
  }
 }
}

void CLASS_Core::CheckS()
{
 if (Graph.Event.key.keysym.sym==SDLK_s)
 {
  if (World.Y==World.MaxBl)
  {
   if (User.Y!=User.MaxBl)
   {
    User.Y+=User.MovSpd;
   }
  }
  else
  {
   if (User.Y==User.MaxBl)
   {
    World.Y+=World.Offs;
   }
   else
   {
    User.Y+=User.MovSpd;
   }
  }
 }
}

void CLASS_Core::CheckD()
{
 if (Graph.Event.key.keysym.sym==SDLK_d)
 {
  if (World.X==World.MaxBl)
  {
   if (User.X!=User.MaxBl)
   {
    User.X+=User.MovSpd;
   }
  }
  else
  {
   if (User.X==User.MaxBl)
   {
    World.X+=World.Offs;
   }
   else
   {
    User.X+=User.MovSpd;
   }
  }
 }
}

int CLASS_Core::DetectKey()
{
 Core.UpdateState();
 if (Core.CheckEscape())
 {
  return 1;
 }
 if (Graph.Event.type==SDL_KEYDOWN)
 {
  Core.CheckSpace();
  Core.CheckTab();
  Core.CheckAlt();
  Core.CheckF1();
  Core.CheckF2();
  Core.CheckUp();
  Core.CheckLeft();
  Core.CheckDown(); 
  Core.CheckRight(); 
  Core.CheckW();
  Core.CheckA();
  Core.CheckS();
  Core.CheckD();
 }
 return 0;
}

//eof

















































