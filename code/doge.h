#pragma once

#include "lib.h"
#include "pipe.h"

using namespace std;

class doge:LTexture
{
public:
    bool init(bool isDark, bool isHard);

    void render();

    void Free();

    void resetTime()
    {
        time = 0;
    }

    void fall();

    void update( int pipeWidth, int pipeHeight,bool isHard);
private:
    int angle, time, x0;
    int ahead = 0;
    string saved_path = "";
    position posDoge;
};
