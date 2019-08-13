#include "EnemyFlyingRocket.h"

EnemyFlyingRocket::EnemyFlyingRocket()
{
	tag = ENEMY;
	type = FLYINGROCKET;

	animations[STANDING] = new Animation(ENEMY, 40, 41);
	animations[RUNNING] = new Animation(ENEMY, 40, 41);
	animations[INJURED] = new Animation(ENEMY, 40);
	animations[ATTACKING] = new Animation(ENEMY, 42, 43);
	animations[DEAD] = new Animation(PLAYER, 20, 22);

	height = 24;
	width = 18;
	speed = 0.1f;
	this->isReverse = true;
	maxDistanceX = 60;
	maxDistanceY = 30;
	bullets = bulletCount = 1;
	typeAI = 0;
	this->delayTime = 5000;
}


void EnemyFlyingRocket::UpdateDistance(float dt)
{
	this->dx = vx * dt;
	this->dy = vy * dt;

	delayTime -= dt;
	if (typeAI == 0)
	{
		if (((this->vx < 0) && (this->posX - this->spawnX < -maxDistanceX))
			|| ((this->vx > 0) && (this->posX - this->spawnX > maxDistanceX))) {
			this->vy = this->vx > 0 ? -0.1f : 0.1f;
			this->vx = 0;
		}
		else if (((this->vy > 0) && (this->posY - this->spawnY > maxDistanceY))
			|| ((this->vy < 0) && (this->posY - this->spawnY < -maxDistanceY)))
		{
			this->vx = this->vy > 0 ? speed : -speed;
			this->vy = 0;
		}
		if (stateName == ATTACKING)
		{
			if (curAnimation->isLastFrame)
			{
				ChangeState(RUNNING);
			}
		}
	}
}

void EnemyFlyingRocket::ChangeState(State StateName)
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
		this->isReverse = true;
		this->isActive = true;
		/*if (activeDistance)
		{
			this->isActive = true;
			auto distance = player->posX - this->spawnX;

			if (activeDistance * distance > 0 && distance >= this->activeDistance)
			{
				this->vy = 0;
				this->isActive = true;
			}
		}*/
		break;
	}
	/*	vx = 0.2f;
		isActive = true;
		break;*/
	case ATTACKING:
	{
		dx = dy = 0;
		break;
	}
	}
	this->stateName = StateName;
	this->curAnimation = animations[stateName];
}
