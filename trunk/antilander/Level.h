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
    float mLndrDescRate;       
    USINT mNumPad;    
    vector<Point> mPadPt;      // !
    USINT mNumTerPt;  // !
    vector<Point> mTerPt;      // !
    USINT mNumMissile;
    float mMissileSpd;             
    USINT mGunStartPad; //!
    bool mGunMoves;				 //-
    bool mGunMoveRnd;			 //- 
    USINT mEndGamePadOcc; //!
    float mGunReload;			   
    float mExpRad;				   //!-
    float mExpRate;                //!-
    bool mFrat;					   //!	
    USINT mNumBomb;       
    float mBombMxSpd;			  	
    float mBombAcc;				   
    float mBombRad;				   
    float mBombReloadTime;		
	
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
    void SetLndrDescRate( float rate );
    void SetNumPad( USINT pads );
    void SetNumTerPt( USINT points );
    void SetNumMissile( USINT missiles );
    void SetMissileSpd( float speed );
    void SetGunStartPad( USINT pad );
    void SetGunMoves( bool moves );
    void SetGunMoveRnd( bool moveRnd );
    void SetEndGamePadOcc( USINT pads );
    void SetGunReload( float reloadTime );
    void SetExpRad( float radius );
    void SetExpRate( float rate );
    void SetFrat( bool frat );
    void SetNumBomb( USINT num );
    void SetBombMxSpd( float spd );
    void SetBombAcc( float acc );
    void SetBombRad( float rad );
    void SetBombReloadTime( float t );
	void ClearLevel();

    bool LoadLevel( string LevString );
    void SaveLevel( string LevString );
   //void EJRTestSaveLevel(string filename);
   //void EJRTestLoadLevel(string filename);

	void AddPoint(Point p);
	void AddPad(Point p);
	void MakePadPtsFromTerrainPts();

    void Clone( Level* srcLvl );
    Level* GetPtr( );
};

#endif // _LEVEL_H
