#include "Enemy.h"

Enemy::Enemy()
{
	tag = ENEMY;
	animations[EXPLODED] = new Animation(PLAYER, 20, 22);
}

void Enemy::Respawn()
{
	this->vx = this->vy = this->dx = this->dy = 0;
	this->posX = this->spawnX;
	this->posY = this->spawnY;
	this->isDead = false;
	this->isReverse = true;
	this->isActive = false;
}

void Enemy::ChangeState(State newState)
{
	switch (stateName)
	{
	case STANDING:
	{
		this->isOutScreen = false;
		this->isActive = false;
		this->isDead = false;
		break;
	}

	case RUNNING:
	{
		this->isActive = true;
		break;
	}

	case DEAD:
	{
		break;
	}
	}

	this->stateName = stateName;
	this->curAnimation = animations[stateName];
}

void Enemy::Update(float dt)
{
	if (isActive == true)
		curAnimation->Update(dt);
}

void Enemy::Render(float cameraX, float cameraY)
{
	screenX = this->posX - cameraX;
	screenY = cameraY - this->posY;
	curAnimation->isReverse = this->isReverse;
	curAnimation->Render(screenX, screenY);
}