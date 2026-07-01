#include <iostream>
#include <fstream>
#include <vector>
#include <SDL/SDL.h>
#include <SDL_ttf/SDL_ttf.h>
#include <MERK/MERK_Core.h>
#include <MERK/MERK_Text.h>
#include <MERK/MERK_Misc.h>

CLASS_Misc Misc;
extern CLASS_Text Text;

void CLASS_Misc::ErrorHandle(const char* Text)
{
 Core.Destroy();
 std::cout<<Text<<std::endl<<SDL_GetError()<<std::endl<<"Exiting..."<<std::endl;
 system("Pause");
 exit(-1);
}

void CLASS_Misc::ShowError(char* Text1,char* Text2,SDL_Renderer* Renderer,SDL_Event Event)
{
 int Y=Text.Height;
 Core.FillScreen();
 Text.SetColor(255,0,0);
 Text.Out(Text1,0,Y,Renderer);
 Y+=Text.Height;
	Text.Out(Text2,0,Y,Renderer);
 Y+=Text.Height;
	Text.Out("Press any key to continue...",0,Y,Renderer);
	Core.FlipBuffer();
 do 
 {
  SDL_WaitEvent(&Event); 
 }
 while (Event.type!=SDL_KEYDOWN);
}

void CLASS_Misc::ShowSuccess(char* Text,SDL_Renderer* Renderer,SDL_Event Event)
{
 int Y=::Text.Height;
 Core.FillScreen();
 ::Text.SetColor(0,255,0);
 ::Text.Out(Text,0,Y,Renderer);
 Y+=::Text.Height;
	::Text.Out("Press any key to continue...",0,Y,Renderer);
	Core.FlipBuffer();
 do 
 {
  SDL_WaitEvent(&Event); 
 }
 while (Event.type!=SDL_KEYDOWN);
}

void CLASS_Misc::ShowHelp(SDL_Renderer* Renderer,SDL_Event Event)
{
 int Y=Text.Height;
 Core.FillScreen();
 ::Text.SetColor(255,255,255);
 ::Text.Out("Instructions:",0,Y,Renderer);
 Y+=Text.Height;
 ::Text.Out("-WASD to move",0,Y,Renderer);
 Y+=Text.Height;
 ::Text.Out("-Arrows to change Texture",0,Y,Renderer);
 Y+=Text.Height;
 ::Text.Out("-F2 to save map",0,Y,Renderer);
 Y+=Text.Height;
 ::Text.Out("-Alt to set starting position",0,Y,Renderer);
 Y+=Text.Height;
 ::Text.Out("-Tab to clear cell",0,Y,Renderer);
 Y+=Text.Height;
 ::Text.Out("-Space to fill cell",0,Y,Renderer);
 Y+=Text.Height;
 ::Text.Out("-Escape to exit",0,Y,Renderer);
 Y+=Text.Height;
	::Text.Out("Press any key to continue...",0,Y,Renderer);
	Core.FlipBuffer();
 do 
 {
  SDL_WaitEvent(&Event); 
 }
 while (Event.type!=SDL_KEYDOWN);
}

void CLASS_Misc::SaveMap(const char* Path,int Size,int StartX,int StartY,CLASS_World::TYPE_Map Map,CLASS_World::TYPE_Barrier Barrier,CLASS_World::TYPE_Mechanism Mechanism)
{
 int Cnt;
 char InfPath[256+1],MapPath[256+1],BarPath[256+1],MchPath[256+1];
 std::ofstream File;
 strcpy_s(InfPath,sizeof(InfPath),Path);
 strcat_s(InfPath,sizeof(InfPath),".inf");
 File.open(InfPath,std::ios::binary);
 if (!File)
 {
  CLASS_Misc::ErrorHandle("Failed to open File");
 }
 File.write((char*)&Size,sizeof(Size));
 File.write((char*)&StartX,sizeof(StartX));
 File.write((char*)&StartY,sizeof(StartY));
 File.close();
 strcpy_s(MapPath,sizeof(MapPath),Path);
 strcat_s(MapPath,sizeof(MapPath),".map");
 File.open(MapPath,std::ios::binary);
 if (!File)
 {
  CLASS_Misc::ErrorHandle("Failed to open File");
 }
 File.write((char*)&Map[0],Map.size());
 File.close();
 strcpy_s(BarPath,sizeof(BarPath),Path);
 strcat_s(BarPath,sizeof(BarPath),".bar");
 File.open(BarPath,std::ios::binary);
 if (!File)
 {
  CLASS_Misc::ErrorHandle("Failed to open File");
 }
 File.write((char*)&Barrier[0],Barrier.size());
 File.close();
 strcpy_s(MchPath,sizeof(MchPath),Path);
 strcat_s(MchPath,sizeof(MchPath),".mch");
 File.open(MchPath,std::ios::binary);
 if (!File)
 {
  CLASS_Misc::ErrorHandle("Failed to open File");
 }
 for (Cnt=0;Cnt<Mechanism.size();Cnt++)
 {
  File.write((char*)&Mechanism[Cnt].X,2);
  File.write((char*)&Mechanism[Cnt].Y,2);
 }
 File.close();
}

//eof

















































