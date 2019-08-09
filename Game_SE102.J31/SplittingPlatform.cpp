#include "SplittingPlatform.h"

SplittingPlatform::SplittingPlatform()
{
	animations[STANDING] = new Animation(ENEMY, 61);
	animations[RUNNING] = new Animation(ENEMY, 61);
	animations[ACTIVE] = new Animation(ENEMY, 62);
	tag = ENEMY;
	type = SPLITTING_PLATFORM;
	width = 32;
	height = 16;
	platform = new Platform();
	platform->type = 4;
	platform->rect = this->GetRect();
	curColor = originalColor;
}

void SplittingPlatform::UpdateDistance(float dt)
{
	switch (stateName) {
	case RUNNING:
	{
		if (delayTime > 0) {
			delayTime -= dt;
		}
		else {
			this->posX -= 32;
			this->flashingTime = 3000;
			ChangeState(ACTIVE);
		}
		break;
	}
	case ACTIVE: {
		if (flashingTime > 0) {
			flashingTime -= dt;
		}
		else {
			this->posX += 32;
			ChangeState(STANDING);
		}
		break;
	}
	}
}

void SplittingPlatform::Update(float dt)
{
	UpdateDistance(dt);
	this->platform->rect = this->GetRect();
}

void SplittingPlatform::Render(float cameraX, float cameraY)
{
	UpdateColor();
	screenX = this->posX - cameraX;
	screenY = cameraY - this->posY;
	curAnimation->isReverse = this->isReverse;
	if (stateName == ACTIVE) {
		Animation *temp =curAnimation;
		temp->AlphaRender(screenX + 64, screenY, curColor, NULL);
	}
	curAnimation->AlphaRender(screenX, screenY, curColor, NULL);
}

void SplittingPlatform::ChangeState(State StateName)
{
	switch (StateName)
	{
	case STANDING:
	{
		isActive = true;
		this->vx = this->dx = 0;
		this->vy = this->dy = 0;
		delayTime = 500;
		break;
	}

	case RUNNING:
	{
		this->isActive = true;
		this->isHasPlayerOn = true;
		this->width = 32;
		this->height = 16;
		break;
	}
	case ACTIVE: {
		this->width = 16;
		this->height = 16;
	}
	}
	this->stateName = StateName;
	this->curAnimation = animations[stateName];

}
