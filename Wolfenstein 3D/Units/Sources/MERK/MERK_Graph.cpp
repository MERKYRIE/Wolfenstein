#include <vector>
#include <SDL/SDL.h>
#include <MERK/MERK_Misc.h>
#include <MERK/MERK_Graph.h>

void CLASS_Graph::Init(const char* Title,int X,int Y,int Width,int Height,Uint32 WindowFlags,Uint32 RendererFlags,int CursorStat)
{
 int HalfWidth,HalfHeight;
 HalfWidth=Width/2;
 HalfHeight=Height/2;
 if (SDL_Init(SDL_INIT_VIDEO)<0)
 {
  Misc.ErrorHandle("Failed to initialize Video");
 }
 CLASS_Graph::Window=SDL_CreateWindow(Title,X,Y,Width,Height,WindowFlags);
 if (CLASS_Graph::Window==NULL)
 {
  Misc.ErrorHandle("Failed to create Window");
 }
 CLASS_Graph::Renderer=SDL_CreateRenderer(CLASS_Graph::Window,-1,RendererFlags);
 if (CLASS_Graph::Renderer==NULL)
 {
  Misc.ErrorHandle("Failed to create Renderer");
 }
 if (SDL_ShowCursor(CursorStat)<0)
 {
  Misc.ErrorHandle("Failed to set Cursor's Status");
 }
 SDL_WarpMouseInWindow(CLASS_Graph::Window,HalfWidth,HalfHeight);
 SDL_SetRenderDrawColor(CLASS_Graph::Renderer,0,0,0,255);
}

void CLASS_Graph::Destroy()
{
 SDL_DestroyRenderer(CLASS_Graph::Renderer);
 CLASS_Graph::Renderer=NULL;
 SDL_DestroyWindow(CLASS_Graph::Window);
 CLASS_Graph::Window=NULL;
 SDL_Quit();
}

CLASS_Graph::TYPE_Atlas CLASS_Graph::LoadAtlas(const char* Path)
{
 SDL_Surface* Surface=NULL;
 SDL_Texture* Texture=NULL;
 Surface=SDL_LoadBMP(Path);
 if (Surface==NULL)
 {
  Misc.ErrorHandle("Failed to load Image");
 }
 SDL_SetColorKey(Surface,SDL_TRUE,SDL_MapRGB(Surface->format,152,0,136));
 Texture=SDL_CreateTextureFromSurface(CLASS_Graph::Renderer,Surface);
 if (Texture==NULL)
 {
  Misc.ErrorHandle("Failed to create Texture");
 }
 SDL_FreeSurface(Surface);
 return Texture; 
}

void CLASS_Graph::UnloadAtlas(CLASS_Graph::TYPE_Atlas &Atlas)
{
 SDL_DestroyTexture(Atlas);
 Atlas=NULL;
}

//eof

















































