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

void Enemy::ChangeState(State StateName)
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

	this->stateName = StateName;
	this->curAnimation = animations[stateName];
}

Rect Enemy::GetSpawnRect()
{
	return Rect(spawnX - (width >> 1), spawnY - (height >> 1), width, height);
}


bool Enemy::isFinishAttack()
{
	return ((this->stateName == ATTACKING || this->stateName == ATTACKING_SIT) && curAnimation->isLastFrame);
}


void Enemy::Update(float dt)
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
		if (curAnimation->isLastFrame == true) {
			this->isDead = true;
			this->isActive = false;
		}
	}
}

void Enemy::UpdateDistance(float dt)
{
	this->dx = vx * dt;
	this->dy = vy * dt;
}

void Enemy::Render(float cameraX, float cameraY)
{
	UpdateColor();
	screenX = this->posX - cameraX;
	screenY = cameraY - this->posY;
	curAnimation->isReverse = this->isReverse;
	curAnimation->AlphaRender(screenX, screenY, curColor, NULL);
}

void Enemy::DetectSpawnY(std::unordered_set<Platform*> grounds)
{
	for (auto g : grounds)
	{
		if (g->rect.x < this->posX && this->posX < g->rect.x + g->rect.width
			&& g->rect.y >= groundBound.rect.y && this->posY > g->rect.y)
		{
			groundBound = *g;
		}
	}
	this->spawnY = this->posY = this->groundBound.rect.y + (this->height >> 1);
}

bool Enemy::DetectGround(std::unordered_set<Platform*> grounds)
{
	auto rbp = this->GetRect();					//rect broading-phase
	auto bottom = rbp.y - rbp.height;
	rbp.y = rbp.y + dy;

	if (rbp.isContain(groundBound.rect) && (bottom >= groundBound.rect.y))
		return true;

	for (auto g : grounds)
	{
		if (rbp.isContain(g->rect) && (bottom >= g->rect.y))
		{
			groundBound = *g;
			return true;
		}
	}
	return false;
}

void Enemy::UpdateColor()
{
	if (flashingTime > 0) {
		if (curColor == flashColor) {
			curColor = originalColor;
		}
		else {
			curColor = flashColor;
		}
	}
	else curColor = originalColor;
}