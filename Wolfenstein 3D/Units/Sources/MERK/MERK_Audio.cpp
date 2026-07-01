#include <vector>
#include <SDL/SDL.h>
#include <SDL_mixer/SDL_mixer.h>
#include <MERK/MERK_Misc.h>
#include <MERK/MERK_Audio.h>

void CLASS_Audio::Init()
{
 if (SDL_Init(SDL_INIT_AUDIO)<0)
 {
  Misc.ErrorHandle("Failed to initialize Audio");
 }
 if (Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,8192)<0)
 {
  Misc.ErrorHandle("Failed to open Audio");
 }
 Mix_AllocateChannels(0);
}

void CLASS_Audio::Destroy()
{
 Mix_Quit();
}

CLASS_Audio::TYPE_Music CLASS_Audio::LoadMusic(const char* Path)
{
 Mix_Music* Music=NULL;
 Music=Mix_LoadMUS(Path);
 if (Music==NULL)
 {
  Misc.ErrorHandle("Failed to load Music");
 }
 return Music;
}

void CLASS_Audio::UnloadMusic(TYPE_Music &Music)
{
 Mix_FreeMusic(Music);
 Music=NULL;
}

void CLASS_Audio::PlayMusic(TYPE_Music Music)
{
 Mix_PlayMusic(Music,-1);
}

void CLASS_Audio::PauseMusic()
{
 Mix_PauseMusic();
}

void CLASS_Audio::ResumeMusic()
{
 Mix_ResumeMusic();
}

void CLASS_Audio::StopMusic()
{
 Mix_HaltMusic();
}

#include <iostream>

CLASS_Audio::CLASS_Sound CLASS_Audio::LoadSound(const char* Path)
{
 CLASS_Sound Sound;
 Sound.Data=NULL;
 Sound.Data=Mix_LoadWAV(Path);
 if (Sound.Data==NULL)
 {
  Misc.ErrorHandle("Failed to load Sound");
 }
 Sound.Channel=Mix_AllocateChannels(-1);
 Mix_AllocateChannels(Mix_AllocateChannels(-1)+1);
 return Sound;
}

void CLASS_Audio::UnloadSound(CLASS_Sound &Sound)
{
 Mix_FreeChunk(Sound.Data);
 Sound.Data=NULL;
}

void CLASS_Audio::PlaySound(CLASS_Sound Sound)
{
 Mix_PlayChannel(Sound.Channel,Sound.Data,0);
}

bool CLASS_Audio::IsSoundPlaying(CLASS_Sound Sound)
{
 if (!Mix_Playing(Sound.Channel))
 {
  return false;
 }
 else
 {
  return true;
 }
}

//eof

















































