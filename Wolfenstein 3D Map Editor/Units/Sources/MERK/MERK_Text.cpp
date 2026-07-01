#include <vector>
#include <SDL/SDL.h>
#include <SDL_ttf/SDL_ttf.h>
#include <MERK/MERK_Misc.h>
#include <MERK/MERK_Text.h>

void CLASS_Text::Init(const char* Path,int Width,int Height)
{
 CLASS_Text::Color={255,255,255,255};
 CLASS_Text::Width=Width;
 CLASS_Text::Height=Height;
 if (TTF_Init()==-1)
 {
  Misc.ErrorHandle("Failed to initialize Font System");
 }
 CLASS_Text::Font=TTF_OpenFont(Path,CLASS_Text::Height);
 if (CLASS_Text::Font==NULL)
 {
  Misc.ErrorHandle("Failed to open Font");
 }
}

void CLASS_Text::Destroy()
{
 TTF_CloseFont(CLASS_Text::Font);
 CLASS_Text::Font=NULL;
 TTF_Quit();
}

void CLASS_Text::Out(char* Text,int X,int Y,SDL_Renderer* Renderer)
{
 static char Buf[256+1]="";
 static SDL_Rect Pos={0,0,0,CLASS_Text::Height};
 SDL_Surface* Surface;
 SDL_Texture* Texture;
 strcpy_s(Buf,Text);
 Pos.x=X;
 Pos.y=Y;
 Pos.w=strlen(Buf)*CLASS_Text::Width;
 Surface=TTF_RenderText_Solid(CLASS_Text::Font,Buf,CLASS_Text::GetColor());
 if (Surface==NULL)
 {
  Misc.ErrorHandle("Failed to load Text");
 }
 Texture=SDL_CreateTextureFromSurface(Renderer,Surface);
 if (Texture==NULL)
 {
  Misc.ErrorHandle("Failed to create Text Texture");
 }
 SDL_FreeSurface(Surface);
 Surface=NULL;
 SDL_RenderCopy(Renderer,Texture,NULL,&Pos);
 Texture=NULL;
}

void CLASS_Text::OutNum(char* Text,int Num,int X,int Y,SDL_Renderer* Renderer)
{
 static char NumBuf[4+1]="",TextBuf[256+sizeof(NumBuf)]="";
 static SDL_Rect Pos={0,0,0,CLASS_Text::Height};
 SDL_Surface* Surface;
 SDL_Texture* Texture;
 strcpy_s(TextBuf,Text);
 _itoa_s(Num,NumBuf,sizeof(NumBuf),10);
 strcat_s(TextBuf,sizeof(TextBuf),NumBuf);
 Pos.x=X;
 Pos.y=Y;
 Pos.w=strlen(TextBuf)*CLASS_Text::Width;
 Surface=TTF_RenderText_Solid(CLASS_Text::Font,TextBuf,CLASS_Text::GetColor());
 if (Surface==NULL)
 {
  Misc.ErrorHandle("Failed to load Text");
 }
 Texture=SDL_CreateTextureFromSurface(Renderer,Surface);
 if (Texture==NULL)
 {
  Misc.ErrorHandle("Failed to create Text Texture");
 }
 SDL_FreeSurface(Surface);
 Surface=NULL;
 SDL_RenderCopy(Renderer,Texture,NULL,&Pos);
 Texture=NULL;
}

void CLASS_Text::SetColor(int r,int g,int b)
{
 CLASS_Text::Color={r,g,b,255};
}

SDL_Color CLASS_Text::GetColor()
{
 return CLASS_Text::Color;
}

//eof

















































