#include <iostream>
#include <fstream>
#include <vector>
#include <SDL/SDL.h>
#include <MERK/MERK_Core.h>
#include <MERK/MERK_Misc.h>

CLASS_Misc Misc;

void CLASS_Misc::ErrorHandle(const char* Text)
{
 Core.Destroy();
 std::cout<<Text<<std::endl<<SDL_GetError()<<std::endl<<"Exiting..."<<std::endl;
 system("Pause");
 exit(-1);
}

void CLASS_Misc::LoadMap(const char* Path,int &MapSize,int &BarSize,int &StartX,int &StartY,CLASS_World::TYPE_Map &Map,CLASS_World::TYPE_Barrier &Barrier,CLASS_World::TYPE_Mechanism &Mechanism)
{
 char InfPath[256+1],MapPath[256+1],BarPath[256+1],MchPath[256+1];
 std::ifstream File;
 strcpy_s(InfPath,sizeof(InfPath),Path);
 strcat_s(InfPath,sizeof(InfPath),".inf");
 File.open(InfPath,std::ios::binary);
 if (!File)
 {
  CLASS_Misc::ErrorHandle("Failed to open file");
 }
 File.read((char*)&MapSize,sizeof(MapSize));
 File.read((char*)&StartX,sizeof(StartX));
 File.read((char*)&StartY,sizeof(StartY));
 File.close();
 strcpy_s(MapPath,sizeof(MapPath),Path);
 strcat_s(MapPath,sizeof(MapPath),".map");
 File.open(MapPath,std::ios::binary);
 if (!File)
 {
  CLASS_Misc::ErrorHandle("Failed to open file");
 }
 Map.resize(MapSize*MapSize);
 File.read((char*)&Map[0],MapSize*MapSize);  
 File.close();
 strcpy_s(BarPath,sizeof(BarPath),Path);
 strcat_s(BarPath,sizeof(BarPath),".bar");
 File.open(BarPath,std::ios::binary);
 if (!File)
 {
  CLASS_Misc::ErrorHandle("Failed to open file");
 }
 BarSize=MapSize*MapSize;
 Barrier.resize(BarSize*BarSize);
 File.read((char*)&Barrier[0],BarSize*BarSize);
 File.close();
 strcpy_s(MchPath,sizeof(MchPath),Path);
 strcat_s(MchPath,sizeof(MchPath),".mch");
 File.open(MchPath,std::ios::binary);
 if (!File)
 {
  CLASS_Misc::ErrorHandle("Failed to open File");
 }
 while (!File.eof())
 {
  Mechanism.resize(Mechanism.size()+1);
  File.read((char*)&Mechanism[Mechanism.size()-1].X,2);
  File.read((char*)&Mechanism[Mechanism.size()-1].Y,2);
  Mechanism[Mechanism.size()-1].Offs=0;
 }
 Mechanism.erase(Mechanism.end()-1);
 File.close();
}

//eof

















































