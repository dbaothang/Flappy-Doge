#include <stdio.h>
#include <iostream>
#include "enemy.h"

int enemy :: frame = 0;

vector<position> posEnemy;

bool enemy :: init ()
{
    posEnemy.clear();

    for (int i = 0; i < TOTAL_ENEMY; i++)
            {
                position temp;
                temp.getPos(SCREEN_WIDTH+350+110+i*(220),20);
                posEnemy.push_back(temp);
            }

            gSpriteClips[ 0 ].x =   0;
            gSpriteClips[ 0 ].y =   0;
            gSpriteClips[ 0 ].w =  43;
            gSpriteClips[ 0 ].h = 31;

            gSpriteClips[ 1 ].x =  43;
            gSpriteClips[ 1 ].y =   0;
            gSpriteClips[ 1 ].w =  43;
            gSpriteClips[ 1 ].h = 31;

            gSpriteClips[ 2 ].x = 86;
            gSpriteClips[ 2 ].y =   0;
            gSpriteClips[ 2 ].w =  43;
            gSpriteClips[ 2 ].h = 31;

            gSpriteClips[ 3 ].x = 129;
            gSpriteClips[ 3 ].y =   0;
            gSpriteClips[ 3 ].w =  43;
            gSpriteClips[ 3 ].h = 31;

            gSpriteClips[ 4 ].x = 172;
            gSpriteClips[ 4 ].y =   0;
            gSpriteClips[ 4 ].w =  43;
            gSpriteClips[ 4 ].h = 31;

	if(isNULL())
    {
        if(!Load( "enemy/enemy.png" , 1))
        {
            return false;
        }
	}

	return true;
}

void enemy :: Free ()
{
    free();
}

void enemy :: render (bool isPause)
{
    SDL_Rect* currentClip = &gSpriteClips[ frame / 5 ];
    if(!die && !isPause)
    {
        for (int i=0;i<TOTAL_ENEMY;i++)
        {
            if(i%2==0)
            {
                if (posEnemy[i].x <= SCREEN_WIDTH && posEnemy[i].x > -getWidth())

                {
                    Render(posEnemy[i].x, posEnemy[i].y,angle,currentClip);

                }
            }

        }

        frame++;
        if(frame / 5 >= enemy_animation)
        {
            frame = 0;
        }
    }
    if(die)
    {
        for (int i=0;i<TOTAL_ENEMY;i++)
        {
            if (i%2==0)
            {
                 if (posEnemy[i].x <= SCREEN_WIDTH && posEnemy[i].x > -getWidth())

                {
                    Render(posEnemy[i].x, posEnemy[i].y,angle,currentClip);

                }
            }

        }
    }
    if(!die && isPause)
    {
        for (int i=0;i<TOTAL_ENEMY;i++)
        {
            if (i%2==0)
            {
                if (posEnemy[i].x <= SCREEN_WIDTH && posEnemy[i].x > -getWidth())

                {
                    Render(posEnemy[i].x, posEnemy[i].y,angle,currentClip);

                }
            }

        }
    }
}

void enemy :: update ()
{
    if(!die)
    {
        for (int i=0;i<TOTAL_ENEMY;i++)
        {
            if(posEnemy[i].x <= -43 )
            {
                posEnemy[i].x=posEnemy[(i+TOTAL_ENEMY-1)%TOTAL_ENEMY].x+220;
                posEnemy[i].y=25;
            }
            else
            {
                posEnemy[i].x-=3;
            }
        }

    }
}
