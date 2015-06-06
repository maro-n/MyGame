#include "cinder/app/AppNative.h"
#include "cinder/TriMesh.h"
#include "cinder/Camera.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Light.h"

using namespace ci;
using namespace ci::app;

class CinderProjectApp : public AppNative {
private:
  TriMesh cube_mesh;

  std::vector<Vec3f> cube_vertex;
  std::vector<Color> cube_color;

  std::unique_ptr<gl::Light> light;

  CameraPersp camera;

  Vec3f cube_translate = Vec3f(0, 0, 0);
  Vec3f cube_rotate = Vec3f(0, 0, 0);
  Matrix44f cube_matrix = Matrix44f::identity();

  int push_state = 0;
  enum push{
    None,

    a,
    s,
    d,
    w,
  };

  public:
	void setup();
  void keyDown(KeyEvent event);
  void keyUp(KeyEvent event);
  void PlayerRoll();
  void update();
	void draw();
};

void CinderProjectApp::setup()
{
  // �����̂̒��_
  // ���ォ�玞�v���� ��O0,1,2,3  ��4,5,6,7
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

  // �����̂̒��_�F
  for (int i = 0; i < 8; ++i){
    cube_color.push_back(Color(1, 1, 1));
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
    //�O
    0, 2, 1,
    0, 3, 2,

    //��
    4, 1, 5,
    4, 0, 1,

    //��
    5, 7, 4,
    5, 6, 7,

    //��
    3, 6, 2,
    3, 7, 6,

    //�E
    1, 6, 5,
    1, 2, 6,

    //��
    4, 3, 0,
    4, 7, 3,
  };
  cube_mesh.appendIndices(&cube_indices[0], sizeof(cube_indices) / sizeof(cube_indices[0]));

  // ���_�̖@����Cinder�Ɍv�Z���Ă��炤
  cube_mesh.recalculateNormals();

  // ���C�g�̏���
  // ���s�������P�p��
  light = std::unique_ptr<gl::Light>(new gl::Light(gl::Light::DIRECTIONAL, 0));
  light->setAmbient(Color(0.5, 0.5, 0.5));
  light->setDiffuse(Color(1.0, 1.0, 1.0));
  light->setDirection(Vec3f(0.0, -1.0, 0.0));

  // �J�����̏���
  camera = CameraPersp(getWindowWidth(), getWindowHeight(),
    35.0, 0.5, 2000.0);

  camera.lookAt(Vec3f(0.0, 1000.0, 1000.0),
    Vec3f(0.0, 0.0, 0.0));

  // �J�����OON
  gl::enable(GL_CULL_FACE);

  // ���_�J���[��Ώۂɂ��ă��C�e�B���O�̌v�Z���s��
  gl::enable(GL_COLOR_MATERIAL);

  // ���C�e�B���OON
  gl::enable(GL_LIGHTING);
  // �@���𐳋K������
  gl::enable(GL_NORMALIZE);

}

void CinderProjectApp::keyDown(KeyEvent event)
{
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

void CinderProjectApp::keyUp(KeyEvent event){
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

void CinderProjectApp::PlayerRoll()
{
  switch (push_state){
  case push::a :
    cube_rotate.z = 3.0f / 60.0f;
    cube_translate.x -= 0.1f;
    break;

  case push::s :
    cube_rotate.x = 3.0f / 60.0f;
    cube_translate.z += 0.1f;
    break;

  case push::d :
    cube_rotate.z = -(3.0f / 60.0f);
    cube_translate.x += 0.1f;
    break;

  case push::w :
    cube_rotate.x = -(3.0f / 60.0f);
    cube_translate.z -= 0.1f;
  }

  if (push_state == push::None){
    cube_matrix = Matrix44f::identity();
    cube_rotate = cube_rotate.zero();
  }
}

void CinderProjectApp::update()
{
  PlayerRoll();

  cube_matrix = Matrix44f::createRotation(cube_rotate) * cube_matrix;
}

void CinderProjectApp::draw()
{
  gl::clear(Color(0.2f, 0.2f, 0.2f));

  gl::setMatrices(camera);

  light->enable();

  gl::pushModelView();
  gl::scale(20.0, 20.0, 20.0);
  gl::translate(cube_translate);
  gl::multModelView(cube_matrix);

  // �|���S����`��
  gl::draw(cube_mesh);
  gl::popModelView();

  light->disable();
}

CINDER_APP_NATIVE( CinderProjectApp, RendererGl )
