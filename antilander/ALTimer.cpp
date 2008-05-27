#include "ALTimer.h"
#include "Constants.h"

ALTimer::ALTimer()
{
	mLastTick= timeGetTime();
}

ALTimer::~ALTimer()
{
	// Default de-constructor
}

unsigned long ALTimer::LastStamp()
{
    return mLastTick;
}

float ALTimer::LastInterval()
{
    return mLastInterval;
}

unsigned long ALTimer::LastDiff()
{
    return mLastDiff;
}

void ALTimer::Mark()
{
	mLastTick= timeGetTime();
}

unsigned long ALTimer::ElapsedMS()
{
    return timeGetTime() - mLastTick;
}

unsigned long ALTimer::CurrentTimeMS()
{
	return timeGetTime();
}

bool ALTimer::CheckElapsedMS(unsigned long ms)
{
    unsigned long curTime= timeGetTime();
	mLastDiff= curTime - mLastTick;
    if (mLastDiff >= ms)
    {
        mLastTick= curTime;
        mLastInterval= (float)(mLastDiff)/kGameDivisor;
        return true;
    }
    return false;
}

unsigned long ALTimer::TimerMinMS()
{
	MMRESULT mr;
	TIMECAPS tc;
	mr= timeGetDevCaps(&tc,sizeof(tc));
	return tc.wPeriodMin;
}
