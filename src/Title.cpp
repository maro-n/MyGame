
#include "Title.h"

cTitle::cTitle(){
  isChange = false;
  text_alpha = 0;
  text_color = ColorA(1, 1, 1, 0);
  logo_x = 1000;
  logo_z = 150;
  end_anime = false;
}

void cTitle::setup(){
  font = Font("", 15);
  isChange = false;
  text_alpha = 0;
  text_color = ColorA(1, 1, 1, 0);
  logo_x = 1000;
  logo_z = 150;
  end_anime = false;
}

void cTitle::keyDown(KeyEvent event){
  if (event.getChar() == 'g'){
    isChange = true;
  }
}

void cTitle::update(){
  text_alpha += 0.05f;
  logo_x *= -0.9f;
  if (isChange){
    logo_z -= 10.0f;
  }
  if (logo_z <= -500){
    end_anime = true;
  }
}

void cTitle::change(int& scene_change){
  if (isChange && end_anime){
    scene_change = GAME;
    isChange = false;
    end_anime = false;
  }
}

void cTitle::draw(){
  gl::clear(ColorA(0.5f, 0.f, 0.f, 0.8f));

  gl::pushModelView();
  gl::translate(logo_x, 50, 50);
  gl::rotate(Vec3f(180, 0, 0));
  gl::drawStringCentered(
    "PUSH KEY [G] GAME START !!",
    Vec2f(0, 100), text_color + std::abs(std::sin(text_alpha)), font);
  gl::popModelView();

  gl::pushModelView();
  gl::translate(logo_x, 120, logo_z);
  gl::rotate(Vec3f(180, 0, 0));
  gl::drawStringCentered(
    "R o l l  a n d  A v o i d",
    Vec2f(0, 100), text_color + std::abs(std::sin(text_alpha)), font);
  gl::popModelView();
}
