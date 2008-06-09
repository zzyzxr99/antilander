#ifndef _GAMEWORLD_H
#define _GAMEWORLD_H


#include "Render.h"
#include "Lander.h"
#include "Gunship.h"
#include "Missile.h"
#include "Bomb.h"
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
	ALTimer mGameStepper;
	vector<Lander> mLanders;
	vector<Missile> mMissiles;
    vector<Bomb> mBombs;
    vector<Explosion> mExplosions;
	Gunship mPlayerShip;
	Terrain mGameTerrain;
	void InitEverything();
	void InitMissiles();
	void InitLanders();
    GameStatusType mGameMode;
	EditStatusType mEditMode;
	Level mEditLevel;
	Level mCurrentLevel;
    unsigned short mNumLndrLvl;
    unsigned short mNumLndrScr;
    bool mLndrPersist;
    unsigned short mNumMissile;
    unsigned short mNumBomb;
    bool mGunMoves;
    bool mGunMoveRnd;
    unsigned short mEndGamePadOcc;
    bool mFrat;
	int lvlCtr;
	char ch;
	

public:
	GameWorld();
	~GameWorld();
    void DrawEverything();
	void EditDrawEverything();
	Render* GetRender( );
	void SpawnMissile();
    void SpawnBomb();
	void StartGameStepper();
    bool CheckTick( );
    void UpdateEverything( );
	bool FireMissile();
    bool FireBomb(); // 
    void TestSpawnExplosion();// onlt for spawning explosion at mouse on right click
    bool SplashRunning( );
    void SpawnExplosion( Point sLoc );
    bool MissileSect(vector<Point>::iterator TerArr, Point MissNose, Vect Direction);

	bool LeftMouseHeld();
	bool RightMouseHeld();
	void SetGameStatus(GameStatusType status);
	void SetEditStatus(EditStatusType status);
	GameStatusType GetGameStatus();
	EditStatusType GetEditStatus();
	void AddEditLevelPoint(Point p);
	void EndEditLvlPts(Point p);
    void SpawnLander();
    void InitLevel( );
    void InitEditLvl( );
    vector<Lander>* GetLanders( );
    unsigned short GetNumLndrScr( );

	string GetLevName (int num);
	Level* GetLevel();

    void TestSaveLoadLevel();
	int PointCheck();

	//lua commands
	
};

#endif // end _GAMEWORLD_H
