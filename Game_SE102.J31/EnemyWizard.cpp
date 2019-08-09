#include "EnemyWizard.h"

EnemyWizard::EnemyWizard()
{
	animations[STANDING] = new Animation(ENEMY, 0);
	animations[RUNNING] = new Animation(ENEMY, 1, 4, DEFAULT_TPF >> 1);
	animations[INJURED] = new Animation(ENEMY, 5);
	animations[DEAD] = new Animation(ENEMY, 6, 7);
	animations[ATTACKING] = new Animation(ENEMY, 8, 11);
	animations[JUMPING] = new Animation(ENEMY, 12);
	animations[FALLING] = new Animation(ENEMY, 13);
	animations[ATTACKING_JUMP] = new Animation(ENEMY, 14);
	tag = ENEMY;
	type = BOSS1;
	health = 1;
	width = ENEMY_BOSS_WIDTH;
	height = ENEMY_BOSS_HEIGHT;
	bullets = bulletCount = 3;
	bulletCountdown = 3;
	delayHit = 3000;
	delayDead = ENEMY_BOSS_DELAY_DEATH;
	speed = 0;
	firstJump = false;
	bulletType = 0;
	curColor = originalColor;

}

void EnemyWizard::UpdateDistance(float dt)
{
	if (stateName == DEAD) return;

	//if (delayJump <= 0)
	//{
	//	--bulletCountdown;
	//	this->ChangeState(JUMPING);
	//	delayJump = ENEMY_BOSS_DELAY_JUMP;
	//}
	//else
	//{
	//	delayJump -= dt;
	//	if (stateName == JUMPING)
	//	{
	//		this->vy -= GRAVITY_SPEED;
	//	}

	//	if (this->posX - (this->width >> 1) + dx <= ENEMY_BOSS_LEFT)
	//	{
	//		this->dx = 0;
	//		this->posX = ENEMY_BOSS_LEFT + (this->width >> 1);
	//	}
	//	else if (this->posX + (this->width >> 1) + dx >= ENEMY_BOSS_RIGHT)
	//	{
	//		this->dx = 0;
	//		this->posX = ENEMY_BOSS_RIGHT - (this->width >> 1);
	//	}

	//	if (this->posY - (this->height >> 1) + dy < this->groundBound.y)
	//	{
	//		this->ChangeState(STANDING);
	//		this->posY = this->groundBound.y + (this->height >> 1);
	//	}
	//}
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

void EnemyWizard::UpdateState(float dt)
{
	switch (stateName) {
	case JUMPING:
	{
		//this->vy -= 0.002;
		if (this->posY + (this->height >> 1) + dy > 200)
		{
			this->posY = 206 - (this->height >> 1);
			this->vy = 0;
			this->ChangeState(ATTACKING_JUMP);
		}
		//if (this->vy <= 0)
		//{
		//	this->ChangeState(ATTACKING_JUMP);
		//	return;
		//}
		break;
	}
	case ATTACKING_JUMP:
	{
		// ----> isReverse = true
		if (isReverse) {
			if (vx > 0)
			{
				this->dx = max(-3.0f, this->dx);
			}
			else {
				this->ChangeState(FALLING);
			}
			this->vx -= 0.002;
		}
		// <---- isReverse = false
		else {
			if (this->vx < 0)
			{
				this->dx = min(3.0f, this->dx);
			}
			else {
				this->ChangeState(FALLING);
			}
			this->vx += 0.002;
		}
		break;
	}
	case FALLING: {
		if (this->vy == 0 /*&& firstJump*/)
			this->ChangeState(STANDING);
		break;
	}
	case STANDING:
	{
		this->ChangeState(RUNNING);
		break;
	}
	case RUNNING:
	{
		this->vx = (this->isReverse ? 0.02f : -0.02f);
		if (curAnimation->isLastFrame == true) {
			this->ChangeState(ATTACKING);
		}
		break;
	}
	case ATTACKING:
	{
		if (bulletCount == 1) 
			this->bulletType = 1;
		break;
	}
	case INJURED:
	{
		this->vy -= GRAVITY_SPEED;
		//if (this->posY <= 70) {
		//	this->posY = 70;
		//	this->ChangeState(STANDING);
		//}
		break;
	}
	}
}

void EnemyWizard::Update(float dt)
{
	if (gameLevel == 3) {
		originalColor = D3DCOLOR_XRGB(0, 0, 0);
		flashColor = D3DCOLOR_XRGB(0, 0, 0, 0);
	}
	else {
		originalColor = D3DCOLOR_XRGB(255, 255, 255);
		flashColor = D3DCOLOR_ARGB(0, 255, 255, 255);
	}
	if (flashingTime > 0) {
		flashingTime -= dt;
	}
	else {
		flashingTime = 0;
	}
	this->UpdateState(dt);
	this->UpdateDistance(dt);
	curAnimation->Update(dt);

	if (this->stateName == DEAD)
	{
		delayDead -= dt;

		/*if (isFrozenEnemies)
		{
			curAnimation->Update(dt);
		}*/

		if (delayDead <= 0)
		{
			this->isDead = true;
			this->isActive = false;
		}
	}
}

void EnemyWizard::ChangeState(State StateName)
{
	switch (StateName)
	{
	case STANDING:
	{
		this->isReverse = !(player->posX < this->posX);
		this->vx = this->dx = 0;
		this->vy = this->dy = 0;
		break;
	}

	case RUNNING:
	{
		this->isActive = true;
		this->vy = this->dy = 0;
		/*this->vx = this->dx = 0.02f;*/
		break;
	}

	case JUMPING:
	{
		this->vy = ENEMY_BOSS_JUMP_SPEED;
		this->vx = 0;
		break;
	}
	case FALLING:
	{
		/*if (firstJump)
		{*/
			this->isActive = true;
			this->vy = -0.2f;
			this->vx = 0;
		//}
		break;
	}
	case ATTACKING_JUMP:
	{
		this->vy = 0;
		this->vx = (this->isReverse ? 0.25f : -0.25f);
		this->bullets = this->bulletCount = 1;
		this->bulletType = 2;
		break;
	}
	case ATTACKING: {
		this->vy = 0;
		this->vx = 0;
		this->bullets = this->bulletCount = 3;
		this->bulletType = 0;
		break;
	}
	case DEAD:
	{
		this->vx = this->dx = 0;
		this->vy = this->dy = 0;
		this->posY = this->groundBound.rect.y + (this->width >>1);
		//Sound::getInstance()->play("bossdie", true);
		break;
	}
	case INJURED:
	{
		this->vx = this->dx = (this->isReverse ? -0.02f : 0.02f);
		this->vy = 0.15f;
		break;
	}
	}

	this->stateName = StateName;
	this->curAnimation = animations[stateName];
	//if (stateName != DEAD)
	//{
	//	
	//}
}

void EnemyWizard::SubtractHealth()
{
	if (!flashingTime)
	{
		--this->health;
		//--scoreboard->bossHealth;
		this->flashingTime = 2000;

		if (this->health == 0)
		{
			this->flashingTime = 3000;
			this->ChangeState(DEAD);
		}
		else this->ChangeState(INJURED);
	}
}


void EnemyWizard::CheckGroundCollision(std::unordered_set<Platform*> grounds)
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

void EnemyWizard::Render(float cameraX, float cameraY)
{
	UpdateColor();
	screenX = this->posX - cameraX;
	screenY = cameraY - this->posY;
	curAnimation->isReverse = this->isReverse;
	curAnimation->AlphaRender(screenX, screenY, curColor, NULL);

}