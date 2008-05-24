// Level.cpp
#include "Structs.h"
#include "Level.h"
#include <vector>
#include <fstream>
#include <iostream>
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

void Level::SetNumLndrLvl( unsigned short landers )
{
    mNumLndrLvl = landers;
}
void Level::SetNumLndrScr( unsigned short landers )
{
    mNumLndrScr = landers;
}

void Level::SetLndrPersist( bool persist )
{
    mLndrPersist = persist;
}

void Level::SetLndrDescRate( unsigned short rate )
{
    mLndrDescRate = rate;
}

void Level::SetNumPad( unsigned short pads )
{
    mNumPad = pads;
}

void Level::SetNumTerPt( unsigned short points )
{
    mNumTerPt = points;
}

void Level::SetNumMissile( unsigned short missiles )
{
    mNumMissile = missiles;
}

void Level::SetMissileSpd( float speed )
{
    mMissileSpd = speed;
}

void Level::SetGunStartPad( unsigned short pad )
{
    mGunStartPad = pad;
}

void Level::SetGunMoves( bool moves )
{
    mGunMoves = moves;
}

void Level::SetGunMoveRnd( bool moveRnd )
{
    mGunMoveRnd = moveRnd;
}

void Level::SetEndGamePadOcc( unsigned short pads )
{
    mEndGamePadOcc = pads;
}

void Level::SetGunReload( float reloadTime )
{
    mGunReload = reloadTime;
}

void Level::SetExpRad( float radius )
{
    mExpRad = radius;
}

void Level::SetExpRate( float rate )
{
    mExpRate = rate;
}

void Level::SetFrat( bool frat )
{
    mFrat = frat;
}

void Level::LoadLevel( )
{
	char ch;
	ifstream infile("insettings.txt");
	while (infile)
	{
		while(!infile.eof())
		{	
			infile.get(ch);
			cout << ch;
		}
	}
}

void Level::SaveLevel( )
{
}

void Level::AddPoint(Point p)
{
	mTerPt.push_back (p);
	mNumTerPt= mTerPt.size();
}