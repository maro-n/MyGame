
#include "Game.h"

cGame::cGame(){
  isChange = false;
}

void cGame::init(){
  player.setup();
  enemy.setup();
}

void cGame::setup(){
  player.setup();
  enemy.setup();
}

void cGame::keyDown(KeyEvent event){
  player.keyDown(event);
  if (event.getChar() == 'r'){
    isChange = true;
  }
}

void cGame::keyUp(KeyEvent event){
  player.keyUp(event);
}

void cGame::change(int& scene_change){
  if (isChange){
    scene_change = RESULT;
    isChange = false;
  }
}

void cGame::update(){
  enemy.update();
  player.update();
}

void cGame::draw(){
  enemy.draw();
  player.draw();
}
