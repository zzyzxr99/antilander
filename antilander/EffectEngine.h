#ifndef _EFFECTENGINE_H
#define _EFFECTENGINE_H

#include "Constants.h"
#include "SEffect.h"

class EffectEngine
{

private:
    SEffect mEffects[knLastEffect];
    bool mStarted;
    
    int FindChannel();

public:
    EffectEngine();
    ~EffectEngine();

    bool Init();
    bool LoadEffectSlot(SoundEffectType slot, const char *fn);
    void PlayEffect(SoundEffectType src, int channel);
    void PlayLoop(SoundEffectType src, int channel);
    void PlayFadeIn(SoundEffectType src, int channel, float length);
    void PlayFadeOut(int channel, float length);
    void Shutdown();
    void Halt(int channel);
    bool InUse(int channel);
};


#endif _EFFECTENGINE_H