
#pragma once
#include "common.h"
#include "Title.h"
#include "Game.h"
#include "Result.h"

class cScene{
private:

  cTitle m_title;
  cGame m_game;
  cResult m_result;

public:
  int scene_mode;
  cScene();
  void setup();
  void keyDown(KeyEvent);
  void keyUp(KeyEvent);
  void change();
  void update();
  void draw();
};
