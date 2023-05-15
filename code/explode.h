#pragma once

#include "lib.h"
#include "rocket.h"
#include <iostream>

using namespace std;

extern position posExplode;
extern bool boom;

class explode : LTexture
{
    private :

    int angle = 0;
    int frame = 0; // biến để làm animation cho vụ nổ
    bool stop_explode = 0; // biến này dùng để vẽ ảnh vụ nổ đang dừng lại
    static const int explode_animation=4;
    SDL_Rect gSpriteClips [explode_animation]; // xử lí animation vụ nổ

    public :

    bool init (); // khởi tạo

    void render(bool isPause); // vẽ lên màn hình

    void Free(); // giải phóng

    void update(); // cập nhật vụ nổ

    void reset_boom(); // reset lại ban đầu

    int width() {return getWidth();} // lấy chiều rộng (theo trục x)

    int height() {return getHeight();} // lấy chiều cao(theo trục y)
};


