#pragma once

#include "lib.h"
#include <iostream>

using namespace std;

extern position posLaser;
extern bool laserOn;

class laser : LTexture
{

    public:

    bool init ();

    void Free();

    void render();

    void reset();

    int width() {return getWidth();}

    int height() {return getHeight();}

};
