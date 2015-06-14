
#pragma once
#include "common.h"
#include "cinder/Rand.h"
#include "cinder/TriMesh.h"
#include "Enemy.h"

using namespace ci;
using namespace ci::app;

class cPlayer{
private:
  TriMesh cube_mesh;

  std::vector<Vec3f> cube_vertex;
  std::vector<Color> cube_color;

  Matrix44f cube_matrix;

  int push_state = 0;
  enum push{
    None,

    a,
    s,
    d,
    w,
  };

public:
  cPlayer();

  Vec3f cube_translate;
  Vec3f cube_rotate;

  void keyDown(KeyEvent);
  void keyUp(KeyEvent);
  void PlayerRoll();
  void setup();
  void update();
  void draw();
};