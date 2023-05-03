#pragma once

#include "lib.h"
#include <iostream>

using namespace std;

extern position posLaser;
extern bool laserOn;

class laser : LTexture
{

    public:

    bool init (); // khởi tạo

    void Free(); // giải phóng

    void render(); // vẽ lên màn hình

    void reset(); // điều chỉnh lại từ đầu

    int width() {return getWidth();} // hàm lấy chiều rộng (theo trục x)

    int height() {return getHeight();} // hàm lấy độ cao (theo trục y)

};
