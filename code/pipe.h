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

    const int randMin = -373 + 60; // vị trí thấp nhất của cột
    const int randMax = SCREEN_HEIGHT - LAND_HEIGHT - PIPE_SPACE - 373 - 60; // vị trí cao nhất của cột
    static bool pipeUp; // biến để cột di chuyển lên
    static bool pipeDown; // biến để cột di chuyển xuống

public:
    bool init(); // khởi tạo

    void Free(); // giải phóng

    void render(); // vẽ lên màn hình

    bool checkDown (position a, bool b); // kiểm tra để cột đi xuống

    bool checkUp (position a, bool b); // kiểm tra để cột đi lên

    void update(bool isHard); // cập nhật cột

    int width() {return getWidth();} // hàm lấy chiều rộng (theo chiều x )

    int height() {return getHeight();} // hàm lấy chiều cao (theo chiều y)

};
