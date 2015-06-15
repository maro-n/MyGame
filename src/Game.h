
#pragma once
#include "common.h"
#include "Player.h"
#include "Enemy.h"

using namespace ci;
using namespace ci::app;

class cGame{
private:

  cPlayer player;
  cEnemy enemy;

  bool isChange;

public:
  cGame();
  void init();
  void setup();
  void keyDown(KeyEvent);
  void keyUp(KeyEvent);
  void change(int&);
  void update();
  void draw();
};