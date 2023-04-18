
#include "rocket.h"
#include "stdio.h"

#include<iostream>

using namespace std;

bool rocket :: init ()
{

    posRocket.getPos(posEnemy[ahead].x-10, posEnemy[ahead].y);

    if(isNULL())
    {
        if(Load("enemy/rocket.png",1))
        {
            return true;
        }
    }
    return false;
}

void rocket :: Free()
{
    free();
}

void rocket :: render()
{
        if(posRocket.x <= SCREEN_WIDTH && posRocket.x > 0 )
        {
            Render (posRocket.x, posRocket.y);
        }
}

void rocket :: update ()
{
    if(!die)
    {
        if (posRocket.x <= 0)
        {
            if (posEnemy[ahead].x > 100)
            {
                posRocket.x = posEnemy[ahead].x-5;
                posRocket.y = posEnemy[ahead].y;
            }
            else
            {
                ahead = (ahead+2)%TOTAL_ENEMY;
            }
            posRocket.x = posEnemy[ahead].x-10;
            posRocket.y =  posEnemy[ahead].y;
        }
        else
        {
            posRocket.x-=5;
        }
    }
}
