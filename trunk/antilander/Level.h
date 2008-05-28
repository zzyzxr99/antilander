// Level.h
#ifndef _LEVEL_H
#define _LEVEL_H
#include "Structs.h"
#include <vector>

using namespace std;

class Level
{
private:

    unsigned short mNumLndrLvl;
    unsigned short mNumLndrScr;
    bool mLndrPersist;
    float mLndrDescRate;
    unsigned short mNumPad;
    vector<Point> mPadPt;
    unsigned short mNumTerPt;
    vector<Point> mTerPt;
    unsigned short mNumMissile;
    float mMissileSpd;
    unsigned short mGunStartPad;
    bool mGunMoves;
    bool mGunMoveRnd;
    unsigned short mEndGamePadOcc;
    float mGunReload;
    float mExpRad;
    float mExpRate;
    bool mFrat;
    unsigned short mNumBomb;
    float mBombMxSpd;
    float mBombAcc;
    float mBombRad;
	

public:

    Level( );
    ~Level( );

    unsigned short GetNumLndrLvl( );
    unsigned short GetNumLndrScr( );
    bool GetLndrPersist( );
    float GetLndrDescRate( );
    unsigned short GetNumPad( );
    vector<Point>* GetPadpt( );				//need this too
    unsigned short GetNumTerPt( );
    vector<Point>* GetTerPt( );				//need this
    unsigned short GetNumMissile( );
    float GetMissileSpd( );
    unsigned short GetGunStartPad( );
    bool GetGunMoves( );
    bool GetGunMoveRnd( );
    unsigned short GetEndGamePadOcc( );
    float GetGunReload( );
    float GetExpRad( );
    float GetExplRate( );
    bool GetFrat( );
    unsigned short GetNumBomb( );
    float GetBombMxSpd( );
    float GetBombAcc( );
    float GetBombRad( );

    void SetNumLndrLvl( unsigned short landers );
    void SetNumLndrScr( unsigned short landers );
    void SetLndrPersist( bool persist );
    void SetLndrDescRate( float rate );
    void SetNumPad( unsigned short pads );
    void SetNumTerPt( unsigned short points );
    void SetNumMissile( unsigned short missiles );
    void SetMissileSpd( float speed );
    void SetGunStartPad( unsigned short pad );
    void SetGunMoves( bool moves );
    void SetGunMoveRnd( bool moveRnd );
    void SetEndGamePadOcc( unsigned short pads );
    void SetGunReload( float reloadTime );
    void SetExpRad( float radius );
    void SetExpRate( float rate );
    void SetFrat( bool frat );
    void SetNumBomb( unsigned short num );
    void SetBombMxSpd( float spd );
    void SetBombAcc( float acc );
    void SetBombRad( float rad );

    void LoadLevel( );
    void SaveLevel( );
    void EJRTestSaveLevel(string filename);
    void EJRTestLoadLevel(string filename);

	void AddPoint(Point p);
};

#endif // _LEVEL_H
