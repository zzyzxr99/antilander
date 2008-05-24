// Level.cpp

#include "Structs.h"
#include "Level.h"
#include <vector>
using namespace std;

Level::Level( )
{
    mNumLndrLvl    = 0;
    mNumLndrScr    = 0;
    mLndrPersist   = false;
    mLndrDescRate  = 0;
    mNumPad        = 0;
    mNumTerPt      = 0;
    mNumMissile    = 0;
    mMissileSpd    = 0.0F;
    mGunStartPad   = 0;
    mGunMoves      = false;
    mGunMoveRnd    = false;
    mEndGamePadOcc = 0;
    mGunReload     = 0.0F;
    mExpRad        = 0.0F;
    mExpRate       = 0.0F;
    mFrat          = 0.0F;
}

Level::~Level( )
{ }

unsigned short Level::GetNumLndrLvl( )
{
    return mNumLndrLvl;
}

unsigned short Level::GetNumLndrScr( )
{
    return mNumLndrScr;
}

bool Level::GetLndrPersist( )
{
    return mLndrPersist;
}

unsigned short Level::GetLndrDescRate( )
{
    return mLndrDescRate;
}

unsigned short Level::GetNumPad( )
{
    return mNumPad;
}

vector<Point>* Level::GetPadpt( )
{
    return &mPadPt;
}

unsigned short Level::GetNumTerPt( )
{
    return mNumTerPt;
}

vector<Point>* Level::GetTerPt()
{
    return &mTerPt;
}

unsigned short Level::GetNumMissile( )
{
    return mNumMissile;
}

float Level::GetMissileSpd( )
{
    return mMissileSpd;
}

unsigned short Level::GetGunStartPad( )
{
    return mGunStartPad;
}

bool Level::GetGunMoves( )
{
    return mGunMoves;
}

bool Level::GetGunMoveRnd( )
{
    return mGunMoveRnd;
}

unsigned short Level::GetEndGamePadOcc( )
{
    return mEndGamePadOcc;
}

float Level::GetGunReload( )
{
    return mGunReload;
}

float Level::GetExpRad( )
{
    return mExpRad;
}

float Level::GetExplRate( )
{
    return mExpRate;
}

bool Level::GetFrat( )
{
    return mFrat;
}

void Level::SetNumLndrLvl( unsigned short Landers )
{
}
void Level::SetNumLndrScr( unsigned short Landers )
{
}

void Level::SetLndrPersist( bool persist )
{
}

void Level::SetLndrDescRate( unsigned short rate )
{
}

void Level::SetNumPad( unsigned short pads )
{
}

void Level::SetNumTerPt( unsigned short points )
{
}

void Level::SetNumMissile( unsigned short missiles )
{
}

void Level::SetMissileSpd( float speed )
{
}

void Level::SetGunStartPad( unsigned short pad )
{
}

void Level::SetGunMoves( bool moves )
{
}

void Level::SetGunMoveRnd( bool moveRnd )
{
}

void Level::SetEndGamePadOcc( unsigned short pads )
{
}

void Level::SetGunReload( float reloadTime )
{
}

void Level::SetExpRad( float radius )
{
}

void Level::SetExpRate( float rate )
{
}

void Level::SetFrat( bool frat )
{
}

void LoadLevel( )
{
}

void SaveLevel( )
{
}