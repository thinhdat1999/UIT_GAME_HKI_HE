#include "EnemyElectricBat.h"

EnemyElectricBat::EnemyElectricBat(float spawnX, float spawnY)
{
	this->stateName = STANDING;

	animations[STANDING] = new Animation(ENEMY, 71);
	animations[ACTIVE] = new Animation(ENEMY, 73, 74);
	animations[RUNNING] = new Animation(ENEMY, 76, 78);

	this->spawnX = this->posX = spawnX;
	this->spawnY = this->posY = spawnY;

	this->vx = 0.0f;
	this->isActive = false;
}

void EnemyElectricBat::UpdatePosition(float dt)
{
	this->dx = vx * dt;
	this->dy = vy * dt;
}

void EnemyElectricBat::Update(float dt)
{
}