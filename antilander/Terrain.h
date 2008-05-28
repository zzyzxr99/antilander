#ifndef _TERRAIN_H
#define _TERRAIN_H

#include "Constants.h"
#include "Structs.h"
#include <vector>
#include "SDL.h"

class Terrain
{
private:
	
	vector<Point> mTerrainPts;
    vector<Point> mPadPts;
    vector<BBox> mTerrainBoxes;
	int mNumTPts;
	int mNumPadPts;

	
public:
	
	Terrain();
	~Terrain();
	void InitTerrain();
    void InitTerrain( vector<Point>* vtp );
	void InitPadPoints( );
    void InitPadPoints( vector<Point>* vpp );
	float InitTbox();
	int GetNumPadPts();
    void SetNumPadPts( int pads );
    void SetNumTPts( int tpts );
	int GetTPts();
	vector<Point>::iterator TerrainPts();
    vector<Point>::iterator PadPts();
    vector<BBox>::iterator TerBox();
    
};

#endif // end _Terrain_H
