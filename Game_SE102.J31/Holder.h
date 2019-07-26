#pragma once
#include "Object.h"
#include "Camera.h"

class Holder : public Object
{
protected:
	unordered_map<State, Animation*> animations;
	Animation *curAnimation;
	State stateName;
public:
	bool isAttacked;
	int itemID;

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
		animations[STANDING] = new Animation(HOLDER, 0);
		animations[ACTIVE] = new Animation(HOLDER, 0, 1);
		curAnimation = animations[ACTIVE];
	}

	~Holder()
	{
	}

	void Render(float cameraX = 0, float cameraY = 0)
	{
		auto sprite = curAnimation->GetSprite(0);
		screenX = this->posX - cameraX;
		screenY = cameraY - this->posY;
		sprite->Render(screenX, screenY);
		curAnimation->Render(screenX, screenY);
	}

	void Update(float dt)
	{
		
	/*	if (player->curAnimation->isLastFrame && this->isAttacked) {
			stateName = ACTIVE;

		}*/
		if (this->isAttacked) {
			if (!this->curAnimation->isLastFrame)
				stateName = ACTIVE;
			else
				stateName = STANDING;
		}
		else 
			stateName = STANDING;
		curAnimation = animations[stateName];
		curAnimation->Update(dt);
	}
};