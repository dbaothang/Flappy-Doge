#include <stdio.h>
#include "explode.h"
#include <iostream>

using namespace std;

bool boom = false;
position posExplode;

bool explode :: init ()
{
    posExplode.getPos(0,1);

    gSpriteClips[ 0 ].x =   0;
    gSpriteClips[ 0 ].y =   0;
    gSpriteClips[ 0 ].w =  96;
    gSpriteClips[ 0 ].h = 96;

    gSpriteClips[ 1 ].x =  96;
    gSpriteClips[ 1 ].y =   0;
    gSpriteClips[ 1 ].w =  96;
    gSpriteClips[ 1 ].h = 96;

    gSpriteClips[ 2 ].x = 192;
    gSpriteClips[ 2 ].y =   0;
    gSpriteClips[ 2 ].w =  96;
    gSpriteClips[ 2 ].h = 96;

    gSpriteClips[ 3 ].x = 288;
    gSpriteClips[ 3 ].y =   0;
    gSpriteClips[ 3 ].w =  96;
    gSpriteClips[ 3 ].h = 96;

    if(isNULL())
    {
        if(!Load( "enemy/explode.png" , 1))
        {
            return false;
        }
	}

	return true;
}

void explode :: Free ()
{
    free();
}
void explode :: render (bool isPause)
{
    SDL_Rect* currentClip = &gSpriteClips[ frame / 7 ];
    if(!isPause && !die)
    {
        if(posRocket.x<=-10 || boom)
        {
            boom = true;
            if (frame/7 <= explode_animation)
            {
                Render (posExplode.x,posExplode.y,angle,currentClip);
                frame++;
            }
        }
    }
    if( (isPause||die) && frame/4 <= explode_animation && boom)
    {
        Render (posExplode.x,posExplode.y,angle,currentClip);
    }
}

void explode :: update ()
{
    if(frame/7 > explode_animation)
    {
        frame = 0;
        boom = false;
    }
}

//void explode :: reset()
//{
//    if(die)
//    {
//        frame = 0;
//    }
//}

void explode::reset_boom ()
{
    boom = false;
    frame = 0;
}

