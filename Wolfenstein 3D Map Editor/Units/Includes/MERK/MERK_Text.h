#ifndef MERK_Text
#define MERK_Text

class CLASS_Text
{
 public:
  int Width,Height;
  TTF_Font* Font=NULL;
  SDL_Color Color;
  void Init(const char* Path,int Width,int Height);
  void Destroy();
		void Out(char* Text,int X,int Y,SDL_Renderer* Renderer);
  void OutNum(char* Text,int Num,int X,int Y,SDL_Renderer* Renderer);
  void SetColor(int R,int G,int B);
  SDL_Color GetColor();
};

#endif

















































