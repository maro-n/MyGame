
#pragma once
#include "common.h"
#include "cinder/Rand.h"

using namespace ci;
using namespace ci::app;

struct Enemy{
  Vec3f pos;
  Vec3f size;
  float speed;
  float player_to_enemy;
  Color color;

  Vec3f getPos(){
    return pos;
  }
};

class cEnemy{
private:

  int count;
  int timer;
  int pop_sec;
  bool is_draw;

public:
  cEnemy();
  void setup();
  void update();
  void draw();
};