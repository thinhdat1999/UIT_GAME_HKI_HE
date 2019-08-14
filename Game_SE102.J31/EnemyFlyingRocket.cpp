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
	this->isOnGround = false;
	this->delayTime = 5000;
}

void EnemyFlyingRocket::CheckGroundCollision(std::unordered_set<Platform*> grounds)
{
	// Trên không
	if (this->vy)
	{
		this->isOnGround = false;
	}
	// Tìm được vùng đất va chạm
	if (DetectGround(grounds))
	{
		if (this->vy < 0)
		{
			this->isOnGround = true;
			this->vy = this->dy = 0;
			this->posY = groundBound.rect.y + (this->height >> 1);
		}
	}
}


void EnemyFlyingRocket::UpdateDistance(float dt)
{
	this->dx = vx * dt;
	this->dy = vy * dt;

	delayTime -= dt;
	if (typeAI == 0)
	{
		switch (stateName) {
		case RUNNING:
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
			break;
		}
		case ATTACKING:
		{
			if (curAnimation->isLastFrame)
			{
				ChangeState(RUNNING);
			}
			break;
		}
		case INJURED:
			if (isOnGround) {
				ChangeState(DEAD);
			}
			break;
		}
	}
}

void EnemyFlyingRocket::Update(float dt)
{
	UpdateDistance(dt);
	curAnimation->Update(dt);
	if (flashingTime > 0) {
		flashingTime -= dt;
	}
	else {
		flashingTime = 0;
	}
	if (this->stateName == DEAD)
	{
		if (this->curAnimation->isLastFrame) {
			this->isDead = true;
			this->isActive = false;
		}
	}
}

void EnemyFlyingRocket::ChangeState(State StateName)
{
	this->stateName = StateName;
	
	switch (stateName)
	{
	case STANDING:
	{
		this->isOutScreen = false;
		this->isActive = false;
		this->isDead = false;
		this->isOnGround = false;
		break;
	}
	case RUNNING:
	{
		this->isReverse = true;
		this->isActive = true;
		break;
	}
	case INJURED: {
		this->vx = this->dx = 0;
		this->vy = this->dy = -0.1f;
		break;
	}
	case DEAD:
	{
		this->vx = this->dx = 0;
		this->vy = this->dy = 0;
		this->posY = this->groundBound.rect.y + (this->height >> 1);
		break;
	}
	case ATTACKING:
	{
		dx = dy = 0;
		break;
	}
	}
	this->curAnimation = animations[stateName];
}

void EnemyFlyingRocket::Render(float cameraX, float cameraY)
{
	UpdateColor();
	if (this->stateName == INJURED) {
		this->isReverse = !this->isReverse;
	}
	screenX = this->posX - cameraX;
	screenY = cameraY - this->posY;
	curAnimation->isReverse = this->isReverse;
	curAnimation->AlphaRender(screenX, screenY, curColor, NULL);
}
