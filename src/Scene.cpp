
#include "Scene.h"

cScene::cScene(){
  scene_mode = TITLE;
}

void cScene::setup(){
  switch (scene_mode){
  case TITLE:
    m_title.setup();
    break;

  case GAME:
    m_game.setup();
    break;

  case RESULT:;
    m_result.setup();
    break;
  }
}

void cScene::keyDown(KeyEvent event){
  switch (scene_mode){
  case TITLE:
    m_title.keyDown(event);
    break;

  case GAME:
    m_game.keyDown(event);
    break;

  case RESULT:
    m_result.keyDown(event);
    break;
  }
}

void cScene::keyUp(KeyEvent event){
  switch (scene_mode){
  case TITLE:
    // do not
    break;
    
  case GAME:
    m_game.keyUp(event);
    break;

  case RESULT:
    // do not
    break;
  }
}

void cScene::change(){
  switch (scene_mode){
  case TITLE:
    m_title.change(scene_mode);
    break;

  case GAME:
    m_game.change(scene_mode);
    break;

  case RESULT:
    m_result.change(scene_mode);
    break;
  }
}

void cScene::update(){

  switch (scene_mode){
  case TITLE:
    m_result.setup();
    m_title.update();
    break;

  case GAME:
    m_title.setup();
    m_game.update();
    break;

  case RESULT:
    m_game.init();
    m_result.update();
    break;
  }
}

void cScene::draw(){
  switch (scene_mode){
  case TITLE:
    m_title.draw();
    break;

  case GAME:
    m_game.draw();
    break;

  case RESULT:
    m_result.draw();
    break;
  }
}
