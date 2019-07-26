#include "EnemyBlueSoldier.h"

EnemyBlueSoldier::EnemyBlueSoldier(float spawnX, float spawnY)
{
	animations[RUNNING] = new Animation(ENEMY, 33, 35);
	animations[SITTING] = new Animation(ENEMY, 36);
	animations[JUMPING] = new Animation(ENEMY, 37);
	animations[ATTACKING_STAND] = new Animation(ENEMY, 38);
	animations[INJURED] = new Animation(ENEMY, 39);

	this->spawnX = spawnX;
	this->spawnY = spawnY;
	this->isActive = false;
	this->bulletCount = 0;
	this->bullets = 1;
	this->stateName = RUNNING;
}

void EnemyBlueSoldier::Update(float dt)
{
	Enemy::Update(dt);
}