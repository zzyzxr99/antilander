// Level.cpp
#include "Constants.h"
#include "Structs.h"
#include "Level.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
using namespace std;

//static variables

Level::Level( )
{
    mNumLndrLvl     = kDefaultLandersPerLevel;
    mNumLndrScr     = kDefaultLandersPerScreen;
    mLndrPersist    = false;
    mLndrDescRate   = kBaseDescendRate;
    mNumMissile     = kStartAmmo;
    mMissileSpd     = kMissileStartSpeed;
    mGunMoves       = false;
    mGunMoveRnd     = false;
    mEndGamePadOcc  = kLanderPadGoal;
    mGunReload      = kReloadTime;
    mExpRad         = kExplosionMaxRadiusDefault;
    mExpRate        = kExplosionExpandRateDefault;
    mFrat           = false;
    mNumBomb        = kDefaultStartBomb;
    mBombMxSpd      = kBombMaxSpeed;
    mBombAcc        = kGravity;
    mBombRad        = kBombRadius;
    mBombReloadTime = kBombReloadTime;
    Point pt;
    pt.x = 10.0F;
    pt.y = 90.0F;
    mPadPt.push_back(pt);
    pt.x = 100.0F;
    pt.y = 180.0F;
    mPadPt.push_back(pt);
    pt.x = 200.0F;
    pt.y = 270.0F;
    mPadPt.push_back(pt);
    pt.x = 320.0F;
    pt.y = 360.0F;
    mPadPt.push_back(pt);
    pt.x = 440.0F;
    pt.y = 270.0F;
    mPadPt.push_back(pt);
    pt.x = 540.0F;
    pt.y = 180.0F;
    mPadPt.push_back(pt);
    pt.x = 629.0F;
    pt.y = 90.0F;
    mPadPt.push_back(pt);
    mNumPad = mPadPt.size( );
    vector<Point>::iterator Iter;
    for ( Iter = mPadPt.begin( ); Iter != mPadPt.end( ); Iter++)
    {
        pt.x = Iter->x-10;
        pt.y = Iter->y;
        mTerPt.push_back(pt);
        pt.x += 20;
        mTerPt.push_back(pt);
    }
    mNumTerPt = mTerPt.size( );
    mGunStartPad = mNumPad/2;
}

Level::~Level( )
{ }

USINT Level::GetNumLndrLvl( )
{
    return mNumLndrLvl;
}

USINT Level::GetNumLndrScr( )
{
    return mNumLndrScr;
}

bool Level::GetLndrPersist( )
{
    return mLndrPersist;
}

float Level::GetLndrDescRate( )
{
    return mLndrDescRate;
}

USINT Level::GetNumPad( )
{
    return mNumPad;
}

vector<Point>* Level::GetPadpt( )
{
    return &mPadPt;
}

USINT Level::GetNumTerPt( )
{
    return mNumTerPt;
}

vector<Point>* Level::GetTerPt()
{
    return &mTerPt;
}

USINT Level::GetNumMissile( )
{
    return mNumMissile;
}

float Level::GetMissileSpd( )
{
    return mMissileSpd;
}

USINT Level::GetGunStartPad( )
{
    return mGunStartPad;
}

bool Level::GetGunMoves( )
{
    return mGunMoves;
}

bool Level::GetGunMoveRnd( )
{
    return mGunMoveRnd;
}

USINT Level::GetEndGamePadOcc( )
{
    return mEndGamePadOcc;
}

float Level::GetGunReload( )
{
    return mGunReload;
}

float Level::GetExpRad( )
{
    return mExpRad;
}

float Level::GetExplRate( )
{
    return mExpRate;
}

bool Level::GetFrat( )
{
    return mFrat;
}

USINT Level::GetNumBomb( )
{
    return mNumBomb;
}

float Level::GetBombMxSpd( )
{
    return mBombMxSpd;
}

float Level::GetBombAcc( )
{
    return mBombAcc;
}

float Level::GetBombRad( )
{
    return mBombRad;
}

float Level::GetBombReloadTime( )
{
    return mBombReloadTime;
}

void Level::SetNumLndrLvl( USINT landers )
{
    mNumLndrLvl = landers;
}
void Level::SetNumLndrScr( USINT landers )
{
    mNumLndrScr = landers;
}

void Level::SetLndrPersist( bool persist )
{
    mLndrPersist = persist;
}

void Level::SetLndrDescRate( float rate )
{
    mLndrDescRate = rate;
}

void Level::SetNumPad( USINT pads )
{
    mNumPad = pads;
}

void Level::SetNumTerPt( USINT points )
{
    mNumTerPt = points;
}

void Level::SetNumMissile( USINT missiles )
{
    mNumMissile = missiles;
}

void Level::SetMissileSpd( float speed )
{
    mMissileSpd = speed;
}

void Level::SetGunStartPad( USINT pad )
{
    mGunStartPad = pad;
}

void Level::SetGunMoves( bool moves )
{
    mGunMoves = moves;
}

void Level::SetGunMoveRnd( bool moveRnd )
{
    mGunMoveRnd = moveRnd;
}

void Level::SetEndGamePadOcc( USINT pads )
{
    mEndGamePadOcc = pads;
}

void Level::SetGunReload( float reloadTime )
{
    mGunReload = reloadTime;
}

void Level::SetExpRad( float radius )
{
    mExpRad = radius;
}

void Level::SetExpRate( float rate )
{
    mExpRate = rate;
}

void Level::SetFrat( bool frat )
{
    mFrat = frat;
}

void Level::SetNumBomb( USINT num )
{
    mNumBomb = num;
}

void Level::SetBombMxSpd( float spd )
{
    mBombMxSpd = spd;
}

void Level::SetBombAcc( float acc )
{
    mBombAcc = acc;
}

void Level::SetBombRad( float rad )
{
    mBombRad = rad;
}

void Level::SetBombReloadTime( float t )
{
    mBombReloadTime = t;
}
void Level::ClearLevel( )
{
    mNumLndrLvl    = kDefaultLandersPerLevel;
    mNumLndrScr    = kDefaultLandersPerScreen;
    mLndrPersist   = false;
    mLndrDescRate  = kBaseDescendRate;
    mNumMissile    = kStartAmmo;
    mMissileSpd    = kMissileStartSpeed;
    mGunMoves      = false;
    mGunMoveRnd    = false;
    mEndGamePadOcc = kLanderPadGoal;
    mGunReload     = kReloadTime;
    mExpRad        = kExplosionMaxRadiusDefault;
    mExpRate       = kExplosionExpandRateDefault;
    mFrat          = false;
    mNumBomb       = kDefaultStartBomb;
    mBombMxSpd     = kBombMaxSpeed;
    mBombAcc       = kGravity;
    mBombRad       = kBombRadius;
    mNumTerPt	   = 0;
	mNumPad	       = 0;
	mTerPt.clear();
	mPadPt.clear();
}
bool Level::LoadLevel( string LevString )
{
	ifstream infile(LevString.c_str());
    if ( !infile )
    {
        return false;
    }
	mTerPt.clear();
	mPadPt.clear();
	vector<Point>::iterator iterTer = mTerPt.begin();
	vector<Point>::iterator iterPad = mPadPt.begin();
	int ctr = 0;
	string str[100];		
	char *cstr, *p;
	cstr = new char [15];
	char* index[] = {"mTerPt","mPadPt","mGunStartPad","mEndGamePadOcc","mNumLndrLvl","mNumLndrScr","mNumBomb","mNumMissile","mBombMxSpd",
					 "mBombAcc","mBombRad","mLndrDescRate","mGunReload","mExpRad","mExpRate","mMissileSpd","mLndrPersist","mFrat","mGunMoves",
					 "mGunMoveRnd","mBombReloadTime","LAST"};		//index of strings to compare
	Point pt;
	while (!infile.eof())
	{
		getline(infile, str[ctr]);
		ctr++;
	}
	//ctr = amount of lines
	for (int j = 0; j < ctr; j++)
	{
		if(!str[j].compare(index[0]))			//if current line is TERRAINPTS
		{
			for (int l = j+1; str[l].compare(index[1]); l++)
			{
				strcpy(cstr, str[l].c_str());
				p = strtok(cstr,",");
				pt.x = (float)atof(p);
				p = strtok(NULL," ");
				pt.y = (float)atof(p);
				mTerPt.push_back(pt);
				cout << pt.x << " " << pt.y << endl;
			}
			mNumTerPt = mTerPt.size();
		} 
		else if(!str[j].compare(index[1]))
		{
			for (int l = j+1, k = 0; str[l].compare(index[2]); l++, k++)
			{
				strcpy (cstr, str[l].c_str());
				p = strtok(cstr,",");
				pt.x = (float)atof(p);
				p = strtok(NULL," ");
				pt.y = (float)atof(p);
				mPadPt.push_back(pt);
			}
			mNumPad = mPadPt.size();
		}		
		else if(!str[j].compare(index[2]))
		{
			SetGunStartPad((USINT)(atoi(str[j+1].c_str())));
		}
		else if(!str[j].compare(index[3]))
		{
			SetEndGamePadOcc((USINT)(atoi(str[j+1].c_str())));
		}
		else if(!str[j].compare(index[4]))
		{
			SetNumLndrLvl((USINT)(atoi(str[j+1].c_str())));
		}
		else if(!str[j].compare(index[5]))
		{
			SetNumLndrScr((USINT)(atoi(str[j+1].c_str())));
		}
		else if(!str[j].compare(index[6]))
		{
			SetNumBomb((USINT)(atoi(str[j+1].c_str())));
		}
		else if(!str[j].compare(index[7]))
		{
			SetNumMissile((USINT)(atoi(str[j+1].c_str())));
		}
		else if(!str[j].compare(index[8]))
		{
			SetBombMxSpd((float)(atof(str[j+1].c_str())));
		}
		else if(!str[j].compare(index[9]))
		{
			SetBombAcc((float)(atof(str[j+1].c_str())));
		}
		else if(!str[j].compare(index[10]))
		{
			SetBombRad((float)(atof(str[j+1].c_str())));
		}
		else if(!str[j].compare(index[11]))
		{
			SetLndrDescRate((float)(atof(str[j+1].c_str())));
		}
		else if(!str[j].compare(index[12]))
		{
			SetGunReload((float)(atof(str[j+1].c_str())));
		}
		else if(!str[j].compare(index[13]))
		{
			SetExpRad((float)(atof(str[j+1].c_str())));
		}
		else if(!str[j].compare(index[14]))
		{
			SetExpRate((float)(atof(str[j+1].c_str())));
		}
		else if(!str[j].compare(index[15]))
		{
			SetMissileSpd((float)(atof(str[j+1].c_str())));
		}
		else if(!str[j].compare(index[16]))
		{
            if ( atoi(str[j+1].c_str( )) > 0 )
            {
    			SetLndrPersist(true);
            }
            else
            {
                SetLndrPersist(false);
            }
		}
		else if(!str[j].compare(index[17]))
		{
			if (atoi(str[j+1].c_str( )) > 0 )
            {
                SetFrat(true);
            }
            else
            {
                SetFrat(false);
            }
		}
		else if(!str[j].compare(index[18]))
		{
			if ( atoi(str[j+1].c_str( )) > 0 )
            {
                SetGunMoves(true);
            }
            else
            {
                SetGunMoves(false);
            }
		}
		else if(!str[j].compare(index[19]))
		{
			if ( atoi(str[j+1].c_str( )) > 0 )
            {
                SetGunMoveRnd(true);
            }
            else
            {
                SetGunMoveRnd(false);
            }
		}
		else if(!str[j].compare(index[20]))
		{
			SetBombReloadTime((float)(atof(str[j+1].c_str())));
		}

	}
	delete [] cstr;
    infile.close( );
    return true;
}

void Level::SaveLevel( string LevString )
{
	ofstream outfile(LevString.c_str());
	outfile << "mTerPt" << endl;
	for(int i = 0; i < mNumTerPt; i++)
	{
		outfile << mTerPt[i].x << ", " << mTerPt[i].y << endl;
	}
	outfile << "mPadPt" << endl;
	for(int i = 0; i < mNumPad; i++)
	{
		outfile << mPadPt[i].x << ", " << mPadPt[i].y << endl;
	}
	outfile << "mGunStartPad" << endl;		outfile << mGunStartPad << endl;
	outfile << "mEndGamePadOcc" << endl;	outfile << mEndGamePadOcc << endl;
	outfile << "mNumLndrLvl" << endl;		outfile << mNumLndrLvl << endl;
	outfile << "mNumLndrScr" << endl;		outfile << mNumLndrScr << endl;
	outfile << "mNumBomb" << endl;			outfile << mNumBomb << endl;
	outfile << "mNumMissile" << endl;		outfile << mNumMissile << endl;	
	outfile << "mBombMxSpd" << endl;		outfile << mBombMxSpd << endl;
    outfile << "mBombAcc" << endl;			outfile << mBombAcc << endl;
    outfile << "mBombRad" << endl;			outfile << mBombRad << endl;
	outfile << "mLndrDescRate" << endl;		outfile << mLndrDescRate << endl;
	outfile << "mGunReload" << endl;		outfile << mGunReload << endl;
    outfile << "mExpRad" << endl;			outfile << mExpRad << endl;
    outfile << "mExpRate" << endl;			outfile << mExpRate << endl;
	outfile << "mMissileSpd" << endl;		outfile << mMissileSpd << endl;
	outfile << "mLndrPersist" << endl;		outfile << mLndrPersist << endl;
	outfile << "mFrat" << endl;				outfile << mFrat << endl;
	outfile << "mGunMoves" << endl;			outfile << mGunMoves << endl;
    outfile << "mGunMoveRnd" << endl;		outfile << mGunMoveRnd << endl;
	//////////////////////////////////////////////////////////////////////////////
	outfile << "mBombReloadTime" << endl;	outfile << mBombReloadTime << endl;	
	outfile << "LAST" << endl;
}

void Level::EJRTestSaveLevel(string filename)
{
    // Open output file stream to destination filename ios::out means to write
    ofstream outf(filename.c_str(),ios::out);
    
    // Write out level header
    outf << "Level 1" << endl;
    // Write out number of terrain points
    outf << mNumTerPt << endl;

    // close and save file
    outf.close();
}

void Level::EJRTestLoadLevel(string filename)
{
    // open file as input file stream, ios::in read
    ifstream inf(filename.c_str(),ios::in);
    // if ifstream is NULL will fail
    if (inf != NULL) // File exists
    {
        // read first line of ifstream inf into strLevel
        string strLevel="";
        getline(inf,strLevel);
        cout << strLevel << endl;; // output to console

        // read next line and convert it to an integer to put into terrain points
        string strNumTerrain="";
        getline(inf,strNumTerrain);
        int numterr= atoi(strNumTerrain.c_str()); // atoi is asc to integer - 

        cout << "Number of points=" << numterr <<endl; // outp to console for test
    }
    inf.close();
}

void Level::AddPoint(Point p)
{
	mTerPt.push_back (p);
	mNumTerPt= mTerPt.size();
}

void Level::AddPad(Point p)
{
	mTerPt.push_back (p);
	mNumTerPt= mTerPt.size();
}

void Level::MakePadPtsFromTerrainPts()
{
	mPadPt.clear();
	for (int n= 0; n < mNumTerPt-1; n++)
	{
		Point p1, p2, p3;
		p1 = mTerPt[n];
		p2 = mTerPt[n+1];
		if (p1.y == p2.y)
		{
			p3.x = (p1.x + p2.x)/2;
			p3.y = p1.y;
			mPadPt.push_back(p3);
		}
		
	}
	mNumPad= mPadPt.size();

}

void Level::Clone( Level* srcLvl )
{
    mNumLndrLvl     = srcLvl->GetNumLndrLvl( );
    mNumLndrScr     = srcLvl->GetNumLndrScr( );
    mLndrPersist    = srcLvl->GetLndrPersist( );
    mLndrDescRate   = srcLvl->GetLndrDescRate( );
    mNumMissile     = srcLvl->GetNumMissile( );
    mMissileSpd     = srcLvl->GetMissileSpd( );
    mGunStartPad    = srcLvl->GetGunStartPad( );
    mGunMoves       = srcLvl->GetGunMoves( );
    mGunMoveRnd     = srcLvl->GetGunMoveRnd( );
    mEndGamePadOcc  = srcLvl->GetEndGamePadOcc( );
    mGunReload      = srcLvl->GetGunReload( );
    mExpRad         = srcLvl->GetExpRad( );
    mExpRate        = srcLvl->GetExplRate( );
    mFrat           = srcLvl->GetFrat( );
    mNumBomb        = srcLvl->GetNumBomb( );
    mBombMxSpd      = srcLvl->GetBombMxSpd( );
    mBombAcc        = srcLvl->GetBombAcc( );
    mBombRad        = srcLvl->GetBombRad( );
    mBombReloadTime = srcLvl->GetBombReloadTime( );

    mPadPt.clear( );
    vector<Point>::iterator Iter;
    for ( Iter = srcLvl->GetPadpt( )->begin( );
          Iter != srcLvl->GetPadpt( )->end( ); Iter++ )
    {
        mPadPt.push_back(*Iter);
    }
    mNumPad = mPadPt.size( );

    mTerPt.clear( );
    for ( Iter = srcLvl->GetTerPt( )->begin( );
          Iter != srcLvl->GetTerPt( )->end( ); Iter++ )
    {
        mTerPt.push_back(*Iter);
    }
    mNumTerPt = mTerPt.size( );
}

Level* Level::GetPtr( )
{
    return this;
}