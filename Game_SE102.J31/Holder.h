#pragma once
#include "Object.h"
#include "Camera.h"

class Holder : public Object
{
protected:
	Animation* animation;

public:
	bool isAttacked;
	int itemID;

	Holder() {
		this->tag = HOLDER;
		this->width = HOLDER_WIDTH;
		this->height = HOLDER_HEIGHT;
		animation = new Animation(ITEM, 0);
	}
	Holder(int itemID)
	{
		this->tag = HOLDER;
		this->width = HOLDER_WIDTH;
		this->height = HOLDER_HEIGHT;
		this->itemID = itemID;
		animation = new Animation(WEAPON, 0);
	}

	~Holder()
	{
	}

	void Render(float cameraX = 0, float cameraY = 0)
	{
		screenX = this->posX - cameraX;
		screenY = cameraY - this->posY;
		animation->Render(screenX, screenY);
	}

	void Update(float dt)
	{
		animation->Update(dt);
	}
};