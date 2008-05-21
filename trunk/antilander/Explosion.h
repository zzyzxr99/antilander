#ifndef _EXPLOSION_H
#define _EXPLOSION_H

#include "SDL.h"
#include "Structs.h"

class Explosion
{
private:
    ExplosionStatusType mStatus;
    Point mDrawLoc;
    float mMaxRadius;
    float mCurrentRadius;
    float mExpansionRate;
    SDL_Color mInnerColor;
    SDL_Color mOuterColor;
    
public:
    Explosion();
    Explosion( Point sLoc );
    Explosion(Point sLoc, float radius, float expandRate, SDL_Color innnerCol, SDL_Color outerCol);
    ~Explosion();
    Point GetLocation();
    float GetMaxRadius();
    float GetCurrentRadius();
    float GetExpansionRate();
    ExplosionStatusType GetStatus();
    SDL_Color GetOuterColor();
    SDL_Color GetInnerColor();
    ExplosionStatusType Update(float elaspedTime);
    void SetStatus(ExplosionStatusType stat);
};

#endif // end _EXPLOSION_H