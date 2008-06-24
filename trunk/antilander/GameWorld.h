#ifndef _GAMEWORLD_H
#define _GAMEWORLD_H

extern "C" 
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}
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
    GameStatusType mGameMode;
	EditStatusType mEditMode;
	static Level mEditLevel;
	static Level mCurrentLevel;
    USINT mNumLndrLvl;
    USINT mNumLndrScr;
    bool mLndrPersist;
    USINT mNumMissile;
    USINT mNumBomb;
    bool mGunMoves;
    bool mGunMoveRnd;
    USINT mEndGamePadOcc;
    bool mFrat;
	int lvlCtr;
	int mNumLndrsToGo;
	int mNumLndrsLanded;
	//console and lua variables
	char ch;
	static lua_State* luaVM;
	static int command;
	static float value;
	Level* mTempLevel;
	//Score	
	int TotalScore;


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

	bool SplashRunning( );
    void SpawnExplosion( Point sLoc );
    bool MissileSect(vector<Point>::iterator TerArr, Point MissNose, Vect Direction);
	void LanderLanded ();

	bool LeftMouseHeld();
	bool RightMouseHeld();
	void SetGameStatus(GameStatusType status);
	void SetEditStatus(EditStatusType status);

	GameStatusType GetGameStatus();
	EditStatusType GetEditStatus();
	void AddEditLevelPoint(Point p);
	void AddEditPadPoint(Point p);
	void EndEditLvlPts(Point p);
    void SpawnLander();
    void InitLevel( );
    void ResetTimers( );
    void InitEditLvl( );
    vector<Lander>* GetLanders( );
    USINT GetNumLndrScr( );

	string GetLevName (int num);
	Level* GetEditLevel();
	Level* GetCurrentLevel();
	Gunship* GetGunship();

   
	int PointCheck();
	void CheckSpawnLander();
	//console commands
	bool IsConsole();
	string DoConsoleIn();
	void DoLua();

	//lua test commands
	static void StartLua();
	static int l_Action(lua_State* LVM);
	
	//Total Score
	int GetScore();
	void AddScore(int Score, int Val);
	
	void CheckPause();
};

#endif // end _GAMEWORLD_H
