#include "EnemyBlueSoldier.h"

EnemyBlueSoldier::EnemyBlueSoldier()
{
	animations[STANDING] = new Animation(ENEMY, 29);
	animations[RUNNING] = new Animation(ENEMY, 29, 31);
	animations[SITTING] = new Animation(ENEMY, 33);
	animations[JUMPING] = new Animation(ENEMY, 33);
	animations[ATTACKING] = new Animation(ENEMY, 32);
	animations[INJURED] = new Animation(ENEMY, 34);
	animations[DEAD] = new Animation(PLAYER, 20, 22);

	tag = ENEMY;
	type = BLUESOLDIER;
	width = 23;
	height = 40;
	speed = 0.128f;
	bullets = bulletCount = 1;
	this->typeAI = 0;
	curColor = originalColor;
}

void EnemyBlueSoldier::DetectCurGround(std::unordered_set<Platform*> grounds)
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

void EnemyBlueSoldier::UpdateDistance(float dt)
{
	//Loại 0: Chỉ đứng lên bắn và ngồi xuống
	//Loại 1: Chạy, khi ra khỏi groundBound thì jump, cho đến khi ra khỏi màn hình
	//Loại 2: Chạy vài bước đứng lại bắn, cứ thế lặp lại
	switch (this->typeAI) {
	case 0:
	{
		this->isReverse = (player->posX > this->posX);
		delayTime -= dt;
		switch (this->stateName) {
		case SITTING:
		{
			if (delayTime <= 0)
			{
				this->posY += 8;
				this->ChangeState(ATTACKING);

				delayTime = 3200;
			}
			break;
		}
		case ATTACKING:
		{
			this->dx = 0;
			break;
		}
		break;
		}
		break;
	}
	case 1: 
	{
		if (!this->isOnGround) this->vy -= GRAVITY_SPEED;

		if (this->isOnGround && ((this->vx < 0 && this->posX - 30 < curGroundBound.rect.x)
			|| (this->vx > 0 && this->posX + 30 > curGroundBound.rect.x + curGroundBound.rect.width)))
		{
			this->isOnGround = false;
			this->vy = 0.26f;
			this->curAnimation = animations[JUMPING];
		}

		this->dx = vx * dt;
		this->dy = vy * dt;
		break;
	}
	case 2:
	{
		//this->isReverse = (player->posX > this->posX);
		delayTime -= dt;

		switch (this->stateName)
		{
		case RUNNING:
		{

			this->dx = vx * dt;

			if ((vx > 0 && this->posX + (this->width >> 1) >= groundBound.rect.x + groundBound.rect.width)
				|| (vx < 0 && this->posX - (this->width >> 1) <= groundBound.rect.x))
			{
				this->vx = -vx;
				this->isReverse = !this->isReverse;
			}
			if (delayTime <= 0)
			{
				this->ChangeState(ATTACKING);
				delayTime = 1500;
			}
			break;
		}
		case ATTACKING:
		{
			this->dx = 0;
			break;
		}
		}
		break;
	}
	}
}

void EnemyBlueSoldier::ChangeState(State StateName)
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
		break;
	}
	case RUNNING: {
		if (activeDistance) {
			auto distance = player->posX - this->spawnX;

			if (activeDistance * distance > 0 && distance >= this->activeDistance)
			{
				this->curGroundBound = groundBound;
				this->isOnGround = true;
				this->vy = 0;
				this->isActive = true;
			}
		}
		else {
			isActive = true;
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
