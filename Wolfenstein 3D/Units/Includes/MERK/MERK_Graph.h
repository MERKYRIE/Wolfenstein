#ifndef MERK_Graph
#define MERK_Graph

#include <SDL/SDL.h>

class CLASS_Graph
{
 public:
  typedef SDL_Texture* TYPE_Atlas;
  const Uint8* Keys; 
  Uint32 Buttons;
  SDL_Window* Window=NULL;
  SDL_Renderer* Renderer=NULL;
  void Init(const char* Title,int X,int Y,int Width,int Height,Uint32 WindowFlags,Uint32 RendererFlags,int CursorStat);
  void Destroy();
  TYPE_Atlas LoadAtlas(const char* Path);
  void UnloadAtlas(TYPE_Atlas &Atlas);
};

#endif

















































