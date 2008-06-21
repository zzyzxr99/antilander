// Level.h
#ifndef _LEVEL_H
#define _LEVEL_H
#include "Structs.h"
#include "Constants.h"
#include <vector>
#include <string>

using namespace std;

class Level
{
private:

    USINT mNumLndrLvl;
    USINT mNumLndrScr;
    bool mLndrPersist;         
    static float mLndrDescRate;       
    USINT mNumPad;    
    vector<Point> mPadPt;      // !
    USINT mNumTerPt;  // !
    vector<Point> mTerPt;      // !
    USINT mNumMissile;
    static float mMissileSpd;             
    static USINT mGunStartPad; //!
    bool mGunMoves;				 //-
    bool mGunMoveRnd;			 //- 
    USINT mEndGamePadOcc; //!
    static float mGunReload;			   
    float mExpRad;				   //!-
    float mExpRate;                //!-
    bool mFrat;					   //!	
    USINT mNumBomb;       
    static float mBombMxSpd;			  	
    static float mBombAcc;				   
    static float mBombRad;				   
    static float mBombReloadTime;
	
public:

    Level( );
    ~Level( );

    USINT GetNumLndrLvl( );
    USINT GetNumLndrScr( );
    bool GetLndrPersist( );
    float GetLndrDescRate( );
    USINT GetNumPad( );
    vector<Point>* GetPadpt( );				//need this too
    USINT GetNumTerPt( );
    vector<Point>* GetTerPt( );				//need this
    USINT GetNumMissile( );
    float GetMissileSpd( );
    USINT GetGunStartPad( );
    bool GetGunMoves( );
    bool GetGunMoveRnd( );
    USINT GetEndGamePadOcc( );
    float GetGunReload( );
    float GetExpRad( );
    float GetExplRate( );
    bool GetFrat( );
    USINT GetNumBomb( );
    float GetBombMxSpd( );
    float GetBombAcc( );
    float GetBombRad( );
    float GetBombReloadTime( );

    void SetNumLndrLvl( USINT landers );
    void SetNumLndrScr( USINT landers );
    void SetLndrPersist( bool persist );
    static void SetLndrDescRate( float rate );
    void SetNumPad( USINT pads );
    void SetNumTerPt( USINT points );
    void SetNumMissile( USINT missiles );
    static void SetMissileSpd( float speed );
    static void SetGunStartPad( USINT pad );
    void SetGunMoves( bool moves );
    void SetGunMoveRnd( bool moveRnd );
    void SetEndGamePadOcc( USINT pads );
    static void SetGunReload( float reloadTime );
    void SetExpRad( float radius );
    void SetExpRate( float rate );
    void SetFrat( bool frat );
    void SetNumBomb( USINT num );
    static void SetBombMxSpd( float spd );
    static void SetBombAcc( float acc );
    static void SetBombRad( float rad );
    static void SetBombReloadTime( float t );
	void ClearLevel();

    void LoadLevel( string LevString );
    void SaveLevel( string LevString );
    void EJRTestSaveLevel(string filename);
    void EJRTestLoadLevel(string filename);

	void AddPoint(Point p);
	void AddPad(Point p);
	void MakePadPtsFromTerrainPts();

    void Clone( Level* srcLvl );
    Level* GetPtr( );
};

#endif // _LEVEL_H
