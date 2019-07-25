#pragma once
#include "Object.h"
#include <unordered_set>

class Item : public Object
{
protected:
	float existsTime;
	Platform groundBound;
	CSprite* sprite;

public:
	Item()
	{
		this->tag = ITEM;
		this->existsTime = ITEM_EXISTS_TIME;
		this->vy = -ITEM_SPEED;
		this->width = ITEM_WIDTH;
		this->height = ITEM_HEIGHT;
	}

	void DetectGround(std::unordered_set<Platform*> grounds)
	{
		for (auto g : grounds)
		{
			Platform pf;
			pf.rect.x = this->posX - (this->width >> 1);
			pf.rect.y = g->rect.y;
			pf.rect.width = this->width;
			pf.rect.height = this->height;

			if (pf.rect.isContain(g->rect) && g->rect.y >= groundBound.rect.y && this->posY - (this->height >> 1) >= g->rect.y)
			{
				groundBound = *g;
			}
		}
	}

	void Update(float dt)
	{
		if (this->IsCollide(groundBound.rect))
		{
			this->vy = 0;
			this->dy = 0;
		}
		else this->dy = vy * dt;

		existsTime -= dt;

		if (existsTime <= 0)
		{
			this->isDead = true;
		}
	}

	void Render(float cameraX = 0, float cameraY = 0)
	{
		screenX = this->posX - cameraX;
		screenY = cameraY - this->posY;
		sprite->Render(screenX, screenY);
	}
};