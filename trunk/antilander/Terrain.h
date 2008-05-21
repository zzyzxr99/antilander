#ifndef _TERRAIN_H
#define _TERRAIN_H

#include "Constants.h"
#include "Structs.h"

// EJR Added for SDL_Surface
#include "SDL.h"

class Terrain
{
private:
	
	Point mTerrainPts [kMaxTpts];
	Point mPadPts [kMaxPpts];
	int mNumTPts;
	int mNumPadPts;
	
public:
	
	Terrain();
	~Terrain();
	void InitTerrain();
	void InitPadPoints();

	int GetNumPadPts();
	int GetTPts();
	Point *TerrainPts();
	Point *PadPts();

};

#endif // end _Terrain_H
