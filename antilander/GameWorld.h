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
#include "Level.h"
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
    GameStatusType mGameMode;
	Level mEditLevel;
	Level mCurrentLevel;

public:
	GameWorld();
	~GameWorld();
    void DrawEverything();
	void EditDrawEverything();
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
	void SetGameStatus(GameStatusType status);
	GameStatusType GetGameStatus();
	void AddEditLevelPoint(Point p);
};

#endif // end _GAMEWORLD_H
