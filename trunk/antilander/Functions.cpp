// Functions.cpp

#include "Functions.h"
#include <cmath>
using namespace std;

int Round( float number )
{
    if ( number < 0.0F )
    {
        number -= 0.5F;
        return (int)(number);
    }
    else
    if ( number > 0.0F )
    {
        number += 0.5F;
        return (int)(number);
    }
    else
    {
        return 0;
    }
}

int Round( double number )
{
    if (number < 0.0)
    {
        number -= 0.5;
        return (int)(number);
    }
    else if (number > 0.0)
    {
        number += 0.5;
        return (int)(number);
    }
    else
    {
        return 0;
    }
}