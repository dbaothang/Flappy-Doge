#pragma once

#include "lib.h"
#include "enemy.h"
#include <iostream>

using namespace std;

extern position posRocket;

class rocket : LTexture
{
  private:

  int ahead = 0;

  public:

  bool init();

  void Free();

  void render();

  void update();

  void reset();

  int width() {return getWidth();}

  int height() {return getHeight();}

};
