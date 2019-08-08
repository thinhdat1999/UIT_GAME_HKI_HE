#include "EnemyElectricBat2.h"

EnemyElectricBat2::EnemyElectricBat2()
{
	tag = ENEMY;
	type = ELECTRICBAT;

	//type 1: Doi treo nguoc
	animations[STANDING] = new Animation(ENEMY, 53);
	animations[ACTIVE] = new Animation(ENEMY, 56, 57, 300);
	animations[RUNNING] = new Animation(ENEMY, 58, 60);
	animations[DEAD] = new Animation(PLAYER, 20, 22);

	width = 15;
	height = 15;
	typeAI = 0;
	this->isActive = false;
}

void EnemyElectricBat2::UpdateDistance(float dt)
{
	switch (stateName)
	{
	case STANDING:
	{
		if (abs(player->posX - this->spawnX < 40))
		{
			ChangeState(ACTIVE);
		}
		break;
	}
	case ACTIVE:
	{
		if (curAnimation->isLastFrame)
			ChangeState(RUNNING);
		break;
	}

	}
	this->dx = vx * dt;
	this->dy = vy * dt;
}

void EnemyElectricBat2::ChangeState(State StateName)
{
	this->stateName = StateName;
	this->curAnimation = animations[stateName];
	switch (stateName)
	{
	case ACTIVE:
	{
		if (activeDistance) {
			auto distance = player->posX - this->spawnX;

			if (activeDistance * distance > 0 && distance >= this->activeDistance)
			{
				this->vy = this->vx = 0;
				this->isActive = true;
			}
		}
		break;
	}
	case RUNNING:
	{
		this->isActive = true;
		height += 15;
		width += 20;
		this->vx = 0.07f;
		this->vy = 0.05f;
	}
	case STANDING:
	{
		this->vx = this->vy = 0;
		this->isActive = true;
	}
	}
}
