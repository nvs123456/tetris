#ifndef _AUDIO_H
#define _AUDIO_H
#include<SDL_mixer.h>

Mix_Chunk* m=NULL;
Mix_Chunk* c=NULL;
//Mix_Chunk* m=Mix_LoadWAV("move.wav");
//Mix_Chunk* c=Mix_LoadWAV("clear.wav");

void move_sound()
{
    Mix_PlayChannel(-1,m,0);
}
void clear_sound()
{
    Mix_PlayChannel(-1,c,0);
}
#endif // _AUDIO_H
