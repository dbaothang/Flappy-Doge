#include "pipe.h"
#include "stdio.h"

vector<position> posPipe;
bool pos_Pipe[6];

bool pipe :: pipeDown = true;
bool pipe :: pipeUp = true;

bool pipe::init()
{
    posPipe.clear();

    for (int i = 0; i < TOTAL_PIPE; i++)
    {
        position temp;
        temp.getPos(SCREEN_WIDTH + i * PIPE_DISTANCE + 350, (rand() % (randMax - randMin + 1)) + randMin);
        posPipe.push_back(temp);
    }
    if (isNULL())
    {
        if (Load( "image/pipe.png", 1 ))
        {
            return true;
        }
    }
    return false;
}

void pipe::Free()
{
    free();
}

void pipe::render()
{
    for (int i = 0; i < TOTAL_PIPE; i++)
    {
        if (posPipe[i].x <= SCREEN_WIDTH && posPipe[i].x > -getWidth())

        {
            Render(posPipe[i].x, posPipe[i].y);
        }

        Render(posPipe[i].x, posPipe[i].y + getHeight() + PIPE_SPACE, 180);
    }
}

bool pipe::checkDown(position a, bool b)
{
    if(a.y>=-323 && a.y <=-212 && pipeDown && !b )
    {
        return true;
    }
    if(a.y>=-323 && a.y <=-211 && !pipeDown && b)
    {
        return false;
    }
}

bool pipe :: checkUp (position a, bool b)
{
    if(a.y>=-209 && a.y <=-97 && pipeUp && !b)
    {
        return true;
    }
    if(a.y>=-210 && a.y <= -97 && !pipeUp && b)
    {
        return false;
    }
}

void pipe::update(bool isHard)
{
    if (!die)
    {
        for (int i = 0; i < TOTAL_PIPE; i++)
        {
            if (posPipe[i].x <= - getWidth())
            {
                posPipe[i].y = (rand() % (randMax - randMin + 1)) + randMin;
                posPipe[i].x = posPipe[(i + TOTAL_PIPE - 1) % TOTAL_PIPE].x + PIPE_DISTANCE ;
            }
            else
            {
                posPipe[i].x -= 3;

                if (isHard)
                {
                    if(posPipe[i].y>=-323 && posPipe[i].y<=-211)
                    {
                        if( checkDown(posPipe[i],pos_Pipe[i]))
                        {
                            posPipe[i].y++;
                            if(posPipe[i].y==-211)
                            {
                                pos_Pipe[i]=true;
                                pipeDown=false;
                            }
                        }

                        if(!checkDown(posPipe[i],pos_Pipe[i]))
                        {
                            posPipe[i].y--;
                            if(posPipe[i].y==-323)
                            {
                                pipeDown=true;
                                pos_Pipe[i]=false;
                            }
                        }

                    }
                    else
                    {
                        if(checkUp(posPipe[i], pos_Pipe[i]))
                        {
                            posPipe[i].y--;
                            if(posPipe[i].y==-210)
                            {
                                pos_Pipe[i]=true;
                                pipeUp=false;
                            }
                        }

                        if(!checkUp(posPipe[i], pos_Pipe[i]))
                        {
                            posPipe[i].y++;
                            if(posPipe[i].y==-97)
                            {
                                pos_Pipe[i]=false;
                                pipeUp=true;
                            }
                        }
                    }
                }
            }
        }
    }
}
