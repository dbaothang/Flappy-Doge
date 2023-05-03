#pragma once

#include "lib.h"
#include "enemy.h"
#include <iostream>

using namespace std;

extern position posRocket;

class rocket : LTexture
{
  private:

  int ahead = 0; // giá trị để xét các các con dơi ( enemy[ehead] )

  public:

  bool init(); // khởi tạo

  void Free(); // giải phóng

  void render(); // vẽ ra màn hình

  void update(); // cập nhật rocket

  void reset(); // cập nhật lại như ban đầu

  int width() {return getWidth();} // hàm lấy chiều rộng ( theo chiều x )

  int height() {return getHeight();} // hàm lấy chiều cao ( theo chiều y )

};
