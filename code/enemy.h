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
  static int frame;

  public:

  static const int enemy_animation=5;

  SDL_Rect gSpriteClips [enemy_animation];

  bool init ();

  void render(bool isPause);

  void Free();

  void update();

  int width() {return getWidth();}

  int height() {return getHeight();}

};
