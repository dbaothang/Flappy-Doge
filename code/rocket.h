#pragma once

#include "lib.h"
#include "enemy.h"
#include <iostream>

using namespace std;


class rocket : LTexture
{
  private:

  position posRocket;
  int ahead = 0;

  public:

  bool init();

  void Free();

  void render();

  void update();

};
