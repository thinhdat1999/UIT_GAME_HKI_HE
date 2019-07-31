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
	//health = ENEMY_BOSS_HEALTH;
	//width = ENEMY_BOSS_WIDTH;
	//height = ENEMY_BOSS_HEIGHT;
	bullets = bulletCount = 3;
	delayDead = ENEMY_BOSS_DELAY_DEATH;
	delayHit = ENEMY_BOSS_DELAY_HIT;
	speed = delayJump = 0;
	firstJump = true;
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
		this->dx = 0;
		this->posX = ENEMY_BOSS_LEFT + (this->width >> 1);
	}
	else if (this->posX + (this->width >> 1) + dx >= ENEMY_BOSS_RIGHT)
	{
		this->dx = 0;
		this->posX = ENEMY_BOSS_RIGHT - (this->width >> 1);
	}
}

void EnemyWizard::UpdateState(float dt)
{
	switch (stateName) {
	case JUMPING:
	{
		this->vy -= GRAVITY_SPEED;

		if (this->vy <= 0)
		{
			this->ChangeState(ATTACKING_JUMP);
			return;
		}
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
			this->vx -= 0.03;
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
			this->vx += 0.03;
		}
		break;
	}
	case FALLING: {
		if (this->posY <= 70) {
			this->posY = 70;
			this->ChangeState(STANDING);
		}
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
	}
}

void EnemyWizard::Update(float dt)
{
	//if (isFrozenEnemies)
	//{
	//	this->dx = this->dy = 0;
	//}
	//else
	//{
	//	this->UpdateDistance(dt);
	//	curAnimation->Update(dt);
	//}
	if (flashingTime > 0) {
		flashingTime -= dt;
	}
	this->UpdateState(dt);
	this->UpdateDistance(dt);
	curAnimation->Update(dt);
	//if (delayHit)
	//{
	//	delayHit -= dt;
	//	if (delayHit <= 0)
	//	{
	//		delayHit = 0;
	//	}
	//}

	//if (this->stateName == DEAD)
	//{
	//	delayDead -= dt;

	//	/*if (isFrozenEnemies)
	//	{
	//		curAnimation->Update(dt);
	//	}*/

	//	if (delayDead <= 0)
	//	{
	//		this->isDead = true;
	//		this->isActive = false;
	//	}
	//}
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
		firstJump = false;
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
		this->isActive = true;
		this->vy = -0.3f;
		this->vx = 0;
		break;
	}
	case ATTACKING_JUMP:
	{
		this->vy = 0;
		this->vx = (this->isReverse ? 0.8f : -0.8f);
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
		//Sound::getInstance()->play("bossdie", true);
		break;
	}
	}

	this->stateName = StateName;

	if (stateName != DEAD)
	{
		this->curAnimation = animations[stateName];
	}
}

//void EnemyWizard::SubtractHealth()
//{
//	if (!delayHit)
//	{
//		--this->health;
//		--scoreboard->bossHealth;
//		this->delayHit = ENEMY_BOSS_DELAY_HIT;
//
//		if (this->health == 0)
//		{
//			this->ChangeState(DEAD);
//		}
//	}
//}

void EnemyWizard::Render(float cameraX, float cameraY)
{
	UpdateColor();
	screenX = this->posX - cameraX;
	screenY = cameraY - this->posY;
	curAnimation->isReverse = this->isReverse;
	curAnimation->AlphaRender(screenX, screenY, curColor);

}