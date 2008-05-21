#include "Constants.h"
#include "Terrain.h"
// EJR added SDL.H to test Draw Functions - its getting messy
#include "SDL_gfxPrimitives.h"


//Definition

Terrain::Terrain()
{
	//initialize all the members of the variable
	for (int i=0;i<kMaxTpts;i++)
	{
		mTerrainPts[i].x=0;
		mTerrainPts[i].y=0;
	}

	for(int i=0;i<kMaxPpts;i++)
	{
		mPadPts[i].x=0;
		mPadPts[i].y=0;

	}
	
	

}
Terrain::~Terrain()
{

	//any new operators must have delete matches here

}

int Terrain::GetNumPadPts()
{
	return mNumPadPts;
}

int Terrain::GetTPts()
{
	return mNumTPts;
}

Point *Terrain::TerrainPts()
{
	return &mTerrainPts[0];
}

Point *Terrain::PadPts()
{
	return &mPadPts[0];
}

void Terrain::InitTerrain()
{
    // *************************************************************************
    // intialize the number of Terrain points so we can loop thru them to draw
    this->mNumTPts= 14;
	this->mTerrainPts[0].x= 0;
	this->mTerrainPts[0].y= 400;
	this->mTerrainPts[1].x= 35;
	this->mTerrainPts[1].y= 400;
	this->mTerrainPts[2].x= 70;
	this->mTerrainPts[2].y= 320;
	this->mTerrainPts[3].x= 104;
	this->mTerrainPts[3].y= 320;
	this->mTerrainPts[4].x= 124;
	this->mTerrainPts[4].y= 386;
	this->mTerrainPts[5].x= 186;
	this->mTerrainPts[5].y= 343;
	this->mTerrainPts[6].x= 220;
	this->mTerrainPts[6].y= 380;
	this->mTerrainPts[7].x= 250;
	this->mTerrainPts[7].y= 380;
	this->mTerrainPts[8].x= 320;
	this->mTerrainPts[8].y= 227;
	this->mTerrainPts[9].x= 378;
	this->mTerrainPts[9].y= 227;
	this->mTerrainPts[10].x= 450;
	this->mTerrainPts[10].y= 193;
	this->mTerrainPts[11].x= 510;
	this->mTerrainPts[11].y= 202;
	this->mTerrainPts[12].x= 540;
	this->mTerrainPts[12].y= 360;
	this->mTerrainPts[13].x= 639; //639 x 479 is max for 640 x 480 resolution
	this->mTerrainPts[13].y= 360;
}



void Terrain::InitPadPoints()
{
	mPadPts[0].x= (mTerrainPts[0].x + mTerrainPts[1].x) / 2;
	mPadPts[0].y= (mTerrainPts[0].y);
	mPadPts[1].x= (mTerrainPts[2].x + mTerrainPts[3].x) / 2;
	mPadPts[1].y= (mTerrainPts[2].y);
	mPadPts[2].x= (mTerrainPts[6].x + mTerrainPts[7].x) / 2;
	mPadPts[2].y= (mTerrainPts[6].y);
	mPadPts[3].x= (mTerrainPts[8].x + mTerrainPts[9].x) / 2;
	mPadPts[3].y= (mTerrainPts[8].y);
	mPadPts[4].x= (mTerrainPts[12].x + mTerrainPts[13].x) / 2;
	mPadPts[4].y= (mTerrainPts[12].y);
}



/*
void Terrain::StevenDrawTerrain(SDL_Surface* surf)
{
	for (int i= 0; i < (mNumTPts-1); i++)
	{
		aalineRGBA(surf, mTerrainPts[i].x, mTerrainPts[i].y,mTerrainPts[i+1].x, mTerrainPts[i+1].y, 255, 255, 255, 255);
	}
}
*/