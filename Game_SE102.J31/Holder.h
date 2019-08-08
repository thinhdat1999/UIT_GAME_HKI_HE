#pragma once
#include "Object.h"
#include "Camera.h"
#include "ScoreBoard.h"
class Holder : public Object
{
protected:
	CSprite *sprite;
public:
	bool isAttacked, isActive;
	int itemID, maxItem;
	float delayDrop;
	bool isCanDrop;
	Holder() {
		this->tag = HOLDER;
		this->width = HOLDER_WIDTH;
		this->height = HOLDER_HEIGHT;
	}
	Holder(int itemID)
	{
		this->tag = HOLDER;
		this->width = HOLDER_WIDTH;
		this->height = HOLDER_HEIGHT;
		this->itemID = itemID;
		isActive = false;
		maxItem = 1;
		sprite = SpriteManager::GetInstance()->GetSprite(HOLDER, 1);
		//animations[ACTIVE] = new Animation(HOLDER, 0, 1, DEFAULT_TPF);
		isCanDrop = true;
	}

	~Holder()
	{
	}

	void Render(float cameraX = 0, float cameraY = 0)
	{
		screenX = this->posX - cameraX;
		screenY = cameraY - this->posY;
		if(isActive)
			sprite->Render(screenX, screenY);
	}

	void Update(float dt)
	{
		if (delayDrop > 0) {
			delayDrop -= dt;
		}
		else {
			isActive = false;
			delayDrop = 600;
			isCanDrop = true;
		}
		if (this->isAttacked) {
			isActive = true;
		}
		if (itemID == 6 && !scoreboard->isHasKey && maxItem == 0) {
			maxItem++;
		}
	}
};