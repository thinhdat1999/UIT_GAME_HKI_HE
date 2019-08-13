#include "EnemyTank.h"

EnemyTank::EnemyTank()
{
	tag = ENEMY;
	type = MINITANK;

	animations[RUNNING] = new Animation(ENEMY, 46, 48);
	animations[SPINNING_LEFT] = new Animation(ENEMY, 49);
	animations[DEAD] = new Animation(ENEMY, 46, 48);

	animations[TOP] = new Animation(ENEMY, 46);

	//Reverse true
	animations[TOPLEFT] = new Animation(ENEMY, 50);
	animations[LEFT] = new Animation(ENEMY, 47);
	animations[BOTLEFT] = new Animation(ENEMY, 51);
	animations[BOT] = new Animation(ENEMY, 48);

	//Reverse false
	animations[BOTRIGHT] = new Animation(ENEMY, 51);
	animations[RIGHT] = new Animation(ENEMY, 47);
	animations[TOPRIGHT] = new Animation(ENEMY, 50);

	animations[ATTACKING] = new Animation(ENEMY, 46);

	height = 16;
	width = 16;
	hitcount = 2;
	bullets = bulletCount = 1;
	delayTime = 3000;
	hitdelay = 1500;
	typeAI = 0;
	speed = 0;
	isActive = true;
	curAnimation = animations[LEFT];
	//isSpinning = false;
}

void EnemyTank::UpdateAttackingState(int hitcount)
{
	switch (hitcount)
	{
	case 0:
		animations[ATTACKING] = animations[TOP];
		break;
	case 1:
		animations[ATTACKING] = animations[TOPLEFT];
		isReverse = true;
		break;
	case 2:
		animations[ATTACKING] = animations[LEFT];
		isReverse = true;
		break;
	case 3:
		animations[ATTACKING] = animations[BOTLEFT];
		isReverse = true;
		break;
	case 4:
		animations[ATTACKING] = animations[BOT];
		break;
	case 5:
		animations[ATTACKING] = animations[BOTRIGHT];
		isReverse = false;
		break;
	case 6:
		animations[ATTACKING] = animations[RIGHT];
		isReverse = false;
		break;
	case 7:
		animations[ATTACKING] = animations[TOPRIGHT];
		isReverse = false;
		break;
	}
}

void EnemyTank::Update(float dt)
{
	Enemy::Update(dt);
	lastReverse = isReverse;
	UpdateAttackingState(hitcount);
	if (stateName == RUNNING)
	{
		if (curAnimation->isLastFrame)
		{
			ChangeState(RIGHT);
		}
	}
	else
		ChangeState(ATTACKING);
}

void EnemyTank::UpdateDistance(float dt)
{
	delayTime -= dt;
	hitdelay -= dt;
	this->dx = vx * dt;
	this->dy = vy * dt;
}

void EnemyTank::ChangeState(State stateName)
{

	if (stateName == RUNNING)
	{
		isActive = true;
		switch (hitcount)
		{
		case 0:
			hitcount = 1;
			break;
		case 1:
			hitcount = 2;
			break;
		case 2:
			hitcount = 3;
			break;
		case 3:
			hitcount = 4;
			break;
		case 4:
			hitcount = 5;
			break;
		case 5:
			hitcount = 6;
			break;
		case 6:
			hitcount = 7;
			break;
		case 7:
			hitcount = 0;
			break;
		}
	}
	this->stateName = stateName;
	this->curAnimation = animations[stateName];
}
