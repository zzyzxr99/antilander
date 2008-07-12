#include "SEffect.h"
#include "SDL_Mixer.h"
#include <iostream>
using namespace std;

SEffect::SEffect()
{
    mChunk= NULL;
    mLoaded= false;
}

SEffect::~SEffect()
{
    if (mChunk)
    {
        Mix_FreeChunk(mChunk);
        mChunk= NULL;
    }
}

bool SEffect::Load(const char *fn)
{
    if (mLoaded)
    {
        Mix_FreeChunk(mChunk);
        mChunk= NULL;
        mLoaded= false;
    }

    mChunk= Mix_LoadWAV(fn);
    if (mChunk == NULL)
    {
        mLoaded= false;
#ifndef _RELEASE
        cout << "Failed to load WAV " << fn << endl;
#endif
    }
    else
    {
        mLoaded= true;
    }
    return mLoaded;
}

Mix_Chunk *SEffect::PtrChunk()
{
    return mChunk;
}

bool SEffect::Loaded()
{
    return mLoaded;
}