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
	bullets = bulletCount = 1;
	//speed = 0.1f;
	typeAI = 0;
	this->delayTime = 5000;
}


void EnemyFlyingRocket::UpdateDistance(float dt)
{
	delayTime -= dt;
	this->dx = vx * dt;
	if (typeAI = 0)
	{
		this->isReverse = (player->posX > this->posX);
		if (stateName == ATTACKING)
		{
			if (curAnimation->isLastFrame)
			{
				ChangeState(RUNNING);
			}
		}
	}
	//}
	//if (posX < 80)
	//{
	//	posX = 80;
	//	speed = -0.1f;
	//}
	//if (posX > 160)
	//{
	//	posX = 160;
	//}


}

void EnemyFlyingRocket::ChangeState(State StateName)
{
	isActive = true;
	this->stateName = StateName;
	this->curAnimation = animations[stateName];
	switch (stateName)
	{
	case RUNNING:
	{
		if (activeDistance)
		{
			this->isActive = true;
			auto distance = player->posX - this->spawnX;

			if (activeDistance * distance > 0 && distance >= this->activeDistance)
			{
				this->vy = 0;
				this->isActive = true;
			}
		}
		break;
	}
	/*	vx = 0.2f;
		isActive = true;
		break;*/
	case ATTACKING:
		vx = 0;
		break;
	}
}
