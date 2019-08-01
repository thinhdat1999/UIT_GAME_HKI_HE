#pragma once
#include "Object.h"
#include <unordered_set>

class Item : public Object
{
protected:
	float existsTime;
	Platform groundBound;
	unordered_map<State, Animation*> animations;
	Animation *curAnimation;
	State stateName;
	D3DCOLOR originalColor = D3DCOLOR_XRGB(255, 255, 255);
	D3DCOLOR flashColor = D3DCOLOR_ARGB(0, 255, 255, 255);
	D3DCOLOR curColor;

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
		if (existsTime <= 1200 && flashingTime <= 0) {
			this->flashingTime = 1200;
		}
		if (flashingTime > 0) {
			flashingTime -= dt;
		}
		if (existsTime <= 0)
		{
			this->isDead = true;
		}
		curAnimation = animations[stateName];
		curAnimation->Update(dt);
	}
	void UpdateColor() {
		if (flashingTime > 0) {
			if (curColor == flashColor) {
				curColor = originalColor;
			}
			else {
				curColor = flashColor;
			}
		}
		else curColor = originalColor;
	}

	void Render(float cameraX = 0, float cameraY = 0)
	{
		UpdateColor();
		screenX = this->posX - cameraX;
		screenY = cameraY - this->posY;
		curAnimation->AlphaRender(screenX, screenY, curColor, NULL);
	}
};