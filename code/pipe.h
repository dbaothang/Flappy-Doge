#pragma once

#include "lib.h"
#include <iostream>
#include <vector>

using namespace std;

extern vector<position> posPipe;
extern bool pos_Pipe[6];

class pipe:LTexture
{
private:

    const int randMin = -373 + 60;
    const int randMax = SCREEN_HEIGHT - LAND_HEIGHT - PIPE_SPACE - 373 - 60;
    static bool pipeUp;
    static bool pipeDown;

public:
    bool init();

    void Free();

    void render();

    bool checkDown (position a, bool b);

    bool checkUp (position a, bool b);

    void update(bool isHard);

    int width() {return getWidth();}

    int height() {return getHeight();}

};
