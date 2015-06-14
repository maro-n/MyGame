
#pragma once
#include "common.h"

using namespace ci;
using namespace ci::app;

class cResult{
private:
  
  bool isChange;

  Font font;
  ColorA text_color;
  float text_alpha;

public:
  cResult();
  void setup();
  void keyDown(KeyEvent);
  void change(int&);
  void update();
  void draw();
};