
#pragma once
#include "common.h"
#include "cinder/Font.h"

using namespace ci;
using namespace ci::app;

class cTitle{
private:

  bool isChange;

public:

  Font font;
  ColorA text_color;
  float logo_x;
  float logo_z;
  float text_alpha;
  bool end_anime;

  cTitle();
  void setup();
  void keyDown(KeyEvent);
  void change(int&);
  void update();
  void draw();
};