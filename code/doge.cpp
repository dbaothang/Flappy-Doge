
#include "doge.h"
#include <stdio.h>
#include <iostream>

bool doge::init(bool isDark, bool isHard)
{

    string shiba_path = "image/shiba.png";
    if (isDark) shiba_path = "image/shiba-dark.png";
    if(isHard)
    {
        string shiba_path = "image/shiba_hard.png";
        if (isDark) shiba_path = "image/ishiba-dark_hard.png";
    }
    if (saved_path == shiba_path)
    {
        posDoge.getPos(60, SCREEN_HEIGHT / 2 -20);
        ahead = 0;
        angle = 0;
    }
    if (isNULL() || saved_path != shiba_path)
    {
        saved_path = shiba_path;

        if ( Load(shiba_path.c_str() , 1) )
        {
            return true;
        }
        else
        {
            return false;
        }

    }
    return false;
}

void doge::Free()
{
    free();
}

void doge::render()
{
    Render(posDoge.x, posDoge.y, angle);
}

void doge::fall()
{
    if (die && posDoge.y < SCREEN_HEIGHT - LAND_HEIGHT - SHIBA_HEIGHT - 5)
    {
        if (time == 0)
        {
            x0 = posDoge.y;
            angle = -25;
        }
        else if (angle < 70 && time > 30)
        {
            angle += 3;
        }

        if (time >= 0)
        {
            posDoge.y = x0 + time * time * 0.18 - 7.3 * time;
            time++;
            if(posDoge.y>SCREEN_HEIGHT - LAND_HEIGHT - SHIBA_HEIGHT - 5)
            {
                posDoge.y=SCREEN_HEIGHT - LAND_HEIGHT - SHIBA_HEIGHT - 5;
            }
        }
    }
    else return;
}

void doge::update( int pipeWidth, int pipeHeight,bool isHard)
{
    if (!die)
    {
        if(!isHard)
        {
            if (time == 0)
            {
                x0 = posDoge.y;
                angle = -25;
            }
            else if (angle < 70 && time > 30)
            {
                angle += 3;
            }

            if (time >= 0)
            {
                posDoge.y = x0 + time * time * 0.18 - 7.3 * time;
                time++;
            }

            if ( (posDoge.x + getWidth()> posPipe[ahead].x  ) && (posDoge.x +5 < posPipe[ahead].x + pipeWidth) &&
             (posDoge.y + 5 < posPipe[ahead].y + pipeHeight || posDoge.y  + getHeight() +5 > posPipe[ahead].y + pipeHeight + PIPE_SPACE ) )
            {
//                die = true;
                    die = false;
            }
            else if (posDoge.x > posPipe[ahead].x + pipeWidth )
            {
                ahead = ( ahead + 1 ) % TOTAL_PIPE;
                score++;
            }

            if (posDoge.y > SCREEN_HEIGHT - LAND_HEIGHT -  SHIBA_HEIGHT - 5)
            {
              //  die = true;
              die = false;
                posDoge.y=SCREEN_HEIGHT - LAND_HEIGHT -  SHIBA_HEIGHT - 5;
            }
            if(posDoge.y < 5)
            {
               // die=true;
               die = false;
                posDoge.y=0;
            }

        }
        else
        {
            if (time == 0)
            {
                x0 = posDoge.y;
                angle = +25;
            }
            else if (angle > -70 && time > 30)
            {
                angle -= 3;
            }

            if (time >= 0)
            {
                posDoge.y = x0 - time * time * 0.18 + 7.3 * time;
                time++;
            }

            if ( (posDoge.x + getWidth()> posPipe[ahead].x  ) && (posDoge.x +5 < posPipe[ahead].x + pipeWidth) &&
             (posDoge.y + 5 < posPipe[ahead].y + pipeHeight || posDoge.y  + getHeight() +5 > posPipe[ahead].y + pipeHeight + PIPE_SPACE ) )
            {
//                die = true;
                    die = false;
            }
            else if (posDoge.x > posPipe[ahead].x + pipeWidth )
            {
                ahead = ( ahead + 1 ) % TOTAL_PIPE;
                score++;
            }

            if (posDoge.y > SCREEN_HEIGHT - LAND_HEIGHT -  SHIBA_HEIGHT - 5)
            {
//                die = true;
                 die = false;
                posDoge.y=SCREEN_HEIGHT - LAND_HEIGHT -  SHIBA_HEIGHT - 5;
            }
            if(posDoge.y < 5)
            {
//                die = true;
                die = false;
                posDoge.y=0;
            }

        }

    }
}
