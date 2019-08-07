#include "EnemyRocketSoldier.h"

EnemyRocketSoldier::EnemyRocketSoldier()
{
	animations[STANDING] = new Animation(ENEMY, 35);
	animations[RUNNING] = new Animation(ENEMY, 35, 37);
	animations[SITTING] = new Animation(ENEMY, 38);
	animations[JUMPING] = new Animation(ENEMY, 38);
	animations[ATTACKING_SIT] = new Animation(ENEMY, 38);
	animations[ATTACKING] = new Animation(ENEMY, 35);
	animations[INJURED] = new Animation(ENEMY, 39);
	animations[DEAD] = new Animation(PLAYER, 20, 22);
	tag = ENEMY;
	type = ROCKETSOLDIER;
	width = 23;
	height = 40;
	speed = 0.1f;
	typeAI = 0;
	bullets = bulletCount = 1;
	curColor = originalColor;
}

EnemyRocketSoldier::~EnemyRocketSoldier()
{
}

void EnemyRocketSoldier::UpdateDistance(float dt)
{
	switch (this->typeAI) {
	case 0:
	{
		this->isReverse = (player->posX > this->posX);
		delayTime -= dt;
		switch (this->stateName) {
		case RUNNING:
		{
			this->dx = vx * dt;
			if (abs(this->posX - this->spawnX) >= 60)
			{
				this->posY -= 8;
				this->ChangeState(ATTACKING);
				delayTime = 1600;
			}
			break;
		}
		case ATTACKING:
		{
			this->dx = 0;
			if (delayTime <= 0) {
				ChangeState(ATTACKING_SIT);
				delayTime = 1600;
			}
			break;
		}
		case ATTACKING_SIT:
			this->dx = 0;

			if (delayTime <= 0) {
				ChangeState(ATTACKING);
				delayTime = 1600;
			}
		break;
		}
		break;
	}
	//case 1:
	//{
	//	delayTime -= dt;
	//	vx -= 0.01;
	//	switch (this->stateName)
	//	{
	//	case RUNNING:
	//	{
	//		this->dx = vx * dt;

	//		if (vx <= 0)
	//		{
	//			this->posY -= 8;

	//			this->ChangeState(ATTACKING_SIT);
	//			delayTime = 1600;
	//		}
	//		break;
	//	}
	//	case ATTACKING:
	//	{
	//		this->dx = 0;
	//		break;
	//	}
	//	}
	//	break;
	//}
	//case 2:
	//{
	//	//this->isReverse = (player->posX > this->posX);
	//	delayTime -= dt;

	//	switch (this->stateName)
	//	{
	//	case RUNNING:
	//	{

	//		this->dx = vx * dt;

	//		if ((vx > 0 && this->posX + (this->width >> 1) >= groundBound.rect.x + groundBound.rect.width)
	//			|| (vx < 0 && this->posX - (this->width >> 1) <= groundBound.rect.x))
	//		{
	//			this->vx = -vx;
	//			this->isReverse = !this->isReverse;
	//		}
	//		if (delayTime <= 0)
	//		{
	//			this->ChangeState(ATTACKING);
	//			delayTime = 2000;
	//		}
	//		break;
	//	}
	//	case ATTACKING:
	//	{
	//		this->dx = 0;
	//		break;
	//	}
	//	}
	//	break;
	//}
	}
}
void EnemyRocketSoldier::DetectCurGround(std::unordered_set<Platform*> grounds)
{
	for (auto g : grounds)
	{
		if (this->posX >= g->rect.x && this->posX <= g->rect.x + g->rect.width &&
			this->posY - (this->height >> 1) <= g->rect.y && this->posY > g->rect.y)
		{
			this->vy = 0;
			this->posY = g->rect.y + (this->height >> 1);
			this->curGroundBound = *g;
			this->isOnGround = true;
			this->curAnimation = animations[RUNNING];
			break;
		}
	}
}
void EnemyRocketSoldier::ChangeState(State StateName)
{
	switch (StateName)
	{
	case STANDING:
	{
		this->isOutScreen = false;
		this->isActive = false;
		this->isDead = false;
		break;
	}
	case SITTING: {
		this->isActive = true;
		this->vx = this->vy = this->dx = this->dy = 0;
		this->height = 20;
		this->posY -= 8;
	}
	case ATTACKING: {
		this->bullets = this->bulletCount = 1;
		this->height = 40;
		this->posY += 8;
		break;
	}
	case ATTACKING_SIT: {
		this->bullets = this->bulletCount = 1;
		this->height = 20;
		this->posY -= 8;
	}
	case RUNNING: {
		this->isActive = true;
		auto distance = player->posX - this->spawnX;

		if (activeDistance * distance > 0 && distance >= this->activeDistance)
		{
			this->curGroundBound = groundBound;
			this->isOnGround = true;
			this->vy = 0;
			this->isActive = true;
		}
		break;
	}
	case DEAD:
	{
		this->vx = this->dx = 0;
		this->dy = 0;
		this->posY = this->groundBound.rect.y + (this->width >> 1);
		break;
	}
	}

	this->stateName = StateName;
	this->curAnimation = animations[stateName];
}