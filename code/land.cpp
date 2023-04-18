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
//    if (isNULL())
//    {
//        if ( Load( "land.png", 1 ) )
//        {
//            return true;
//        }
//        else
//        {
//            return false;
//        }
//    }
//    return false;
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
    }
    else if (posLand.x > -SCREEN_WIDTH && posLand.x <= 0)
    {
        Render(posLand.x, posLand.y);
        Render(posLand.x + SCREEN_WIDTH, posLand.y);
    }
    else
    {
        posLand.getPos(0, SCREEN_HEIGHT - LAND_HEIGHT);
        Render(posLand.x, posLand.y);
    }
}

void land::update()
{
    posLand.x -= 3;
}
