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
  int frame = 0;
  static const int enemy_animation=5;
  SDL_Rect gSpriteClips [enemy_animation];

  public:

  bool init ();

  void render(bool isPause);

  void Free();

  void update();

  void reset();

  int width() {return getWidth();}

  int height() {return getHeight();}

};
