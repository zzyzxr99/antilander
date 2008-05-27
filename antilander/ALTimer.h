#ifndef _ALTIMER_H
#define _ALTIMER_H

// Class prototypes
class ALTimer;

#include "Windows.h"
#include "Mmsystem.h"
#include <ctime>

// Timer class to count of game step and for special attacks/delays
class ALTimer
{

private:
	unsigned long mLastTick;
    unsigned long mLastDiff;
    float mLastInterval;

public:
	ALTimer();
	~ALTimer();
	unsigned long ElapsedMS(void);
	void Mark(void);
	unsigned long CurrentTimeMS();
	bool CheckElapsedMS(unsigned long ms);
	unsigned long TimerMinMS();
    unsigned long LastStamp();
    unsigned long LastDiff();
    float LastInterval();
};

#endif /*_ALTIMER_H*/