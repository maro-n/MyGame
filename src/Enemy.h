
#pragma once
#include "common.h"
#include "Player.h"
#include "cinder/Rand.h"

using namespace ci;
using namespace ci::app;

class cEnemy{
private:
  struct Enemy{
    Vec3f pos;
    Vec3f size;
    float speed;
    float player_to_enemy;
    Color color;
  }; 
  std::list<Enemy> enemy;
  Enemy enemy_init;

  cPlayer* player_ref;

  int count;
  int timer;
  int pop_sec;
  bool is_draw;

public:
  cEnemy();
  void setup();
  void SetReference(cPlayer*);
  void update(bool&);
  void draw();
};