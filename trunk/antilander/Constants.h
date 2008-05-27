// constants.h

#ifndef _CONSTANTS_H
#define _CONSTANTS_H

#include "SDL.h"
#include <cmath>
using namespace std;

// math
const float kPi = acos( -1.0F );

// GameWorld
const unsigned long kGameStep = 10; // kGameStep is in milliseconds

// window
// EJR this makes a const char array of char's the correct size - and than we can use it as a const char * in GameLoop
const char kWinTitle[] = "Anti-Lander";
const int kWinWidth = 640;
const int kWinHeight = 480;
const int kBackColorR = 0;
const int kBackColorG = 0;
const int kBackColorB = 0;
const int kBackColorT = 255;
const int kForeColorR = 255;
const int kForeColorG = 255;
const int kForeColorB = 255;
const int kForeColorT = 255;
const int kSplashFadeRate = 100;

// terrain
const int kDefaultNumLPad = 8;
const int kDefaultNumTPt = kDefaultNumLPad * 2;
const int kPadWidth = 30;
const int kWallHeight = 300;
const int kFloorHeight = 20;
const int kInitialTPts = 100; // Initial size of vector
const int kInitialPPts = 100; // Initial size of vector

const int kTerrainLineR = kForeColorR;
const int kTerrainLineG = kForeColorG;
const int kTerrainLineB = kForeColorB;
const int kTerrainLineT = kForeColorT;
const int kTerrainFillR = kBackColorR;
const int kTerrainFillG = kBackColorG;
const int kTerrainFillB = kBackColorB;
const int kTerrainFillT = kBackColorT;

// gunship
const int kStartAmmo = 1000;
const float kBaseGunSpeed = 0.0F;
const float kGunshipStartX = (float)(kWinWidth) / 2.0F;
const float kGunshipStartY = (float)(kWinHeight - kFloorHeight);
const float kReloadTime = 0.5F;
const unsigned short kDefaultGunStartPad = 0;
const int kGunshipLineR = kForeColorR;
const int kGunshipLineG = kForeColorG;
const int kGunshipLineB = kForeColorB;
const int kGunshipLineT = kForeColorT;
enum GunshipStatusType { ready = 1,
                         reloading };

// missile
const float kMissileStartSpeed = 100.0F;
const float kMissileAcceleration = 10.0F;
enum MissileStatusType { flight = 1,
                         boom,
                         gone };
// bomb
const float kGravity = 9.8F;
const float kBombRadius = 5.0F;
const float kBombStartSpeed = 100.0F;
const float kBombAcceleration = 10.0F;
enum BombStatusType { knBombFlying = 1,
                         knBombBoom,
                         knBombGone };
const int kWarheadColorR = 255;
const int kWarheadColorG = 0;
const int kWarheadColorB = 0;
const int kWarheadColorT = 255;
const int kMissileColorR = 255;
const int kMissileColorG = 255;
const int kMissileColorB = 255;
const int kMissileColorT = 255;
const int kFinColorR = 0;
const int kFinColorG = 255;
const int kFinColorB = 0;
const int kFinColorT = 255;

// landers
const float kLanderStartY = -14.0F;
const float kBaseDescendRate = 30.0F;
const int kBaseLanderSpeed = 0;
enum LanderStatusType { descending = 1,
                        dead,
                        landed,
                        exploding };
const int kLanderLineR = kForeColorR;
const int kLanderLineG = kForeColorG;
const int kLanderLineB = kForeColorB;
const int kLanderLineT = kForeColorT;
const int kLanderFillR = kBackColorR;
const int kLanderFillG = kBackColorG;
const int kLanderFillB = kBackColorB;
const int kLanderFillT = kBackColorT;

// Explosion
// SDL_Color has 4 Uint8 values - last is unused 
const SDL_Color kExplosionInnerColorDefault = {0xF0,0x80,0x10,0xFF};
const SDL_Color kExplosionOuterColorDefault = {0xFF,0xFF,0x00,0xFF};
const float kExplosionMaxRadiusDefault = 50.0F; // was 50
const float kExplosionSecondRadiusDefault = 4.0F;
const float kExplosionExpandRateDefault = 35.0F; // Pixel radius per second
const float kExplosionStartRadiusDefault= 0.0F;
enum ExplosionStatusType { knExplosionOccuring = 1,
                           knExplosionDone };
enum GameStatusType { knPlayMode = 1,
					  knEditMode };
#endif // _CONSTANTS_H

// comment
// Eric comment