#pragma once
#include "Item.h"
#include "Camera.h"

class Holder : public Object
{
protected:
	Animation* animation;

public:
	bool isAttacked;
	int itemID;

	Holder() {}
	Holder(int itemID)
	{
		this->tag = HOLDER;
		this->width = HOLDER_WIDTH;
		this->height = HOLDER_HEIGHT;
		this->itemID = itemID;
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