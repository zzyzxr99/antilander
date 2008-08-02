// constants.h

#ifndef _CONSTANTS_H
#define _CONSTANTS_H

#include "SDL.h"
#include "SDL_Mixer.h"
#include <cmath>
using namespace std;

//TYPEDEF
typedef unsigned short USINT;

// math
const float kPi = acos( -1.0F );
const float kSlopeRunTolerance = 0.00001F; // Slope tolerance for vertical lines - nearly zero run
// GameWorld
const unsigned long kGameStep = 10; // kGameStep is in milliseconds
const float kGameDivisor = 1000.0F;
const USINT kDefaultLandersPerLevel = 10;
const USINT kDefaultLandersPerScreen = 1;

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
const int kSplashFadeRate = 150;

//Menu

const int kMenuWidth= 80;
const int kMenuHeight= 100;
const unsigned char kMenuRvalue= 255;
const unsigned char kMenuGvalue= 255;
const unsigned char kMenuBvalue= 255;
const unsigned char kMenuAvalue= 255;

const int kMenuDrawX=(kWinWidth/2)-(kMenuWidth/2);
const int kMenuDrawY= 60;

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
const int kStartAmmo = 300;
const int kDefaultStartBomb = 100;
const float kBaseGunSpeed = 0.0F;
const float kGunshipStartX = (float)(kWinWidth) / 2.0F;
const float kGunshipStartY = (float)(kWinHeight - kFloorHeight);
const float kReloadTime = 0.5F;
const float kBombReloadTime = 3.0F;
const USINT kDefaultGunStartPad = 0;
const int kGunshipLineR = kForeColorR;
const int kGunshipLineG = kForeColorG;
const int kGunshipLineB = kForeColorB;
const int kGunshipLineT = kForeColorT;
enum GunshipStatusType { ready = 1,
                         reloading = 2 };

// missile
const float kMissileStartSpeed = 100.0F;
const float kMissileAcceleration = 10.0F;
enum MissileStatusType { knMissileFlying = 1,
                         knMissileExplode,
                         knMissileDead };
// bomb
const float kGravity = 9.8F;
const float kBombRadius = 5.0F;
const float kBombMaxSpeed = 100.0F;
enum BombStatusType { knBombFlying = 1,
                         knBombExplode,
                         knBombDead };
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
const USINT kLanderPadGoal = 3;
enum LanderStatusType { knLanderDescending = 1,
                        knLanderDead,
                        knLanderLanded,
                        knLanderExplode };
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
					  knEditMode,
					  knMenuMode,
					  knIntroMode,
					  knLevTransMode,
					  knEndMode };
enum EditStatusType { knBuildMode = 1,
                      knMoveMode };

// Render
enum FadeType { knFadeIn = 1,
                knFadeOut,
                knFadeDone };

//SCORE
const int knMKill = 50;
const int knBKill = 75;
const int knFKill = 100;

//SOUND EFFECTS

const int kFrequency = 44100;
const Uint16 kFormat = MIX_DEFAULT_FORMAT;
const int kListenChannels = 2;
const int kChunkSize = 2096;
const int kDefaultVolume = MIX_MAX_VOLUME/4;
const int kPriorityVolume = MIX_MAX_VOLUME/2;
const int kMAXChannels = 256;
const int kReservedChannels = 4; // number of channels for loops reserved not used for effects

enum SoundEffectType { knSEMissileLaunch = 0,
					   knSEMissileExplosion,
					   knSEBombLaunch,
					   knSEBombExplosion,
					   knSELanderSpawn,
					   knSELanderExplosion,
					   knSELanderLanded,
					   knSEMenuClick,
					   knSEIntroSound,
					   knSEGameOver,
					   knSELevelClear,
					   knSLMenu,
					   knSLPlay,
					   knLastEffect
					 };

enum LoopChannels    { knMenuChannel = 0,
					   knPlayChannel
					 };

#endif // _CONSTANTS_H