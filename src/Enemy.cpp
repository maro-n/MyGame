
#include "Enemy.h"

cEnemy::cEnemy(){
  enemy_init = {
    Vec3f(0, 0, 0), Vec3f(20, 20, 20), 20, 0, Color(0, 0, 0),
  };
  count = 1;
  timer = -1;
  pop_sec = 3;
  is_draw = true;
}

void cEnemy::setup(){
  enemy_init = {
    Vec3f(0, 0, 0), Vec3f(20, 20, 20), 20, 0, Color(0, 0, 0),
  };
  count = 1;
  timer = -1;
  pop_sec = 3;
  is_draw = true;
  enemy.clear();
}

void cEnemy::SetReference(cPlayer* pl_ref){
  player_ref = pl_ref;
}

void cEnemy::update(bool& isEnd){

  timer++;
  if (timer % (pop_sec * 60) == 0){
    enemy_init.size = Vec3f(
      Rand::randFloat(150, 250),
      Rand::randFloat(150, 250),
      Rand::randFloat(150, 250)
      );

    enemy_init.pos = Vec3f(
      Rand::randFloat(-120.f, 120.f),
      Rand::randFloat(-120.f, 120.f),
      1200.f);

    if (timer / 60 == 3 * count){
      enemy_init.speed = Rand::randFloat(1.0f * count, 1.5f * count);
      timer = 0;
      count++;
      if (count % 10 == 0){
        pop_sec++;
      }
    }
    else{
      enemy_init.speed = Rand::randFloat(1.0f, 2.0f);
    }

    enemy_init.color = {
      Rand::randFloat(0.5f, 1.0f),
      Rand::randFloat(0.5f, 1.0f),
      Rand::randFloat(0.5f, 1.0f),
    };

    enemy_init.player_to_enemy = enemy_init.pos.z - (enemy_init.size.z / 2 + 20);

    enemy.push_back(enemy_init);
  }

  std::list<Enemy>::iterator enemy_it = enemy.begin();

  while (enemy_it != enemy.end()){

    enemy_it->pos.z -= enemy_it->speed;

    enemy_it->player_to_enemy = enemy_it->pos.z - (enemy_init.size.z / 2 + 20);


    if (enemy_it->player_to_enemy <= 0){
      if (player_ref->cube_translate.x + 20 >= enemy_it->pos.x - enemy_it->size.x / 2){
        if (player_ref->cube_translate.x - 20 <= enemy_it->pos.x + enemy_it->size.x / 2){
          isEnd = true;
        }
      }

      enemy_it = enemy.erase(enemy_it);
      continue;
    }
    ++enemy_it;
  }
}

void cEnemy::draw(){
  for (auto& enemies : enemy){
    //“GˆÚ“®
    gl::color(enemies.color);
    gl::drawCube(enemies.pos, enemies.size);
    gl::color(1.0f, 0.0f, 0.0f);
    gl::drawStrokedCube(enemies.pos, enemies.size);
    gl::color(0.5f, 0.5f, 0.5f);
  }
}