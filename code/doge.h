#pragma once

#include "laser.h"
#include "enemy.h"
#include "rocket.h"
#include "explode.h"
#include "lib.h"
#include "pipe.h"

using namespace std;

class doge: LTexture
{
public:
    bool init(bool isDark, bool isHard); // khởi tạo shiba

    void render(); // vẽ lên màn hình

    void Free(); // giải phóng

    void resetTime()
    {
        time = 0;
    }

    void fall(bool isHard); // xử lí khi shiba chết sẽ rơi xuống(level normal) và rơi lên trên (level hard)

    void update_pipe( int pipeWidth, int pipeHeight,bool isHard);
    // xử lí va chạm với cột, va chạm với trời, đất và cập nhật shiba

    void update_threat(int enemyWidth, int enemyHeight, int rocketWith, int rocketHeight, int explodeWidth, int explodeHeight);
    // xử lí va chạm với các kẻ thù khác

    void reset(); // reset lại các biến ahead, ahead2

private:
    int angle, time, y0;
    // angle là góc của chú chó shiba, time là để tính toán khoảng cách shiba bay lên và rơi xuống, y0 vị trí theo chiều dọc hiện tại của shiba
    int ahead = 0; // xét các vị trí pipe[ahead] để xử lí va chạm
    int ahead2=0;  // xét các vị trí enemy[ahead2] để xử lí va chạm
    string saved_path = ""; // lấy link ảnh chú chó shiba
    position posDoge;
};
