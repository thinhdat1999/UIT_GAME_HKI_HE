#include "MovingPlatform.h"

MovingPlatform::MovingPlatform()
{
	animations[STANDING] = new Animation(ENEMY, 63);
	animations[RUNNING] = new Animation(ENEMY, 63);
	tag = ENEMY;
	type = MOVING_PLATFORM;
	width = 32;
	height = 16;
	typeAI = 0;
	//speed = 0.1f;
	platform = new Platform();
	platform->type = 3;
	platform->rect = this->GetRect();
	curColor = originalColor;
}

void MovingPlatform::UpdateDistance(float dt)
{
	this->dx = this->vx * dt;
	this->dy = this->vy /** dt*/;

	switch (stateName) {
	case STANDING: {
		this->dx = 0;
		this->dy = 0;
		if (delayTime > 0) {
			delayTime -= dt;
		}
		else {
			this->ChangeState(RUNNING);
		}
		break;
	}
	case RUNNING:
	{
		// TypeAI: 
		// 0: di chuyển ngang
		// 1: di chuyển xéo
		// 2: di chuyển tròn 
		oldPosY = posY;
		switch (typeAI) {
		case 0:
			if (((this->vx < 0) && (this->posX - this->spawnX < -maxDistanceX))
				|| ((this->vx > 0) && (this->posX - this->spawnX > maxDistanceX)))
			{
				this->vx = -this->vx;
				this->vy = 0;
				this->ChangeState(STANDING);
			}
			break;
		case 1:
			if (((this->vx < 0) && (this->posX - this->spawnX < -maxDistanceX))
				|| ((this->vx > 0) && (this->posX - this->spawnX > maxDistanceX))
				|| ((this->vy > 0) && (this->posY - this->spawnY > maxDistanceY))
				|| ((this->vy < 0) && (this->posY - this->spawnY < -maxDistanceY))) {
				this->vx = -this->vx;
				this->vy = -this->vy;
				this->ChangeState(STANDING);
			}
			break;
		case 2:
			this->dx = (cos(angle) * 0.1f * dt) / 2;
			this->dy = (sin(angle) * 1.0f);
			angle += 0.02f;
			if (angle >= 360) {
				angle = 0;
			}
			break;

		}
		break;
	}
	}
}

void MovingPlatform::Update(float dt)
{
	UpdateDistance(dt);
	this->platform->rect = this->GetRect();
	this->platform->type = 3;
	this->platform->dx = this->dx;
	this->platform->dy = this->dy;
}

void MovingPlatform::Render(float cameraX, float cameraY)
{
	screenX = this->posX - cameraX;
	screenY = cameraY - this->posY;
	SpriteManager::GetInstance()->GetSprite(ENEMY, 63)->AlphaRender(screenX, screenY, curColor, NULL);
}

void MovingPlatform::ChangeState(State StateName)
{
	switch (StateName)
	{
	case STANDING:
	{
		isActive = true;
		delayTime = 300;
		break;
	}
	case RUNNING: {
		isActive = true;
		break;
	}
	}
	this->stateName = StateName;
	this->curAnimation = animations[stateName];

}
