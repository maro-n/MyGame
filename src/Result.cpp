
#include "Result.h"

cResult::cResult(){
  isChange = false;
  text_alpha = 0;
  text_color = ColorA(1, 1.f, 1.f, 0.f);
}

void cResult::setup(){
  font = Font("", 100);
  isChange = false;
  text_alpha = 0;
  text_color = ColorA(1, 1.f, 1.f, 0.f);
}

void cResult::keyDown(KeyEvent event){
  if (event.getChar() == 't'){
    isChange = true;
  }
}

void cResult::update(){
  text_alpha += 0.05f;
}

void cResult::change(int& scene_change){
  if (isChange){
    scene_change = TITLE;
    isChange = false;
  }
}

void cResult::draw(){
  gl::clear(ColorA(0.f, 0.5f, 0.f, 0.8f));

  gl::pushModelView();
  gl::translate(-200, 150, -1000);
  gl::rotate(Vec3f(180, 0, 0));
  gl::drawStringCentered(
    "SCORE : ",
    Vec2f(0, 100), text_color + std::abs(std::sin(text_alpha)), font);
  gl::popModelView();


  gl::pushModelView();
  gl::translate(0, -150, -1000);
  gl::rotate(Vec3f(180, 0, 0));
  gl::drawStringCentered(
    "PUSH KEY [T] BACK TITLE !!",
    Vec2f(0, 100), text_color + std::abs(std::sin(text_alpha)), font);
  gl::popModelView();

}
