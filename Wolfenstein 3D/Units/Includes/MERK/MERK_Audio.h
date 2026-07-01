#ifndef MERK_Audio
#define MERK_Audio

#include <SDL_mixer/SDL_mixer.h>

class CLASS_Audio
{
 public:
  typedef Mix_Music* TYPE_Music;
  typedef class CLASS_Sound
  {
   public:
    Mix_Chunk* Data;
    int Channel; 
  };
  void Init();
  void Destroy();
  TYPE_Music LoadMusic(const char* Path);
  void UnloadMusic(TYPE_Music &Music);
  void PlayMusic(TYPE_Music Music);
  void PauseMusic();
  void ResumeMusic();
  void StopMusic();
  CLASS_Sound LoadSound(const char* Path);
  void UnloadSound(CLASS_Sound &Sound);
  void PlaySound(CLASS_Sound Sound);
  bool IsSoundPlaying(CLASS_Sound Sound);
};

#endif

















































