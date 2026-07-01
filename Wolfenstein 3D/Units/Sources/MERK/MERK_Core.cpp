#pragma comment (lib,"SDL/SDL2main")
#pragma comment (lib,"SDL/SDL2test")
#pragma comment (lib,"SDL/SDL2")
#pragma comment (lib,"SDL_mixer/SDL2_mixer")    

#include <iostream>
#include <vector>
#include <SDL/SDL.h>
#include <SDL_mixer/SDL_mixer.h>
#include <MERK/MERK_Audio.h>
#include <MERK/MERK_Column.h>
#include <MERK/MERK_Graph.h>
#include <MERK/MERK_Math.h>
#include <MERK/MERK_Misc.h>
#include <MERK/MERK_Ray.h>
#include <MERK/MERK_Screen.h>
#include <MERK/MERK_Table.h>
#include <MERK/MERK_User.h>
#include <MERK/MERK_World.h>
#include <MERK/MERK_Core.h>

CLASS_Audio Audio;
CLASS_Column Column;
CLASS_Core Core;
CLASS_Graph Graph;
//CLASS_Math//ADDITIONAL MODULE
//CLASS_Misc//ADDITIONAL MODULE
CLASS_Ray Ray;
CLASS_Screen Screen;
CLASS_Table Table;
CLASS_User User;
CLASS_World World;

void CLASS_Core::Bind()
{
 World.Assign(64);//No addiction
 User.NON_Assign(World.StartX,World.StartY,60,90,5);//World addiction
 Screen.Assign(640,480,User.HalfFov);//User_NON addiction
 Ray.Assign(User.HalfFov,Screen.HalfWidth);//User_NON and Screen addiction
 Table.Assign(Ray.MinAngle,Ray.MaxAngle);//Ray addiction
 User.ADD_Assign(Screen.HalfWidth,Ray.ExtAngle);//Screen and Ray addiction
 Column.Assign(World.Block,Screen.Plane,Screen.HalfWidth,User.HalfFov,64);//World,Screen and User_NON addiction
 Graph.Init(
            "Wolfenstein 3D",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            Screen.Width,
            Screen.Height,
            SDL_WINDOW_SHOWN
            |SDL_WINDOW_FULLSCREEN
            ,
            SDL_RENDERER_ACCELERATED
            |SDL_RENDERER_PRESENTVSYNC
            ,
            SDL_DISABLE
           );//Screen addiction
 Audio.Init();
}

void CLASS_Core::Load()
{
 //Atlases
 Core.HUD=Graph.LoadAtlas("Graphics/Atlases/HUD.bmp");
 Core.Faces=Graph.LoadAtlas("Graphics/Atlases/Faces.bmp");
 Core.Tools=Graph.LoadAtlas("Graphics/Atlases/Tools.bmp");
 Core.Numbers=Graph.LoadAtlas("Graphics/Atlases/Numbers.bmp");
 Core.Hands=Graph.LoadAtlas("Graphics/Atlases/Hands.bmp");
 Core.Walls=Graph.LoadAtlas("Graphics/Atlases/Walls.bmp");
 Core.Mechs=Graph.LoadAtlas("Graphics/Atlases/Mechanisms.bmp");
 Core.Objects=Graph.LoadAtlas("Graphics/Atlases/Objects.bmp");
 //Music
 Core.E1M1=Audio.LoadMusic("Audio/Music/E1M1.mp3");
 //Sounds
 Core.Step[0]=Audio.LoadSound("Audio/Sounds/Step_1.wav");
 Core.Step[1]=Audio.LoadSound("Audio/Sounds/Step_2.wav");
 Core.Step[2]=Audio.LoadSound("Audio/Sounds/Step_3.wav");
 Core.Step[3]=Audio.LoadSound("Audio/Sounds/Step_4.wav");
 Core.Select=Audio.LoadSound("Audio/Sounds/Select.wav");
 Core.Fist=Audio.LoadSound("Audio/Sounds/Fist.wav");
 Core.Werewolf[0]=Audio.LoadSound("Audio/Sounds/Werewolf_1.wav");
 Core.Werewolf[1]=Audio.LoadSound("Audio/Sounds/Werewolf_2.wav");
 Core.Werewolf[2]=Audio.LoadSound("Audio/Sounds/Werewolf_3.wav");
 Core.Werewolf[3]=Audio.LoadSound("Audio/Sounds/Werewolf_4.wav");
 Core.Werewolf[4]=Audio.LoadSound("Audio/Sounds/Werewolf_5.wav");
 //Audio.PlayMusic(Core.E1M1);
}

void CLASS_Core::Init()
{
 Core.Bind();
 Core.Load();
}

void CLASS_Core::Unload()
{
 //Atlases
 Graph.UnloadAtlas(Core.HUD);
 Graph.UnloadAtlas(Core.Faces);
 Graph.UnloadAtlas(Core.Tools);
 Graph.UnloadAtlas(Core.Numbers);
 Graph.UnloadAtlas(Core.Hands);
 Graph.UnloadAtlas(Core.Walls);
 Graph.UnloadAtlas(Core.Mechs);
 Graph.UnloadAtlas(Core.Objects);
 //Music
 Audio.UnloadMusic(Core.E1M1); 
 //Sounds
 Audio.UnloadSound(Core.Step[0]);
 Audio.UnloadSound(Core.Step[0]);
 Audio.UnloadSound(Core.Step[0]);
 Audio.UnloadSound(Core.Step[0]);
 Audio.UnloadSound(Core.Select);
 Audio.UnloadSound(Core.Fist);
 Audio.UnloadSound(Core.Werewolf[0]);
 Audio.UnloadSound(Core.Werewolf[1]);
 Audio.UnloadSound(Core.Werewolf[2]);
 Audio.UnloadSound(Core.Werewolf[3]);
 Audio.UnloadSound(Core.Werewolf[4]);
}

void CLASS_Core::Unbind()
{
 Graph.Destroy();
 Audio.Destroy();
}

void CLASS_Core::Destroy()
{
 Core.Unload();
 Core.Unbind();
}

void CLASS_Core::FillScreen()
{
 SDL_SetRenderDrawColor(Graph.Renderer,50,50,50,255);
 SDL_RenderFillRect(Graph.Renderer,&Screen.UpPart);
 SDL_SetRenderDrawColor(Graph.Renderer,150,150,150,255);
 SDL_RenderFillRect(Graph.Renderer,&Screen.DnPart);
}

void CLASS_Core::FlipBuffer()
{
 SDL_RenderPresent(Graph.Renderer);
}

void CLASS_Core::Reset()
{
 Column.Stack.clear();
 Column.Dst.x=0;
 Ray.CurAngle=User.Pov+User.HalfFov;
 if (Ray.CurAngle>Ray.MaxAngle)
 {
  Ray.CurAngle-=Ray.MaxAngle;
 }
}

void CLASS_Core::Prepaire()
{
 Ray.VerError=false;
 Ray.HorError=false;
 Column.VerIntType=Column.NORMAL;
 Column.HorIntType=Column.NORMAL;
}

void CLASS_Core::CheckVerError()
{
 if (Ray.VerX<0 || Ray.VerY<0 || Ray.VerX>World.MaxPx || Ray.VerY>World.MaxPx)
 {
  Ray.VerError=true;
 }
}

void CLASS_Core::PrepaireVerVar()
{
 if (Ray.CurAngle<=180 && Ray.CurAngle>=Ray.MinAngle)
 {
  Ray.VerY=int(User.Y/World.Block)*World.Block-1;
  Ray.VerStepY=-World.Block;
  Ray.VerStepX=World.Block/Table.GetTan(Ray.CurAngle);
 }
 else
 {
  Ray.VerY=int(User.Y/World.Block)*World.Block+World.Block;
  Ray.VerStepY=World.Block;
  Ray.VerStepX=-World.Block/Table.GetTan(Ray.CurAngle);
 }
 Ray.VerX=User.X+(User.Y-Ray.VerY)/Table.GetTan(Ray.CurAngle);
 Core.CheckVerError();
}

void CLASS_Core::MakeVerStep()
{
 Ray.VerX+=Ray.VerStepX;
 Ray.VerY+=Ray.VerStepY;
}

void CLASS_Core::SaveObjInfo(int X,int Y,int HitNum,int CellCnt)
{
 Column.Stack.resize(CellCnt+1);
 Column.Stack[CellCnt].X=X;
 Column.Stack[CellCnt].Y=Y;
 Column.Stack[CellCnt].HitNum=HitNum-200;
}

void CLASS_Core::FindObjXYOffs(double &XOffs,double &YOffs,int CellCnt)
{
 XOffs=Column.Stack[CellCnt].X*World.Block+World.HalfBlock-User.X;
 YOffs=Column.Stack[CellCnt].Y*World.Block+World.HalfBlock-User.Y;
}

void CLASS_Core::FindObjAbsXYOffs(double XOffs,double YOffs,double &AbsXOffs,double &AbsYOffs)
{
 AbsXOffs=abs(XOffs);
 AbsYOffs=abs(YOffs);
}

void CLASS_Core::FindObjMinMaxOffs(double AbsXOffs,double AbsYOffs,double &MinOffs,double &MaxOffs)
{
 if (AbsXOffs>AbsYOffs)
 {
  MinOffs=AbsYOffs;
  MaxOffs=AbsXOffs;
 }
 else
 {
  MinOffs=AbsXOffs;
  MaxOffs=AbsYOffs;
 }
}

void CLASS_Core::FindObjDist(double AbsXOffs,double AbsYOffs,int CellCnt)
{
 Column.Stack[CellCnt].Dist=sqrt(AbsXOffs*AbsXOffs+AbsYOffs*AbsYOffs);
}

void CLASS_Core::FindObjDistAngle(double XOffs,double YOffs,double AbsXOffs,double AbsYOffs,double MaxOffs,double &DistAngle)
{
 if (MaxOffs==AbsXOffs)
 {
  if (AbsXOffs!=0 && AbsYOffs!=0)
  {
   DistAngle=90-Math.ATan(AbsYOffs/AbsXOffs);
  }
  else
  {
   DistAngle=90;
  }
 }
 else
 {
  if (AbsYOffs!=0 && AbsXOffs!=0)
  {
   DistAngle=90-Math.ATan(AbsXOffs/AbsYOffs);
  }
  else
  {
   DistAngle=90;
  }
 }
 if (MaxOffs==AbsXOffs)
 {
  if (XOffs<0)
  {
   if (YOffs<0)
   {
    DistAngle=DistAngle;
    DistAngle+=90;
   }
   else
   {
    DistAngle=abs(90-DistAngle);
    DistAngle+=180;
   }
  }
  else
  {
   if (YOffs<0)
   {
    if (User.Pov>90)
    {
     DistAngle=abs(90-DistAngle);
     DistAngle+=360;
    }
    else
    {
     DistAngle=abs(90-DistAngle);
     DistAngle+=0;
    }
   }
   else
   {
    if (User.Pov>90)
    {
     DistAngle=DistAngle;
     DistAngle+=270;
    }
    else
    {
     DistAngle=DistAngle;
     DistAngle-=90;
    }
   }
  }
 }
 else
 {
  if (XOffs<0)
  {
   if (YOffs<0)
   {
    DistAngle=abs(90-DistAngle);
    DistAngle+=90;
   }
   else
   {
    DistAngle=DistAngle;
    DistAngle+=180;
   }
  }
  else
  {
   if (YOffs<0)
   {
    DistAngle=DistAngle;
    DistAngle+=0;
   }
   else
   {
    DistAngle=abs(90-DistAngle);
    DistAngle+=270;
   }
  }
 }
}

void CLASS_Core::FindObjOffsAngle(double DistAngle,double &OffsAngle)
{                            
 if (User.Pov<=90 && DistAngle>=270)
 {
  OffsAngle=(DistAngle-360)-User.Pov;
  OffsAngle-=int(OffsAngle/90)*90;
 }
 else
 {
  if (User.Pov>=270 && DistAngle<=90)
  {
   OffsAngle=DistAngle-(User.Pov-360);
   OffsAngle-=int(OffsAngle/90)*90;
  }
  else
  {
   if (User.Pov<=180 && DistAngle>360)
   {
    OffsAngle=(DistAngle-360)-User.Pov;
    OffsAngle-=int(OffsAngle/90)*90;
   }
   else
   {
    OffsAngle=DistAngle-User.Pov;
    OffsAngle-=int(OffsAngle/90)*90;
   }
  }
 }
}

void CLASS_Core::FindObjOffs(double OffsAngle,double &Offs)
{
 Offs=Column.DgrToScr*OffsAngle;
}

void CLASS_Core::FindObjSrc(int CellCnt)
{
 Column.Stack[CellCnt].Src.h=Column.ImgOffs;
 Column.Stack[CellCnt].Src.w=Column.ImgOffs;
 Column.Stack[CellCnt].Src.y=Column.ImgOffs*Column.Stack[CellCnt].HitNum;
 Column.Stack[CellCnt].Src.x=0;
}

void CLASS_Core::FindObjDst(double Offs,int CellCnt)
{
 Column.Stack[CellCnt].Dst.h=Column.BlockPlane/int(Column.Stack[CellCnt].Dist);
 Column.Stack[CellCnt].Dst.w=Column.Stack[CellCnt].Dst.h;
 Column.Stack[CellCnt].Dst.y=Screen.MaxHalfHeight-Column.Stack[CellCnt].Dst.h/2;
 Column.Stack[CellCnt].Dst.x=Screen.HalfWidth-int(Offs)-Column.Stack[CellCnt].Dst.h/2;
}

void CLASS_Core::AddObj(int X,int Y,int HitNum)
{
 int CellCnt=Column.Stack.size();
 double XOffs,YOffs,AbsXOffs,AbsYOffs,MinOffs,MaxOffs,DistAngle,OffsAngle,Offs;
 Core.SaveObjInfo(X,Y,HitNum,CellCnt);
 Core.FindObjXYOffs(XOffs,YOffs,CellCnt);
 Core.FindObjAbsXYOffs(XOffs,YOffs,AbsXOffs,AbsYOffs);
 Core.FindObjMinMaxOffs(AbsXOffs,AbsYOffs,MinOffs,MaxOffs);
 Core.FindObjDist(AbsXOffs,AbsYOffs,CellCnt);
 Core.FindObjDistAngle(XOffs,YOffs,AbsXOffs,AbsYOffs,MaxOffs,DistAngle);
 Core.FindObjOffsAngle(DistAngle,OffsAngle);
 Core.FindObjOffs(OffsAngle,Offs);
 Core.FindObjSrc(CellCnt);
 Core.FindObjDst(Offs,CellCnt);
}

void CLASS_Core::FindVerInt()
{
 int HitNumBuf=32000,XBuf,YBuf,PerDotStepCnt,RayXOffs,DoorXBuf,DoorYBuf;
 double PerDotStepX,PerDotStepY; 
 while (!Ray.VerError && HitNumBuf>=200)
 {
  while (!Ray.VerError && !World.Map[World.GetMapCell(int(Ray.VerX/World.Block),int(Ray.VerY/World.Block))])
  {
   Core.MakeVerStep();
   Core.CheckVerError();
  }
  if (!Ray.VerError)
  {
   HitNumBuf=World.Map[World.GetMapCell(XBuf=int(Ray.VerX/World.Block),YBuf=int(Ray.VerY/World.Block))];
   if (HitNumBuf>=100)
   {
    if (HitNumBuf>=200)
    {
     if (!Column.Find(XBuf,YBuf))
     {
      Core.AddObj(XBuf,YBuf,HitNumBuf);
     }
     Core.MakeVerStep();
     Core.CheckVerError();
    }
    else
    {
     PerDotStepCnt=0;
     PerDotStepX=Ray.VerStepX/World.Block;
     PerDotStepY=Ray.VerStepY/World.Block;
     Ray.VerX+=PerDotStepX;
     Ray.VerY+=PerDotStepY;
     Core.CheckVerError();
     while (XBuf==int(Ray.VerX/World.Block) && YBuf==int(Ray.VerY/World.Block) && PerDotStepCnt!=World.HalfBlock)
     {
      PerDotStepCnt++;
      Ray.VerX+=PerDotStepX;
      Ray.VerY+=PerDotStepY;
      Core.CheckVerError();
     }
     DoorXBuf=int(Ray.VerX/World.Block);
     DoorYBuf=int(Ray.VerY/World.Block);
     if  (XBuf!=DoorXBuf || YBuf!=DoorYBuf)
     {
      Column.VerIntType=Column.DOORWALK;
     }
     else
     {
      RayXOffs=int(Ray.VerX)%World.Block;
      if (RayXOffs<World.Find(DoorXBuf,DoorYBuf))
      {
     
      }
     }
    }
   }
  }
 }
}

void CLASS_Core::FindVerDist()
{
 if (!Ray.VerError)
 {
  Ray.VerDist=abs((User.Y-Ray.VerY)/Table.GetSin(Ray.CurAngle));
 }
}

void CLASS_Core::FindVerOffs()
{
 if (!Ray.VerError)
 {
  if (Column.VerIntType==Column.NORMAL)
  {
   if (Ray.VerY<User.Y)
   {
    Column.VerOffs=int(Ray.VerX)%World.Block;
   }												 
   else
   {
    Column.VerOffs=World.Block-1-int(Ray.VerX)%World.Block;
   }
  }
  else
  {
   if (Ray.VerX>User.X)
   {
    Column.VerOffs=int(Ray.VerY)%World.Block;
   }
   else 
   {
    Column.VerOffs=World.Block-1-int(Ray.VerY)%World.Block;
   }
  } 
 }
}

void CLASS_Core::FindVerHitNum()
{
 if (!Ray.VerError)
 {
  Column.VerHitNum=World.Map[World.GetMapCell(int(Ray.VerX/World.Block),int(Ray.VerY/World.Block))];
 }
}

void CLASS_Core::CheckHorError()
{
 if (Ray.HorX<0 || Ray.HorY<0 || Ray.HorX>World.MaxPx || Ray.HorY>World.MaxPx)
 {
  Ray.HorError=true;
 }
}

void CLASS_Core::PrepaireHorVar()
{
 if (Ray.CurAngle<=270 && Ray.CurAngle>=90)
 {
  Ray.HorX=int(User.X/World.Block)*World.Block-1;
  Ray.HorStepX=-World.Block;
  Ray.HorStepY=World.Block*Table.GetTan(Ray.CurAngle);
 }
 else
 {
  Ray.HorX=int(User.X/World.Block)*World.Block+World.Block;
  Ray.HorStepX=World.Block;
  Ray.HorStepY=-World.Block*Table.GetTan(Ray.CurAngle);
 }
 Ray.HorY=User.Y+(User.X-Ray.HorX)*Table.GetTan(Ray.CurAngle);
 Core.CheckHorError();
}

void CLASS_Core::MakeHorStep()
{
 Ray.HorX+=Ray.HorStepX;
 Ray.HorY+=Ray.HorStepY;
}

void CLASS_Core::FindHorInt()
{
 int HitNumBuf=32000,XBuf,YBuf,PerDotStepCnt,RayYOffs,DoorXBuf,DoorYBuf;
 double PerDotStepX,PerDotStepY;
 while (!Ray.HorError && HitNumBuf>=200)
 {
  while (!Ray.HorError && !World.Map[World.GetMapCell(int(Ray.HorX/World.Block),int(Ray.HorY/World.Block))])
  {
   Core.MakeHorStep();
   Core.CheckHorError();
  }
  if (!Ray.HorError)
  {
   HitNumBuf=World.Map[World.GetMapCell(XBuf=int(Ray.HorX/World.Block),YBuf=int(Ray.HorY/World.Block))];
   if (HitNumBuf>=100)
   {
    if (HitNumBuf>=200)
    {
     if (!Column.Find(XBuf,YBuf))
     {
      Core.AddObj(XBuf,YBuf,HitNumBuf);
     }
     Core.MakeHorStep();
     Core.CheckHorError();
    }
    else
    {
     PerDotStepCnt=0;
     PerDotStepX=Ray.HorStepX/World.Block;
     PerDotStepY=Ray.HorStepY/World.Block;
     Ray.HorX+=PerDotStepX;
     Ray.HorY+=PerDotStepY;
     Core.CheckHorError();
     while (XBuf==int(Ray.HorX/World.Block) && YBuf==int(Ray.HorY/World.Block) && PerDotStepCnt!=World.HalfBlock)
     {
      PerDotStepCnt++;
      Ray.HorX+=PerDotStepX;
      Ray.HorY+=PerDotStepY;
      Core.CheckHorError();
     }
     DoorXBuf=int(Ray.HorX/World.Block);
     DoorYBuf=int(Ray.HorY/World.Block);
     if  (XBuf!=DoorXBuf || YBuf!=DoorYBuf)
     {
      Column.HorIntType=Column.DOORWALK;
     }
     else
     {
      RayYOffs=int(Ray.HorY)%World.Block;
      if (RayYOffs<World.Find(DoorXBuf,DoorYBuf))
      {
     
      }
     }
    }
   }
  }
 }
}

void CLASS_Core::FindHorDist()
{
 if (!Ray.HorError)
 {
  Ray.HorDist=abs((User.Y-Ray.HorY)/Table.GetSin(Ray.CurAngle));
 }
}

void CLASS_Core::FindHorOffs()
{
 if (!Ray.HorError)
 {
  if (Column.HorIntType==Column.NORMAL)
  {
   if (Ray.HorX>User.X)
   {
    Column.HorOffs=int(Ray.HorY)%World.Block;
   }
   else 
   {
    Column.HorOffs=World.Block-1-int(Ray.HorY)%World.Block;
   }
  }
  else
  {
   if (Ray.HorY<User.Y)
   {
    Column.HorOffs=int(Ray.HorX)%World.Block;
   }												 
   else
   {
    Column.HorOffs=World.Block-1-int(Ray.HorX)%World.Block;
   }
  } 
 }
}

void CLASS_Core::FindHorHitNum()
{
 if (!Ray.HorError)
 {
  Column.HorHitNum=World.Map[World.GetMapCell(int(Ray.HorX/World.Block),int(Ray.HorY/World.Block))];
 }
}

void CLASS_Core::Compare()
{
 if (!Ray.VerError && !Ray.HorError)
 {
  if (Column.VerIntType==Column.DOORWALK)
  {
   Ray.Dist=Ray.HorDist; 
   Column.Offs=Column.HorOffs;
		 Column.HitNum=Column.HorHitNum;
		 Column.Src.x=Column.ImgOffs+Column.Offs;
  }
  else
  {
   if (Column.HorIntType==Column.DOORWALK)
   {
    Ray.Dist=Ray.VerDist;
    Column.Offs=Column.VerOffs;
		  Column.HitNum=Column.VerHitNum;
		  Column.Src.x=Column.Offs;
   }
   else
   {
    if (Ray.VerDist>Ray.HorDist)
    {
	    Ray.Dist=Ray.HorDist; 
     Column.Offs=Column.HorOffs;
		   Column.HitNum=Column.HorHitNum;
		   Column.Src.x=Column.ImgOffs+Column.Offs;
	   }
    else
    {
     Ray.Dist=Ray.VerDist;
     Column.Offs=Column.VerOffs;
		   Column.HitNum=Column.VerHitNum;
		   Column.Src.x=Column.Offs;
    }
   }
  }
 }
 else 
 {
  if (Ray.VerError)
		{
		 Ray.Dist=Ray.HorDist;
		 Column.Offs=Column.HorOffs;
		 Column.HitNum=Column.HorHitNum;
		 Column.Src.x=Column.ImgOffs+Column.Offs;
		}
	 else
	 {
	  Ray.Dist=Ray.VerDist;
   Column.Offs=Column.VerOffs;
		 Column.HitNum=Column.VerHitNum;
		 Column.Src.x=Column.Offs;
	 }
 }
 Screen.Dist[Column.Dst.x]=Ray.Dist;
}

void CLASS_Core::FindDirDist()
{
 if (User.Pov-Ray.CurAngle!=0)
 {
  Ray.DirectDist=Ray.Dist*Table.GetCos(User.Pov-Ray.CurAngle);
 }
 else
 {
  Ray.DirectDist=Ray.Dist;
 }
}

void CLASS_Core::CorrectDirDist()
{
 if (Ray.DirectDist<=0)
 {
  Ray.DirectDist=1;
 }
}

void CLASS_Core::FindSrc()
{
 if (Column.HitNum<100)
 {
  Column.Src.y=Column.ImgOffs*Column.HitNum;
 }
 else
 {
  Column.Src.y=Column.ImgOffs*(Column.HitNum-100);
 }
}

void CLASS_Core::FindDst()
{
 if (Column.HitNum<100)
 {
  Column.Dst.h=int(Column.BlockPlane/Ray.DirectDist);
  Column.Dst.y=Screen.MaxHalfHeight-int(Column.Dst.h/2);
 }
 else
 {
  Column.Dst.h=int(Column.BlockPlane/Ray.DirectDist);
  Column.Dst.y=Screen.MaxHalfHeight-int(Column.Dst.h/2);
 }
}

void CLASS_Core::Out()
{
 if (Column.HitNum<100)
 {
  SDL_RenderCopy(Graph.Renderer,Core.Walls,&Column.Src,&Column.Dst);
 }
 else
 {
  SDL_RenderCopy(Graph.Renderer,Core.Mechs,&Column.Src,&Column.Dst);
 }
}

void CLASS_Core::SortObjByDist(int CellCnt)
{
 int SortCnt,FindCnt,CellCntBuf;
 double MaxDistBuf;
 Column.Sort.resize(CellCnt);
 for (SortCnt=0;SortCnt<CellCnt;SortCnt++)
 {
  MaxDistBuf=0;
  for (FindCnt=0;FindCnt<CellCnt;FindCnt++)
  {
   if (Column.Stack[FindCnt].Dist>MaxDistBuf)
   {
    MaxDistBuf=Column.Stack[FindCnt].Dist;
    CellCntBuf=FindCnt;
   }
  }
  Column.Sort[SortCnt].CellCnt=CellCntBuf;
  Column.Sort[SortCnt].Dist=MaxDistBuf;
  Column.Stack[CellCntBuf].Dist=0;
 }
}

void CLASS_Core::CutObjByDist(int CellCnt)
{
 int Start,End,Width,Offs;
 double WidthCoef,OffsCoef;
 Start=Column.Stack[Column.Sort[CellCnt].CellCnt].Dst.x;
 if (Start<0)
 {
  Start=0;
 }
 while (Start<Screen.Width && Column.Sort[CellCnt].Dist>Screen.Dist[Start])
 {
  Start++;
 }
 if (Start>=Screen.Width)
 {
  Start=Screen.Width-1;
 }
 End=Column.Stack[Column.Sort[CellCnt].CellCnt].Dst.x+Column.Stack[Column.Sort[CellCnt].CellCnt].Dst.w;
 if (End>=Screen.Width)
 {
  End=Screen.Width-1;
 }
 while (End>=0 && Column.Sort[CellCnt].Dist>Screen.Dist[End])
 {
  End--;
 }
 if (End<0)
 {
  End=0;
 }
 Width=End-Start;
 WidthCoef=double(Width)/double(Column.Stack[Column.Sort[CellCnt].CellCnt].Dst.w);
 Column.Stack[Column.Sort[CellCnt].CellCnt].Src.w=int(Column.Stack[Column.Sort[CellCnt].CellCnt].Src.w*WidthCoef);
 Offs=Start-Column.Stack[Column.Sort[CellCnt].CellCnt].Dst.x;
 OffsCoef=double(Column.ImgOffs)/double(Column.Stack[Column.Sort[CellCnt].CellCnt].Dst.w);
 Column.Stack[Column.Sort[CellCnt].CellCnt].Src.x=int(Offs*OffsCoef);
 Column.Stack[Column.Sort[CellCnt].CellCnt].Dst.w=Width;
 Column.Stack[Column.Sort[CellCnt].CellCnt].Dst.x=Start;    
}

void CLASS_Core::OutObj()
{
 int Cnt,CellCnt=Column.Stack.size();
 Core.SortObjByDist(CellCnt);
 for (Cnt=0;Cnt<CellCnt;Cnt++)
 {
  Core.CutObjByDist(Cnt);
  SDL_RenderCopy(Graph.Renderer,Core.Objects,
                 &Column.Stack[Column.Sort[Cnt].CellCnt].Src,&Column.Stack[Column.Sort[Cnt].CellCnt].Dst);
 }
}

void CLASS_Core::Postpaire()
{
 Ray.CurAngle-=Ray.ExtAngle;
 if (Ray.CurAngle<Ray.MinAngle)
 {
  Ray.CurAngle+=Ray.MaxAngle;
 }
 Column.Dst.x++;
}

void CLASS_Core::Raycasting()
{
 Core.Reset();
 while (Column.Dst.x!=Screen.Width)
 {
  Core.Prepaire();
  Core.PrepaireVerVar();
  Core.FindVerInt();
  Core.FindVerDist();
  Core.FindVerOffs();
  Core.FindVerHitNum();
  Core.PrepaireHorVar();
  Core.FindHorInt();
  Core.FindHorDist();
  Core.FindHorOffs();
  Core.FindHorHitNum();
  Core.Compare();
  Core.FindDirDist();
  Core.CorrectDirDist();
  Core.FindSrc();
  Core.FindDst();
  Core.Out();
  Core.Postpaire();
 }
 Core.OutObj();
}

void CLASS_Core::DrawHUD()
{
 SDL_RenderCopy(Graph.Renderer,Core.HUD,NULL,&Screen.HUD);
}

void CLASS_Core::DrawTool()
{
 SDL_Rect Src={0,52*User.Tool,72,52};
 SDL_RenderCopy(Graph.Renderer,Core.Tools,&Src,&Screen.Tool);
}

void CLASS_Core::OutHealth()
{
 SDL_Rect Src={0,0,16,32},DstBuf=Screen.Health;
 int Cnt=0;
 char Buf[4];
 _itoa_s(User.Health,Buf,4,10);
 while (Buf[Cnt+1]!='\0')
 {
  Cnt++;
 }
 while (Cnt!=-1)
 {
  Src.y=(Buf[Cnt]-48)*Src.h;
  SDL_RenderCopy(Graph.Renderer,Core.Numbers,&Src,&DstBuf);
  DstBuf.x-=DstBuf.w;
  Cnt--;
 }
}

void CLASS_Core::DrawFace()
{    
 SDL_Rect Src={0,52*User.Face,72,52};   
 SDL_RenderCopy(Graph.Renderer,Core.Faces,&Src,&Screen.Face);
}

void CLASS_Core::DrawHand()
{
 static int Time=6,Timer=Time; 
 if (User.HandPhase!=0)
 {
  if (Timer==0)
  {
   if (User.HandPhase!=5)
   {
    User.HandPhase++;
   }
   else
   {
    User.HandPhase=0;
   }
   Timer=Time;
  }
  else
  {
   Timer--;
  }
 }
 SDL_Rect Src={384*User.HandPhase,384*User.Tool,384,384};
 SDL_RenderCopy(Graph.Renderer,Core.Hands,&Src,&Screen.Hand);
}

void CLASS_Core::Draw()
{
 Core.Raycasting();
 Core.DrawHUD();
 Core.DrawTool();
 Core.OutHealth();
 Core.DrawFace();
 Core.DrawHand();
}

void CLASS_Core::UpdatePovSide()
{
 User.PovSide=User.Pov+90;
 if (User.PovSide>Ray.MaxAngle)
 {
  User.PovSide-=Ray.MaxAngle;
 }
}

void CLASS_Core::UpdateKeyState()
{
 SDL_PumpEvents();
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

void CLASS_Core::CheckW()
{
 if (Graph.Keys[SDL_SCANCODE_W])
 {
  if (World.Bar[World.GetBarCell(int(User.X),int(User.Y-User.MovSpd*Table.GetSin(User.Pov)))]==0)
  {
   User.Y-=User.MovSpd*Table.GetSin(User.Pov);
  }  
  if (World.Bar[World.GetBarCell(int(User.X+User.MovSpd*Table.GetCos(User.Pov)),int(User.Y))]==0)
  {
   User.X+=User.MovSpd*Table.GetCos(User.Pov);
  }
  if (User.StepPhase!=0)
  {
   if (!Audio.IsSoundPlaying(Core.Step[User.StepPhase-1]))
   {
    Audio.PlaySound(Core.Step[User.StepPhase]);
    if (User.StepPhase!=3)
    {
     User.StepPhase++;
    }
    else
    {
     User.StepPhase=0;
    }
   }
  }
  else
  {
   if (!Audio.IsSoundPlaying(Core.Step[3]))
   {
    Audio.PlaySound(Core.Step[User.StepPhase]);
    User.StepPhase++;
   }
  }
 }
}

void CLASS_Core::CheckA()
{
 if (Graph.Keys[SDL_SCANCODE_A])
 {
  if (World.Bar[World.GetBarCell(int(User.X),int(User.Y-User.MovSpd*Table.GetSin(User.PovSide)))]==0)
  {
   User.Y-=User.MovSpd*Table.GetSin(User.PovSide);
  }
  if (World.Bar[World.GetBarCell(int(User.X+User.MovSpd*Table.GetCos(User.PovSide)),int(User.Y))]==0)
  {
   User.X+=User.MovSpd*Table.GetCos(User.PovSide);
  }
  if (User.StepPhase!=0)
  {
   if (!Audio.IsSoundPlaying(Core.Step[User.StepPhase-1]))
   {
    Audio.PlaySound(Core.Step[User.StepPhase]);
    if (User.StepPhase!=3)
    {
     User.StepPhase++;
    }
    else
    {
     User.StepPhase=0;
    }
   }
  }
  else
  {
   if (!Audio.IsSoundPlaying(Core.Step[3]))
   {
    Audio.PlaySound(Core.Step[User.StepPhase]);
    User.StepPhase++;
   }
  }
 }
}

void CLASS_Core::CheckS()
{
 if (Graph.Keys[SDL_SCANCODE_S])
 {
  if (World.Bar[World.GetBarCell(int(User.X),int(User.Y+User.MovSpd*Table.GetSin(User.Pov)))]==0)
  {
   User.Y+=User.MovSpd*Table.GetSin(User.Pov);
  }
  if (World.Bar[World.GetBarCell(int(User.X-User.MovSpd*Table.GetCos(User.Pov)),int(User.Y))]==0)
  {
   User.X-=User.MovSpd*Table.GetCos(User.Pov);
  }
  if (User.StepPhase!=0)
  {
   if (!Audio.IsSoundPlaying(Core.Step[User.StepPhase-1]))
   {
    Audio.PlaySound(Core.Step[User.StepPhase]);
    if (User.StepPhase!=3)
    {
     User.StepPhase++;
    }
    else
    {
     User.StepPhase=0;
    }
   }
  }
  else
  {
   if (!Audio.IsSoundPlaying(Core.Step[3]))
   {
    Audio.PlaySound(Core.Step[User.StepPhase]);
    User.StepPhase++;
   }
  }
 }
}

void CLASS_Core::CheckD()
{
 if (Graph.Keys[SDL_SCANCODE_D])
 {
  if (World.Bar[World.GetBarCell(int(User.X),int(User.Y+User.MovSpd*Table.GetSin(User.PovSide)))]==0)
  {
   User.Y+=User.MovSpd*Table.GetSin(User.PovSide);
  }
  if (World.Bar[World.GetBarCell(int(User.X-User.MovSpd*Table.GetCos(User.PovSide)),int(User.Y))]==0)
  {
   User.X-=User.MovSpd*Table.GetCos(User.PovSide);
  }
  if (User.StepPhase!=0)
  {
   if (!Audio.IsSoundPlaying(Core.Step[User.StepPhase-1]))
   {
    Audio.PlaySound(Core.Step[User.StepPhase]);
    if (User.StepPhase!=3)
    {
     User.StepPhase++;
    }
    else
    {
     User.StepPhase=0;
    }
   }
  }
  else
  {
   if (!Audio.IsSoundPlaying(Core.Step[3]))
   {
    Audio.PlaySound(Core.Step[User.StepPhase]);
    User.StepPhase++;
   }
  }
 }
}

void CLASS_Core::Check1()
{
 if (Graph.Keys[SDL_SCANCODE_1])
 {
  if (User.Tool!=0)
  {
   User.Tool=0;
   User.HandPhase=0;
   User.Face=0;
   Audio.PlaySound(Core.Select);   
  }
 }
}

void CLASS_Core::Check2()
{
 if (Graph.Keys[SDL_SCANCODE_2])
 {
  if (User.Tool!=1)
  {
   User.Tool=1;
   User.HandPhase=0;
   User.Face=1;
   Audio.PlaySound(Core.Select);
  }
 }
}

void CLASS_Core::CheckSpace()
{
 if (Graph.Keys[SDL_SCANCODE_SPACE])
 {
  
 }
}

void CLASS_Core::UpdateMouseState()
{
 SDL_WarpMouseInWindow(Graph.Window,Screen.HalfWidth,Screen.HalfHeight);
 Graph.Buttons=SDL_GetMouseState(&User.MouseX,NULL);
}

void CLASS_Core::CheckMouseX()
{
 if (User.MouseX<Screen.HalfWidth)
 {
  User.Pov+=User.RotSpd*(Screen.HalfWidth-User.MouseX);
  if (User.Pov>Ray.MaxAngle)
  {
   User.Pov-=Ray.MaxAngle;
  }
 }
 else
 { 
	 User.Pov-=User.RotSpd*(User.MouseX-Screen.HalfWidth);
	 if (User.Pov<Ray.MinAngle)
  {
   User.Pov+=Ray.MaxAngle;
  }                 
 }
}

void CLASS_Core::CheckMouseLeft()
{
 if (Graph.Buttons & SDL_BUTTON(SDL_BUTTON_LEFT))
 {
  switch (User.Tool)
  {
   case 0:
    if (User.HandPhase==0)
    {
     User.HandPhase=1;
     if (!Audio.IsSoundPlaying(Core.Fist))
     {
      Audio.PlaySound(Core.Fist);
     }
    }
    break;
   case 1:
    if (User.HandPhase==0)
    {
     User.HandPhase=1;
     if (User.WerewolfPhase!=0)
     {
      if (!Audio.IsSoundPlaying(Core.Werewolf[User.WerewolfPhase-1]))
      {
       Audio.PlaySound(Core.Werewolf[User.WerewolfPhase]);     
       if (User.WerewolfPhase!=4)
       {
        User.WerewolfPhase++;
       }
       else
       {
        User.WerewolfPhase=0;
       }
      }
     }
     else
     {
      if (!Audio.IsSoundPlaying(Core.Werewolf[4]))
      {
       Audio.PlaySound(Core.Werewolf[User.WerewolfPhase]);
       User.WerewolfPhase++;
      }
     }
    }
    break;
  }
 }
}

int CLASS_Core::DetectKey()
{
 Core.UpdatePovSide();
 Core.UpdateKeyState();
 if (Core.CheckEscape())
 {
  return 1;
 }
 Core.CheckW();
 Core.CheckA();
 Core.CheckS();
 Core.CheckD();
 Core.Check1();
 Core.Check2();
 Core.CheckSpace();
 Core.UpdateMouseState();
 Core.CheckMouseX();
 Core.CheckMouseLeft();
 return 0;
}

//eof

















































