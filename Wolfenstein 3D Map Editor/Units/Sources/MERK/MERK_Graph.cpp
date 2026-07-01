#include <vector>
#include <SDL/SDL.h>
#include <MERK/MERK_Misc.h>
#include <MERK/MERK_Graph.h>

void CLASS_Graph::Init(const char* Title,int X,int Y,int Width,int Height,Uint32 WindowFlags,Uint32 RendererFlags,int CursorStat)
{
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
 SDL_WarpMouseInWindow(CLASS_Graph::Window,Width/2,Height/2);
 SDL_SetRenderDrawColor(CLASS_Graph::Renderer,0,0,0,255);
 CLASS_Graph::AtlasCnt=0;
 CLASS_Graph::Atlas.resize(1);
}

void CLASS_Graph::Destroy()
{
 SDL_DestroyRenderer(CLASS_Graph::Renderer);
 CLASS_Graph::Renderer=NULL;
 SDL_DestroyWindow(CLASS_Graph::Window);
 CLASS_Graph::Window=NULL;
 SDL_Quit();
}

void CLASS_Graph::LoadAtlas(const char* Path,int MaxTex)
{
 CLASS_Graph::AtlasCnt++;
 SDL_Surface* Surface;
 SDL_Texture* Texture;
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
 Surface=NULL;
 CLASS_Graph::Atlas.resize(CLASS_Graph::Atlas.size()+1);
 CLASS_Graph::Atlas[CLASS_Graph::AtlasCnt].Data=Texture;
 CLASS_Graph::Atlas[CLASS_Graph::AtlasCnt].MaxTex=MaxTex;
 Texture=NULL;
}

int CLASS_Graph::GetAtlasCnt()
{
 return CLASS_Graph::AtlasCnt; 
}

//eof

















































