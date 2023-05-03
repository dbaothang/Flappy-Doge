
#include "doge.h"
#include <stdio.h>
#include <iostream>

bool doge::init(bool isDark, bool isHard)
{

    string shiba_path = "image/shiba.png";
    if (isDark) shiba_path = "image/shiba-dark.png";

    if (saved_path == shiba_path)
    {
        posDoge.getPos(60, SCREEN_HEIGHT / 2 -20);
        ahead = 0;
        angle = 0;
    }
    if (isNULL() || saved_path != shiba_path)
    {
        saved_path = shiba_path;

        if ( Load(shiba_path.c_str() , 1) )
        {
            return true;
        }
        else
        {
            return false;
        }

    }
    return false;
}


void doge::Free()
{
    free();
}

void doge::render()
{
    Render(posDoge.x, posDoge.y, angle);
}

void doge::fall(bool isHard)
{
    if (!isHard) // xử lí shiba rơi với trường hợp level normal
    {
        if (die && posDoge.y < SCREEN_HEIGHT - LAND_HEIGHT - SHIBA_HEIGHT - 5) // khi shiba chết và chưa chạm đất
        {
            if (time == 0)
            {
                y0 = posDoge.y; // lấy vị trí hiện tại của shiba theo chiều dọc
                angle = -25;    // shiba sẽ chếch lên cho hợp logic
            }
            else if (angle < 70 && time > 30) // xử lí góc khi shiba đang rơi (rơi xuống dưới)
            {
                angle += 3;
            }

            if (time >= 0)
            {
                posDoge.y = y0 + time * time * 0.18 - 7.3 * time;
                // logic vị trí của y (khi chơi thì shiba bay lên phía trên và rơi xuống phía dưới
                time++;
                if(posDoge.y>SCREEN_HEIGHT - LAND_HEIGHT - SHIBA_HEIGHT - 5)
                {
                    posDoge.y=SCREEN_HEIGHT - LAND_HEIGHT - SHIBA_HEIGHT - 5;
                }
            }
        }
    }
    else // đây là level hard
    {
        if (die && posDoge.y > 0) // khi shiba chết và chưa chạm trời
        {
            if (time == 0)
            {
                y0 = posDoge.y; // lấy vị trí hiện tại của shiba theo chiều dọc
                angle = +25; // shiba sẽ chếch xuống cho hợp logic
            }
            else if (angle > -70 && time > 30) // xử lí góc khi shiba đang rơi (rơi lên trên)
            {
                angle -= 3;
            }

            if (time >= 0)
            {
                posDoge.y = y0 - time * time * 0.18 + 7.3 * time;
                // logic vị trí của y (khi chơi thì shiba bay xuống dưới và rơi xuống phía trên
                time++;
                if(posDoge.y<0)
                {
                    posDoge.y=0;
                }
            }

        }

    }

}

void doge::update_pipe( int pipeWidth, int pipeHeight,bool isHard)
{
    if (!die)
    {
        if(!isHard) // xử lí với level normal (những phần giống ở fall thì sẽ không nhắc lại nữa
        {
            if (time == 0)
            {
                y0 = posDoge.y;
                angle = -25;
            }

            else if (angle < 70 && time > 30)
            {
                angle += 3;
            }

            if (time >= 0)
            {
                posDoge.y = y0 + time * time * 0.18 - 7.3 * time;
                time++;
            }

            if ( (posDoge.x + getWidth()> posPipe[ahead].x  ) && (posDoge.x +5 < posPipe[ahead].x + pipeWidth) &&
             (posDoge.y + 5 < posPipe[ahead].y + pipeHeight || posDoge.y  + getHeight() +5 > posPipe[ahead].y + pipeHeight + PIPE_SPACE ) )
            // đây là xử lí va chạm của shiba và cột
            {
                die = true;

            }

            else if (posDoge.x > posPipe[ahead].x + pipeWidth ) // khi vượt qua cột thì sẽ cộng điểm
            {
                ahead = ( ahead + 1 ) % TOTAL_PIPE; // chuyển sang pipe tiếp theo bằng cách thay đổi ahead
                score++;
            }

            if (posDoge.y > SCREEN_HEIGHT - LAND_HEIGHT -  SHIBA_HEIGHT - 5)
            // xử lí khi shiba chạm đất
            {
                die = true;
//                posDoge.y=SCREEN_HEIGHT - LAND_HEIGHT -  SHIBA_HEIGHT - 5;
            }

            if(posDoge.y < 5)
            // xử lí khi shiba chạm trời
            {
                die=true;
//                posDoge.y=0;
            }

        }
        else // xử lí với level hard
        {
            if (time == 0)
            {
                y0 = posDoge.y;
                angle = +25;
            }
            else if (angle > -70 && time > 30)
            {
                angle -= 3;
            }

            if (time >= 0)
            {
                posDoge.y = y0 - time * time * 0.18 + 7.3 * time;
                time++;
            }

            if ( (posDoge.x + getWidth()> posPipe[ahead].x  ) && (posDoge.x +5 < posPipe[ahead].x + pipeWidth) &&
             (posDoge.y + 5 < posPipe[ahead].y + pipeHeight || posDoge.y  + getHeight() +5 > posPipe[ahead].y + pipeHeight + PIPE_SPACE ) )
            // xử lí va chạm của shiba và cột
            {
                die = true;

            }
            else if (posDoge.x > posPipe[ahead].x + pipeWidth ) // khi vượt qua cột thì sẽ cộng điểm
            {
                ahead = ( ahead + 1 ) % TOTAL_PIPE; // chuyển sang pipe tiếp theo bằng cách thay đổi ahead
                score++;
            }

            if (posDoge.y > SCREEN_HEIGHT - LAND_HEIGHT -  SHIBA_HEIGHT - 5)
            // xử lí khi shiba chạm đất
            {
                die = true;

//                posDoge.y=SCREEN_HEIGHT - LAND_HEIGHT -  SHIBA_HEIGHT - 5;
            }
            if(posDoge.y < 5)
            // xử lí khi shiba chạm trời
            {
                die = true;

//                posDoge.y=0;
            }

        }

    }
}

void doge :: update_threat(int enemyWidth, int enemyHeight, int rocketWidth, int rocketHeight, int explodeWidth, int explodeHeight)
{
    if( (posDoge.x + getWidth() > posEnemy[ahead2].x) && (posDoge.x < posEnemy[ahead2].x+enemyWidth) &&
       ( (posDoge.y < posEnemy[ahead2].y+enemyHeight) ||
        ((posEnemy[ahead2].y+enemyHeight>posDoge.y + getHeight()) && (posDoge.y + getHeight()> posEnemy[ahead2].y) )))
    // xử lí va chạm của shiba với dơi
       {
           die = true;
       }
    else {ahead2=(2+ahead2)%TOTAL_ENEMY;} // chuyển sang con dơi tiếp theo

     if( (posDoge.x + getWidth() > posRocket.x) && (posDoge.x < posRocket.x+rocketWidth) &&
       ( (posDoge.y < posRocket.y+rocketHeight) || ((posRocket.y+rocketHeight>posDoge.y + getHeight())&&(posDoge.y + getHeight() > posRocket.y ))  ) )
       // xư lí va chạm của shiba với rocket
       {
           die = true;
       }

    if( boom && (posDoge.x + getWidth() > posExplode.x && posDoge.x < posExplode.x+explodeWidth) &&
       ( posDoge.y < posExplode.y + explodeHeight || (  (posExplode.y+explodeHeight>posDoge.y + getHeight())&&(posDoge.y + getHeight() > posExplode.y ) ) ) )
       // xử lí va chạm của shiba với vụ nổ
       {
           die = true;
       }

    if (posDoge.y+getHeight() > 440 && laserOn ) // xử lí va chạm của shiba và laser
    {
        die = true;
    }

}

void doge :: reset()
{
    ahead = 0;
    ahead2 = 0;
}
