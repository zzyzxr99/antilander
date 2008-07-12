#ifndef _SEFFECT_H
#define _SEFFECT_H

#include "SDL_Mixer.h"

class SEffect
{

private:
    Mix_Chunk *mChunk;
    bool mLoaded;

public:
    SEffect();
    ~SEffect();
    bool Load(const char *file);
    bool Loaded();
    Mix_Chunk *PtrChunk();
};



#endif // end _SEFFECT_H