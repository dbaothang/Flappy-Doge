#include <iostream>
#include "laser.h"

using namespace std;

position posLaser;

bool laserOn = false;

bool laser :: init ()
{
    posLaser.getPos(0,SCREEN_WIDTH-80);

    if (isNULL())
    {
        if ( Load("enemy/laser.png",1) )
        {
            return true;
        }
    }
    return false;
}

void laser :: Free ()
{
    free();
}

void laser :: render ()
{
    if((score%5==2) || laserOn)
    {
        laserOn = true;
        Render(posLaser.x, posLaser.y);
    }
    if(score%5==4)
    {
        laserOn=false;
    }
}


void laser :: reset()
{
    laserOn = false;
}
