
#include "common.h"
#include "Scene.h"
#include "cinder/Camera.h"
#include "cinder/audio/Context.h"
#include "cinder/audio/SamplePlayerNode.h"
#include "cinder/audio/NodeEffects.h"
#include "cinder/gl/Light.h"
#include "cinder/Rand.h"

using namespace ci;
using namespace ci::app;

class CinderProjectApp : public AppNative {
private:

  cScene m_scene;

  std::unique_ptr<gl::Light> light;

  CameraPersp camera;
  CameraPersp camera2;

  audio::BufferPlayerNodeRef bgm;
  audio::GainNodeRef gain;

  bool is_start_bgm = false;

  public:
	void setup();
  void keyDown(KeyEvent event);
  void keyUp(KeyEvent event);
  void update();
	void draw();
};

void CinderProjectApp::setup()
{
  Rand::randomize();

  m_scene.setup();

  // �o�̓f�o�C�X���Q�b�g
  auto ctx = audio::Context::master();

  // �I�[�f�B�I�f�[�^��ǂݍ���ŏ�����
  audio::SourceFileRef sourceFile = audio::load(loadAsset("BGM.wav"));
  audio::BufferRef buffer = sourceFile->loadBuffer();
  bgm = ctx->makeNode(new audio::BufferPlayerNode(buffer));
  gain = ctx->makeNode(new audio::GainNode(0.5f));

  // �ǂݍ��񂾃I�[�f�B�I���o�̓f�o�C�X�Ɋ֘A�t���Ă���
  // ���Ɖ��ʗ��������
  bgm >> gain >> ctx->getOutput();

  // �o�̓f�o�C�X��L���ɂ���
  ctx->enable();


  // ���C�g�̏���
  // ���s�������P�p��
  light = std::unique_ptr<gl::Light>(new gl::Light(gl::Light::DIRECTIONAL, 0));
  light->setAmbient(Color(0.5, 0.5, 0.5));
  light->setDiffuse(Color(1.0, 1.0, 1.0));
  light->setDirection(Vec3f(0.0, 0.0, 1.0));

  // �J�����̏���
  camera = CameraPersp(getWindowWidth(), getWindowHeight(),
    35.0, 0.5, 2000.0);
  camera2 = CameraPersp(getWindowWidth(), getWindowHeight(),
    35.0, 0.5, 2000.0);


  camera.lookAt(Vec3f(0.0, 300.0, -800.0),
    Vec3f(0.0, 0.0, 0.0));
  camera2.lookAt(Vec3f(0.0, 0.0, 300.0),
    Vec3f(0.0, 0.0, 0.0));


  // �J�����OON
  gl::enable(GL_CULL_FACE);

  // ���_�J���[��Ώۂɂ��ă��C�e�B���O�̌v�Z���s��
  gl::enable(GL_COLOR_MATERIAL);

  // ���C�e�B���OON
  gl::enable(GL_LIGHTING);
  // �@���𐳋K������
  gl::enable(GL_NORMALIZE);

  gl::enableAlphaBlending();

  // �[�x�o�b�t�@
  gl::enableDepthRead();
  gl::enableDepthWrite();
}

void CinderProjectApp::keyDown(KeyEvent event)
{
  m_scene.keyDown(event);
}

void CinderProjectApp::keyUp(KeyEvent event)
{
  m_scene.keyUp(event);
}

void CinderProjectApp::update()
{
  m_scene.change();

  if (!is_start_bgm){
    bgm->start();
    is_start_bgm = true;
  }
  if (bgm->isEof()){
    is_start_bgm = false;
  }
  
  m_scene.update();
}

void CinderProjectApp::draw()
{
  gl::clear(Color(0.2f, 0.2f, 0.2f));

  if (m_scene.scene_mode == GAME){
    gl::setMatrices(camera);
  }
  else{
    gl::setMatrices(camera2);
  }

  light->enable();

  m_scene.draw();

  light->disable();
}

CINDER_APP_NATIVE( CinderProjectApp, RendererGl )
