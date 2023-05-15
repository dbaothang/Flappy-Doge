#include "land.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>

#include "land.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>

bool land::init()
{
    posLand.getPos(0, SCREEN_HEIGHT - LAND_HEIGHT);


    string land_path = "image/land.png";

    if(isNULL())
    {
        if(Load(land_path.c_str(),1))
        {
            return true;
        }
    }
    return false;
}

void land::Free()
{
    free();
}

void land::render()
{
    if (posLand.x > 0)
    {
        Render(posLand.x, posLand.y);
        // vẽ mặt đất
    }
    else if (posLand.x > -SCREEN_WIDTH && posLand.x <= 0)
    {
        Render(posLand.x, posLand.y);
        // vẽ mặt đất
        Render(posLand.x + SCREEN_WIDTH, posLand.y);
        // vẽ mặt đất cách 1 khoảng bằng độ rộng của màn hình
    }
    else
    {
        posLand.getPos(0, SCREEN_HEIGHT - LAND_HEIGHT);
        // reset lại mặt đất trước
        Render(posLand.x, posLand.y);
    }
}

void land::update()
{
    posLand.x -= 3;
}
