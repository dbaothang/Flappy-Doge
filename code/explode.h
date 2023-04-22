#pragma once

#include "lib.h"
#include "rocket.h"
#include <iostream>

using namespace std;

extern position posExplode;
extern bool boom;

class explode : LTexture
{
    private :

    int angle = 0;
    int frame = 0;
    static const int explode_animation=4;
    SDL_Rect gSpriteClips [explode_animation];

    public :

//    static bool boom;

    bool init ();

    void render(bool isPause);

    void Free();

    void update();

//    void reset();

    void reset_boom();

    int width() {return getWidth();}

    int height() {return getHeight();}
};


