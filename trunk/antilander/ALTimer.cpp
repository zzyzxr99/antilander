#include "ALTimer.h"

ALTimer::ALTimer()
{
	mTick= 0;
}

ALTimer::~ALTimer()
{
	// Default de-constructor
}

void ALTimer::Mark()
{
	mTick= timeGetTime();
}

unsigned long ALTimer::ElapsedMS()
{
    return timeGetTime() - mTick;
}

unsigned long ALTimer::CurrentTimeMS()
{
	return timeGetTime();
}

bool ALTimer::CheckElapsedMS(unsigned long ms)
{
	unsigned long passed;
	passed= timeGetTime() - mTick;
	return (passed >= ms);
}

unsigned long ALTimer::TimerMinMS()
{
	MMRESULT mr;
	TIMECAPS tc;
	mr= timeGetDevCaps(&tc,sizeof(tc));
	return tc.wPeriodMin;
}
