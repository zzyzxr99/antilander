#ifndef _GAMEWORLD_H
#define _GAMEWORLD_H

#include "Render.h"
#include "Lander.h"
#include "Gunship.h"
#include "Missile.h"
#include "Terrain.h"
#include "Explosion.h"
#include "ALTimer.h"
#include <vector>
using namespace std;

class GameWorld
{
private:
    Render mRender;
    bool mStarted;
	unsigned long mLastTimeStamp;
	ALTimer mGameStepper;
	float mLastElapsedTime;
	vector<Lander> mLanders;
	vector<Missile> mMissiles;
    vector<Explosion> mExplosions;
	Gunship mPlayerShip;
	Terrain mGameTerrain;
	void InitEverything();
	void InitMissiles();
	void InitLanders();
	void SpawnLander();

public:
	GameWorld();
	~GameWorld();
    void DrawEverything();
	Render* GetRender( );
	void SpawnMissile();
	void StartGameStepper();
    void Timestamp( );
    bool CheckTick( );
    void UpdateEverything( );
	bool FireMissile();
    bool TestFireExplosion(); // only for testing exploison on rightclick
    void TestSpawnExplosion();// onlt for spawning explosion at mouse on right click
    bool SplashRunning( );
    void SpawnExplosion( Point sLoc );
	bool MissileSect(Point * TerArr, Point MissNose, Vect Direction);

	bool LeftMouseHeld();
	bool RightMouseHeld();
};

#endif // end _GAMEWORLD_H
