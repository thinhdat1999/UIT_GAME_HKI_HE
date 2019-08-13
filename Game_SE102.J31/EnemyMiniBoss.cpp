#include "EnemyMiniBoss.h"

EnemyMiniBoss::EnemyMiniBoss()
{
	//TypeAI 1
	animations[STANDING] = new Animation(ENEMY, 16);
	animations[RUNNING] = new Animation(ENEMY, 18, 20, DEFAULT_TPF >> 1);
	animations[INJURED] = new Animation(ENEMY, 16, 17);
	animations[ATTACKING] = new Animation(ENEMY, 24);
	animations[FALLING] = new Animation(ENEMY, 21);
	animations[THROWING] = new Animation(ENEMY, 22, 23, DEFAULT_TPF);
	animations[LOWHP_STANDING] = new Animation(ENEMY, 25);
	animations[LOWHP_ATTACKING] = new Animation(ENEMY, 26, 28, DEFAULT_TPF >> 1);
	animations[DEAD] = new Animation(ENEMY, 25);
	animations[EXPLODED] = new Animation(PLAYER, 20, 22);
	tag = ENEMY;
	type = BOSS2;
	health = 6;
	width = ENEMY_BOSS_WIDTH;
	height = ENEMY_BOSS_HEIGHT;
	bullets = bulletCount = 1;
	typeAI = 0;
	delayDead = ENEMY_BOSS_DELAY_DEATH;
	delayAttack = 1500;
	speed = 0;
	bulletType = 0;
	flashingTime = 0;
}

void EnemyMiniBoss::UpdateDistance(float dt)
{
	if (stateName == DEAD) return;

	this->dx = vx * dt;
	this->dy = vy * dt;
	if (this->posX - (this->width >> 1) + dx <= ENEMY_BOSS_LEFT)
	{
		this->dx = this->vx = 0;
		this->posX = ENEMY_BOSS_LEFT + (this->width >> 1);
	}
	else if (this->posX + (this->width >> 1) + dx >= ENEMY_BOSS_RIGHT)
	{
		this->dx = this->vx = 0;
		this->posX = ENEMY_BOSS_RIGHT - (this->width >> 1);
	}
	if (this->posY - (this->height >> 1) + dy < this->groundBound.rect.y)
	{
		this->ChangeState(STANDING);
		this->posY = this->groundBound.rect.y + (this->height >> 1);
	}
}

void EnemyMiniBoss::UpdateState(float dt)
{
	switch (stateName) {
	case FALLING: {
		if (this->vy == 0) {
			this->ChangeState(STANDING);
		}
			
		break;
	}
	case STANDING:
	{
		if (delayAttack <= 0)
		{
			this->ChangeState(ATTACKING);
			delayAttack = 1000;
			if (bulletType == 1) {
				canShoot = true;
			}
			else if (bulletType == 0) {
				canShoot = false;
			}
		}
		break;
	}
	case RUNNING:
	{
		if (vx == 0) {
			this->ChangeState(STANDING);
			this->isReverse = !this->isReverse;
			if (this->health > 3) {
				this->bulletType = 0;
			}
			delayAttack = 1500;
		}


		break;
	}
	case ATTACKING:
	{
		if (this->health > 3) {
			if (bulletType == 0 && this->curAnimation->isLastFrame)
			{
				this->bulletType = 1;
				this->bullets = this->bulletCount = 2;
				this->ChangeState(STANDING);
			}
			else if (bulletType == 1) {
				if (delayAttack <= 0) {
					bulletCount--;
					if (bulletCount > 0) {
						ChangeState(STANDING);
					}
					else {
						ChangeState(RUNNING);
					}
					delayAttack = 1500;
					canShoot = true;
				}
				//this->ChangeState(RUNNING);
			}
		}
		else {
			if (delayAttack <= 0)
			{
				delayAttack = 2000;
				canShoot = true;
			}
			if (vx == 0) {
				this->ChangeState(STANDING);
				this->isReverse = !this->isReverse;
			}

		}
		break;
	}
	case INJURED:
	{
		// NOTE: Coi lại
		if (this->health > 3 && flashingTime <= 0) {
			this->ChangeState(STANDING);
		}
		else if (this->health <= 3) {
			bulletType = 1;
			this->typeAI = 1;
			animations[STANDING] = animations[LOWHP_STANDING];
			animations[ATTACKING] = animations[LOWHP_ATTACKING];
			this->ChangeState(STANDING);
		}
		break;
	}
	}
}

void EnemyMiniBoss::Update(float dt)
{
	if (flashingTime > 0) {
		flashingTime -= dt;
	}
	else {
		flashingTime = 0;
	}
	delayAttack -= dt;
	this->UpdateState(dt);
	this->UpdateDistance(dt);
	if (this->stateName == ATTACKING && !this->curAnimation->isLastFrame && this->bulletType == 0)
	{
		if (delayAttack <= 0) {
			curAnimation->Update(500);
			delayAttack = 500;
		}
		if (this->curAnimation->CurFrameIndex == 1) {
			canShoot = true;
		}
	}
	else {
		curAnimation->Update(dt);
	}
	if (b != NULL) {
		if (b->StateName == DEAD && !canShoot) {
			this->SubtractHealth();
		}
	}

	if (this->stateName == DEAD)
	{
		delayDead -= dt;
		/*if (isFrozenEnemies)
		{
			curAnimation->Update(dt);
		}*/
		if (delayDead <= 200) {
			this->curAnimation = animations[EXPLODED];
		}
		if (delayDead <= 0)
		{
			this->isDead = true;
			this->isActive = false;
		}
	}
}

int EnemyMiniBoss::GetHealth()
{
	return health;
}

void EnemyMiniBoss::ChangeState(State StateName)
{
	this->stateName = StateName;
	this->curAnimation = animations[stateName];
	switch (StateName)
	{
	case STANDING:
	{
		this->vx = this->dx = 0;
		this->vy = this->dy = 0;
		delayAttack = 1500;
		break;
	}
	case RUNNING:
	{
		this->isActive = true;
		this->vy = this->dy = 0;
		this->vx = this->dx = (this->isReverse ? 0.1f : -0.1f);
		break;
	}
	case FALLING:
	{
		this->isActive = true;
		this->vy = -0.2f;
		this->vx = 0;
		break;
	}
	case ATTACKING: {
		this->vy = 0;
		this->vx = 0;
		//bulletType == 0: barrel
		if (this->health > 3) {
			if (bulletType == 0) {
				this->bullets = this->bulletCount = 1;
				this->curAnimation = animations[THROWING];
			}
			else {
				if (bulletCount < 0)
					this->bullets = this->bulletCount = 2;
				this->curAnimation = animations[ATTACKING];
			}
		}
		else {
			this->vx = this->dx = (this->isReverse ? 0.08f : -0.08f);
			this->bullets = this->bulletCount = 2;
			this->curAnimation = animations[ATTACKING];
		}
		break;
	}
	case DEAD:
	{
		this->vx = this->dx = 0;
		this->vy = this->dy = 0;
		this->posY = this->groundBound.rect.y + (this->width >> 1);
		//Sound::getInstance()->play("bossdie", true);
		break;
	}
	case INJURED:
	{
		if (this->health > 3) this->bulletType = 1;
		this->bullets = this->bulletCount = 2;
		break;
	}
	}


	//if (stateName != DEAD)
	//{
	//	
	//}
}

void EnemyMiniBoss::SubtractHealth()
{
	if (!flashingTime && health <= 3)
	{
		--this->health;
		flashColor = D3DCOLOR_ARGB(0, 255, 255, 255);
		if (this->health == 0)
		{
			//this->flashingTime = 3000;
			this->ChangeState(DEAD);
		}
		else
		{
			//--scoreboard->bossHealth;
			this->flashingTime = 2000;
		}
	}
	if (!flashingTime && health > 3) {
		--health;
		this->ChangeState(INJURED);
		this->flashingTime = 2000;
		flashColor = originalColor;

	}
}


void EnemyMiniBoss::CheckGroundCollision(std::unordered_set<Platform*> grounds)
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
	else if (!this->vy)
	{
		this->ChangeState(FALLING);
	}
}

void EnemyMiniBoss::Render(float cameraX, float cameraY)
{
	UpdateColor();
	if (this->stateName == DEAD) {
		this->isReverse = !this->isReverse;
	}
	screenX = this->posX - cameraX;
	screenY = cameraY - this->posY;
	curAnimation->isReverse = this->isReverse;
	curAnimation->AlphaRender(screenX, screenY, curColor, NULL);

}