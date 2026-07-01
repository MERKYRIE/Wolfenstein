#ifndef MERK_Misc
#define MERK_Misc

#include <MERK/MERK_World.h>

class CLASS_Misc
{
 public:
  void ErrorHandle(const char* Text);
  void ShowError(char* Text1,char* Text2,SDL_Renderer* Renderer,SDL_Event Event);
  void ShowSuccess(char* Text,SDL_Renderer* Renderer,SDL_Event Event);
  void ShowHelp(SDL_Renderer* Renderer,SDL_Event Event);
  void SaveMap(const char* Path,int Size,int StartX,int StartY,CLASS_World::TYPE_Map Map,CLASS_World::TYPE_Barrier Barrier,CLASS_World::TYPE_Mechanism Mechanism);
};

extern CLASS_Misc Misc;

#endif

















































