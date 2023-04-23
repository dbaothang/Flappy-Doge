#pragma once

#include "laser.h"
#include "enemy.h"
#include "rocket.h"
#include "explode.h"
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

    void fall(bool isHard);

    void update_pipe( int pipeWidth, int pipeHeight,bool isHard);

    void update_threat(int enemyWidth, int enemyHeight, int rocketWith, int rocketHeight, int explodeWidth, int explodeHeight);

    void reset();

private:
    int angle, time, x0;
    int ahead = 0;
    int ahead2=0;
    string saved_path = "";
    position posDoge;
};
