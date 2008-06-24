#include "Constants.h"
#include "Terrain.h"
// EJR added SDL.H to test Draw Functions - its getting messy
#include "SDL_gfxPrimitives.h"
#include <vector>
using namespace std;


//Definition

Terrain::Terrain()
{
	//initialize all the members of the variable

    // Terrain Point already cleared in vector constructor
	/*for (int i=0;i<kMaxTpts;i++)
	{
		mTerrainPts[i].x=0;
		mTerrainPts[i].y=0;
	}*/

    // Padpoints vector already cleared in vector constructor
	//for(int i=0;i<kMaxPpts;i++)
	//{
	//	mPadPts[i].x=0;
	//	mPadPts[i].y=0;

	//}
	// Reserve Initial size of vector for Terrain, Pad Points, BBoxes
	mTerrainPts.reserve(kInitialTPts);
    mPadPts.reserve(kInitialPPts);
    mTerrainBoxes.reserve(kInitialTPts);

}
Terrain::~Terrain()
{
	//any new operators must have delete matches here
}

int Terrain::GetNumPadPts()
{
	return mNumPadPts;
}

void Terrain::SetNumPadPts( int pads )
{
    mNumPadPts = pads;
}

void Terrain::SetNumTPts( int tpts )
{
    mNumTPts = tpts;
}

int Terrain::GetTPts()
{
	return mNumTPts;
}

vector<Point>::iterator Terrain::TerrainPts()
{
	return mTerrainPts.begin();
}

vector<Point>::iterator Terrain::PadPts()
{
	return mPadPts.begin();
}

void Terrain::InitTerrain()
{
    // *************************************************************************
    // intialize the number of Terrain points so we can loop thru them to draw
    mTerrainPts.clear( );
    Point tp;
	tp.x= 0;
	tp.y= 400;
    mTerrainPts.push_back(tp);
	tp.x= 35;
	tp.y= 400;
    mTerrainPts.push_back(tp);
	tp.x= 70;
	tp.y= 320;
	mTerrainPts.push_back(tp);
	tp.x= 104;
	tp.y= 320;
	mTerrainPts.push_back(tp);
	tp.x= 124;
	tp.y= 386;
	mTerrainPts.push_back(tp);
	tp.x= 186;
	tp.y= 343;
	mTerrainPts.push_back(tp);
	tp.x= 220;
	tp.y= 380;
	mTerrainPts.push_back(tp);
	tp.x= 250;
	tp.y= 380;
	mTerrainPts.push_back(tp);
	tp.x= 320;
	tp.y= 227;
	mTerrainPts.push_back(tp);
	tp.x= 378;
	tp.y= 227;
	mTerrainPts.push_back(tp);
	tp.x= 450;
	tp.y= 193;
	mTerrainPts.push_back(tp);
	tp.x= 510;
	tp.y= 202;
	mTerrainPts.push_back(tp);
	tp.x= 540;
	tp.y= 360;
	mTerrainPts.push_back(tp);
	tp.x= 639; //639 x 479 is max for 640 x 480 resolution
	tp.y= 360;
    mTerrainPts.push_back(tp);
	
    this->mNumTPts= mTerrainPts.size();
    vector<Point>::iterator iterTPts= mTerrainPts.begin();
    BBox boxTPts;
	for (int i= 0; i < (mNumTPts-1); i++)
	{
		boxTPts.x = iterTPts[i].x;
		boxTPts.y = iterTPts[i].y;
		boxTPts.w = iterTPts[i+1].x - iterTPts[i].x;
		boxTPts.h = iterTPts[i+1].y - iterTPts[i].y;
        mTerrainBoxes.push_back(boxTPts);
	}
}

void Terrain::InitTerrain( vector<Point>* vtp )
{
    mTerrainPts.clear( );
    vector<Point>::iterator srcIter = vtp->begin( );
    for ( ; srcIter != vtp->end( ); srcIter++ )
    {
        mTerrainPts.push_back( *srcIter );
    }
    this->mNumTPts= mTerrainPts.size();
    vector<Point>::iterator iterTPts= mTerrainPts.begin();
    BBox boxTPts;
	for (int i= 0; i < (mNumTPts-1); i++)
	{
		boxTPts.x = iterTPts[i].x;
		boxTPts.y = iterTPts[i].y;
		boxTPts.w = iterTPts[i+1].x - iterTPts[i].x;
		boxTPts.h = iterTPts[i+1].y - iterTPts[i].y;
        mTerrainBoxes.push_back(boxTPts);
	}
}

void Terrain::InitPadPoints()
{

    // EJR hard coded still - can be exceptions
    mPadPts.clear( );
    Point pTemp;
    pTemp.x= (mTerrainPts[0].x + mTerrainPts[1].x)/2;
    pTemp.y= (mTerrainPts[0].y);
    mPadPts.push_back(pTemp);

    pTemp.x= (mTerrainPts[2].x + mTerrainPts[3].x)/2;
    pTemp.y= (mTerrainPts[2].y);
    mPadPts.push_back(pTemp);

    pTemp.x= (mTerrainPts[6].x + mTerrainPts[7].x)/2;
    pTemp.y= (mTerrainPts[6].y);
    mPadPts.push_back(pTemp);

    pTemp.x= (mTerrainPts[8].x + mTerrainPts[9].x)/2;
    pTemp.y= (mTerrainPts[8].y);
    mPadPts.push_back(pTemp);

    pTemp.x= (mTerrainPts[12].x + mTerrainPts[13].x)/2;
    pTemp.y= (mTerrainPts[12].y);
    mPadPts.push_back(pTemp);

    /*
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
    */
}

void Terrain::InitPadPoints( vector<Point>* vpp )
{
    mPadPts.clear( );
    vector<Point>::iterator srcIter = vpp->begin( );
    for ( ; srcIter != vpp->end( ); srcIter++ )
    {
        mPadPts.push_back( *srcIter );
    }
}

vector<BBox>::iterator Terrain::TerBox()
{
	return mTerrainBoxes.begin();
}
