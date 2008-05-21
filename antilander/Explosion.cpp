#include "Constants.h"
#include "Explosion.h"

Explosion::Explosion()
{
    mStatus= knExplosionOccuring;
    mDrawLoc.x= 0;
    mDrawLoc.y= 0;
    mCurrentRadius= kExplosionStartRadiusDefault;
    mMaxRadius= kExplosionMaxRadiusDefault;
    mExpansionRate= kExplosionExpandRateDefault;
    mInnerColor= kExplosionInnerColorDefault;
    mOuterColor= kExplosionOuterColorDefault;
}

Explosion::Explosion( Point sLoc )
{
    mStatus= knExplosionOccuring;
    mDrawLoc = sLoc;
    mCurrentRadius= kExplosionStartRadiusDefault;
    mMaxRadius= kExplosionMaxRadiusDefault;
    mExpansionRate= kExplosionExpandRateDefault;
    mInnerColor= kExplosionInnerColorDefault;
    mOuterColor= kExplosionOuterColorDefault;
}

Explosion::Explosion(Point sLoc, float radius, float expandRate, SDL_Color innerCol, SDL_Color outerCol)
{
    mStatus= knExplosionOccuring;
    mDrawLoc= sLoc;
    mCurrentRadius= kExplosionStartRadiusDefault;
    mMaxRadius= radius;
    mExpansionRate= expandRate;
    mInnerColor= innerCol;
    mOuterColor= outerCol;
}

Explosion::~Explosion()
{
    // Any 'new' need matching 'delete'
}

Point Explosion::GetLocation()
{
    return mDrawLoc;
}

float Explosion::GetMaxRadius()
{
    return mMaxRadius;
}

float Explosion::GetCurrentRadius()
{
    return mCurrentRadius;
}
float Explosion::GetExpansionRate()
{
    return mExpansionRate;
}

SDL_Color Explosion::GetInnerColor()
{
    return mInnerColor;
}

SDL_Color Explosion::GetOuterColor()
{
    return mOuterColor;
}

ExplosionStatusType Explosion::GetStatus()
{
    return mStatus;
}

ExplosionStatusType Explosion::Update(float elapsedTime)
{
    if (mStatus == knExplosionOccuring)
    {
        mCurrentRadius+= mExpansionRate*elapsedTime;
        if (mCurrentRadius >= mMaxRadius)
        {
            mStatus= knExplosionDone;
        }
    }
    return mStatus;
}

void Explosion::SetStatus(ExplosionStatusType stat)
{
    mStatus= stat;
}