#include "EnemyTank.h"

EnemyTank::EnemyTank(float spawnX, float spawnY)
{
	this->stateName = SPINNING_LEFT;

	animations[SPINNING_LEFT] = new Animation(ENEMY, 63, 65, 1);
	animations[SPINNING_RIGHT] = new Animation(ENEMY, 69, 69, 1);
	animations[TOP] = new Animation(ENEMY, 63);
	//Reverse false
	animations[TOPLEFT] = new Animation(ENEMY, 66);
	animations[LEFT] = new Animation(ENEMY, 64);
	animations[BOTLEFT] = new Animation(ENEMY, 67);
	animations[BOT] = new Animation(ENEMY, 65);
	//Reverse true
	animations[BOTRIGHT] = new Animation(ENEMY, 68);
	animations[RIGHT] = new Animation(ENEMY, 69);
	animations[TOPRIGHT] = new Animation(ENEMY, 70);

	this->spawnX = this->posX = spawnX;
	this->spawnY = this->posY = spawnY;

	this->isActive = true;
	this->bulletCount = 0;
	this->bullets = 1;
	this->isReverse = false;
	this->hitcount = 1;
	this->curAnimation = animations[SPINNING_LEFT];
}

void EnemyTank::UpdatePosition(float dt)
{
	this->dx = vx * dt;
	this->dy = vy * dt;
}

void EnemyTank::Update(float dt)
{
	Enemy::Update(dt);
	/*if (abs(player->posX - this->posY) <= 50)
	{
		isActive = true;
		if (isActive == true && isAttacked == false)
		{
			ChangeState(SPINNING_LEFT);
			this->vx = 0;
		}
		else if (isAttacked == true)
			ChangeState(EXPLODE);
	}*/

	if (stateName == SPINNING_LEFT)
	{
		this->isReverse = false;
		if (curAnimation->isLastFrame)
		{
			ChangeState(SPINNING_RIGHT);
			this->isReverse = true;
		}
	}
	else if (stateName == SPINNING_RIGHT)
	{
		this->isReverse == true;
		if (curAnimation->isLastFrame)
		{
			ChangeState(SPINNING_LEFT);
			this->isReverse = false;
		}
	}
}
