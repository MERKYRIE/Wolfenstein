#ifndef MERK_Graph
#define MERK_Graph

class CLASS_Graph
{
 public:
  typedef class CLASS_Atlas
  {
   public:
    SDL_Texture* Data;
    int MaxTex;
  };
  typedef std::vector <CLASS_Atlas> TYPE_Atlas;
  TYPE_Atlas Atlas;
  const Uint8* Keys;
  int AtlasCnt;
  SDL_Window* Window=NULL;
  SDL_Renderer* Renderer=NULL;
  SDL_Event Event;
  void Init(const char* Title,int X,int Y,int Width,int Height,Uint32 WindowFlags,Uint32 RendererFlags,int CursorStat);
  void Destroy();
  void LoadAtlas(const char* Path,int MaxTex);
  int GetAtlasCnt();
};

#endif

















































