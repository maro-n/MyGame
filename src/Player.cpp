
#include "Player.h"

cPlayer::cPlayer(){
  cube_translate = Vec3f(0, 0, 0);
  cube_rotate = Vec3f(0, 0, 0);
  cube_matrix = Matrix44f::identity();

  // 立方体の頂点
  // 左上から時計回りに 手前0,1,2,3  奥4,5,6,7
  cube_vertex.push_back({ -1, 1, 1 });    // 0
  cube_vertex.push_back({ 1, 1, 1 });    // 1
  cube_vertex.push_back({ 1, -1, 1 });    // 2
  cube_vertex.push_back({ -1, -1, 1 });    // 3

  cube_vertex.push_back({ -1, 1, -1 });    // 4
  cube_vertex.push_back({ 1, 1, -1 });    // 5
  cube_vertex.push_back({ 1, -1, -1 });    // 6
  cube_vertex.push_back({ -1, -1, -1 });    // 7

  Vec3f cube_vertices[] = {
    cube_vertex[0],
    cube_vertex[1],
    cube_vertex[2],
    cube_vertex[3],
    cube_vertex[4],
    cube_vertex[5],
    cube_vertex[6],
    cube_vertex[7],
  };
  cube_mesh.appendVertices(&cube_vertices[0], sizeof(cube_vertices) / sizeof(cube_vertices[0]));

  // 立方体の頂点色
  for (int i = 0; i < 8; ++i){
    cube_color.push_back(Color(randFloat(0.5f, 1.0f), randFloat(0.5f, 1.0f), randFloat(0.5f, 1.0f)));
  }

  Color cube_colors[] = {
    { cube_color[0] },
    { cube_color[1] },
    { cube_color[2] },
    { cube_color[3] },
    { cube_color[4] },
    { cube_color[5] },
    { cube_color[6] },
    { cube_color[7] },
  };
  cube_mesh.appendColorsRgb(&cube_colors[0], sizeof(cube_colors) / sizeof(cube_colors[0]));

  uint32_t cube_indices[] = {
    //前
    0, 2, 1,
    0, 3, 2,

    //上
    4, 1, 5,
    4, 0, 1,

    //後
    5, 7, 4,
    5, 6, 7,

    //下
    3, 6, 2,
    3, 7, 6,

    //右
    1, 6, 5,
    1, 2, 6,

    //左
    4, 3, 0,
    4, 7, 3,
  };
  cube_mesh.appendIndices(&cube_indices[0], sizeof(cube_indices) / sizeof(cube_indices[0]));

  // 頂点の法線をCinderに計算してもらう
  cube_mesh.recalculateNormals();
}

void cPlayer::setup(){
  cube_translate = Vec3f(0, 0, 0);
  cube_rotate = Vec3f(0, 0, 0);
  cube_matrix = Matrix44f::identity();
}

void cPlayer::keyDown(KeyEvent event){
  if (event.getChar() == 'a'){
    push_state = push::a;
  }
  if (event.getChar() == 's'){
    push_state = push::s;
  }
  if (event.getChar() == 'd'){
    push_state = push::d;
  }
  if (event.getChar() == 'w'){
    push_state = push::w;
  }
}

void cPlayer::keyUp(KeyEvent event){
  if (event.getChar() == 'a'){
    push_state = push::None;
  }
  if (event.getChar() == 's'){
    push_state = push::None;
  }
  if (event.getChar() == 'd'){
    push_state = push::None;
  }
  if (event.getChar() == 'w'){
    push_state = push::None;
  }
}

void cPlayer::PlayerRoll(){
  switch (push_state){
  case push::a:
    cube_rotate.y = -9.0f / 60.0f;
    if (cube_translate.x > 8){
      cube_translate.x = 8;
    }
    else{
      cube_translate.x += 0.3f;
    }
    break;

  case push::s:
    cube_rotate.x = -9.0f / 60.0f;
    if (cube_translate.y < -6){
      cube_translate.y = -6;
    }
    else{
      cube_translate.y -= 0.3f;
    }
    break;

  case push::d:
    cube_rotate.y = 9.0f / 60.0f;
    if (cube_translate.x < -8){
      cube_translate.x = -8;
    }
    else{
      cube_translate.x -= 0.3f;
    }
    break;

  case push::w:
    cube_rotate.x = 9.0f / 60.0f;
    if (cube_translate.y > 6){
      cube_translate.y = 6;
    }
    else{
      cube_translate.y += 0.3f;
    }
  }

  if (push_state == push::None){
    cube_rotate = cube_rotate.zero();
  }
}

void cPlayer::update(){
  PlayerRoll();

  cube_matrix = Matrix44f::createRotation(cube_rotate) * cube_matrix;
}

void cPlayer::draw(){
  gl::pushModelView();
  gl::scale(20.0, 20.0, 20.0);
  gl::translate(cube_translate);
  gl::multModelView(cube_matrix);

  // ポリゴンを描画
  gl::draw(cube_mesh);
  gl::popModelView();
}