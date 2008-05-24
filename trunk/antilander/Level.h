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
    unsigned short mLndrDescRate;
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
	

public:

    Level( );
    ~Level( );

    unsigned short GetNumLndrLvl( );
    unsigned short GetNumLndrScr( );
    bool GetLndrPersist( );
    unsigned short GetLndrDescRate( );
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

    void SetNumLndrLvl( unsigned short landers );
    void SetNumLndrScr( unsigned short landers );
    void SetLndrPersist( bool persist );
    void SetLndrDescRate( unsigned short rate );
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

    void LoadLevel( );
    void SaveLevel( );

	void AddPoint(Point p);
};

#endif // _LEVEL_H
