#pragma once

#include "lib.h"
#include <vector>

using namespace std;


class land : LTexture
{
public:
    bool init(); // khởi tạo

    void Free(); // giải phóng

    void render(); // vẽ lên màn hình

    void update(); // cập nhật land

private:
    position posLand;
    string saved_path = ""; // lấy link ảnh của land
};
