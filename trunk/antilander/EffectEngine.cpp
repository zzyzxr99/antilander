#include "EffectEngine.h"
#include <iostream>
using namespace std;


EffectEngine::EffectEngine()
{

    // mEffects array intialize by SEffect constructor
    mStarted= false;
}

EffectEngine::~EffectEngine()
{
    // mEffects array deallocated by SEffect deconstructor
    if (mStarted)
    {
        Shutdown();
        mStarted= false;

    }
}

bool EffectEngine::Init()
{
    int mix_result;
    bool retval;

    mix_result= Mix_OpenAudio(kFrequency,kFormat,kListenChannels,kChunkSize);
    if (mix_result)
	{
#ifndef _RELEASE
		cout << "Mix_OpenAudio failed to open mixer!" << endl;
#endif
		retval= false;
	}
    else
    {

        int alloc_result= Mix_AllocateChannels(kMAXChannels);
        if (alloc_result < kMAXChannels)
        {
#ifndef _RELEASE
            cout << "Mix_AllocateChannels failed to allocate " << knLastEffect << " channels." << endl;
#endif
            retval= false;
        }
        else
        {
            retval|= LoadEffectSlot(knSEMissileLaunch, "data\\effects\\tMissileLaunch1.wav");
            retval|= LoadEffectSlot(knSEMissileExplosion, "data\\effects\\tLanderExplode3.wav");
            retval|= LoadEffectSlot(knSELanderExplosion, "data\\effects\\tLanderExplode2.wav");
            retval|= LoadEffectSlot(knSELanderSpawn, "data\\effects\\tLanderSpawn1.wav");
            retval|= LoadEffectSlot(knSEBombExplosion, "data\\effects\\tBombExplosion.wav");
            retval|= LoadEffectSlot(knSEBombLaunch, "data\\effects\\tBombLaunch.wav");
            retval|= LoadEffectSlot(knSLMenu, "data\\loops\\tMenuMusic.wav");
            retval|= LoadEffectSlot(knSEMenuClick, "data\\effects\\MenuClick.wav");
			retval|= LoadEffectSlot(knSEIntroSound,"data\\effects\\intro1.wav");
			retval|= LoadEffectSlot(knSEGameOver,"data\\effects\\gameover3.wav");
			retval|= LoadEffectSlot(knSELevelClear,"data\\effects\\LevelComplete.wav");
			//retval|= LoadEffectSlot(knLastEffect,"");




			


            Mix_Volume(-1,kDefaultVolume);
        }

    }
    mStarted= retval;
    return retval;
 }

void EffectEngine::Shutdown()
{
    if (mStarted)
    {
        Mix_CloseAudio();
        mStarted= false;
    }
}

bool EffectEngine::LoadEffectSlot(SoundEffectType slot, const char *fn)
{
    return mEffects[slot].Load(fn);
}

// channel -1 picks the next available channel
void EffectEngine::PlayEffect(SoundEffectType src, int channel)
{
    if (mEffects[src].Loaded())
    {
        if (channel == -1)
        {
            channel= FindChannel();
        }
        if (channel != -1)
        {
            if (  src == knSEMissileLaunch
               || src == knSEBombLaunch
               || src == knSELanderSpawn )
            {
                Mix_Volume( channel,
                            kPriorityVolume );
            }
            else
            {
                Mix_Volume( channel,
                            kDefaultVolume );
            }
            int play_result= Mix_PlayChannel(channel,mEffects[src].PtrChunk(),0);
            if (play_result == -1)
            {
#ifndef _RELEASE
                cout << "Failed to mix chunk on channel " << src << endl;
#endif 
            }
        }
    }
}

void EffectEngine::PlayLoop(SoundEffectType src, int channel)
{
    if (mEffects[src].Loaded())
    {
        int play_result= Mix_PlayChannel(src,mEffects[src].PtrChunk(),-1);
        if (play_result == -1)
        {
#ifndef _RELEASE
            cout << "Failed to mix chunk looped on channel " << src << endl;
#endif 
        }
        
    }
}

void EffectEngine::Halt(int channel)
{
    if ((channel >= 0) && (channel < kMAXChannels))
    {
        Mix_HaltChannel(channel);
    }
}

bool EffectEngine::InUse(int channel)
{
    if ((channel >= 0) && (channel < kMAXChannels))
    {
        return (Mix_Playing(channel) != 0) ;
    }
    return false;
}

int EffectEngine::FindChannel()
{
    int i= kReservedChannels;
    while ((i < kMAXChannels) && InUse(i))
    {
        i++;
    }

    if (i < kMAXChannels)
    {
        return i;
    }
    return -1;
}

void EffectEngine::PlayFadeIn(SoundEffectType src, int channel, float length)
{
	if(Mix_FadeInChannel(channel,mEffects[src].PtrChunk(),-1,(int)length*1000) == -1)
	{
		cout << "Failure - Sound Effect not loaded" << endl;
	}
}

void EffectEngine::PlayFadeOut(int channel, float length)
{
	if ((channel >= 0) && (channel < kMAXChannels))
	{
		int res = Mix_FadeOutChannel(channel,(int)length*1000);
	}
}