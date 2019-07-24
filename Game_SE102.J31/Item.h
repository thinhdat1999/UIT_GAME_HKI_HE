#pragma once
#include "Object.h"
#include <unordered_set>

class Item : public Object
{
protected:
	float existsTime;
	Rect groundBound;
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

	void DetectGround(std::unordered_set<Rect*> grounds)
	{
		for (auto g : grounds)
		{
			Rect rect;
			rect.x = this->posX - (this->width >> 1);
			rect.y = g->y;
			rect.width = this->width;
			rect.height = this->height;

			if (rect.isContain(*g) && g->y >= groundBound.y && this->posY - (this->height >> 1) >= g->y)
			{
				groundBound = *g;
			}
		}
	}

	void Update(float dt)
	{
		if (this->IsCollide(groundBound))
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