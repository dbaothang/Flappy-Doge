#pragma once

#include "lib.h"
#include <iostream>
#include <vector>

using namespace std;

extern vector<position> posEnemy;

class enemy : LTexture
{
  private:

  int angle = 0;
  int frame = 0; // biến để làm animation cho dơi
  static const int enemy_animation=5;
  SDL_Rect gSpriteClips [enemy_animation]; // xử lí animation dơi

  public:

  bool init (); // khởi tạo

  void render(bool isPause); // vẽ lên màn hình

  void Free(); // giải phóng

  void update(); // cập nhật dơi

  void reset(); // reset lại frame

  int width() {return getWidth();} // hàm lầy độ dài (theo trục x)

  int height() {return getHeight();} // hàm lấy độ cao (theo trục y)

};
