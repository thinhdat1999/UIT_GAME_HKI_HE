#pragma once
#include "Object.h"
#include "Camera.h"
#include <unordered_set>

class Bullet : public Object
{
protected:
	Animation* activeAnimation;
	Animation* deadAnimation;
	Animation* curAnimation;
	Platform groundBound;
public:
	bool isOnGround;
	State StateName;
	int bulletType;	
	Bullet()
	{
		this->tag = BULLET;
		deadAnimation = new Animation(PLAYER, 20, 22, 85);
	}

	~Bullet()
	{
	}

	void Render(float cameraX = 0, float cameraY = 0)
	{
		screenX = this->posX - cameraX;
		screenY = cameraY - this->posY;
		curAnimation->isReverse = this->isReverse;
		curAnimation->Render(screenX, screenY);
	}

	virtual void UpdateDistance(float dt)
	{
		this->dx = vx * dt;
		this->dy = vy * dt;
	}

	virtual void Update(float dt)
	{
	/*	if (isFrozenEnemies)
		{
			this->dx = this->dy = 0;
		}
		else
		{
			this->UpdateDistance(dt);
			curAnimation->Update(dt);
		}*/
		this->UpdateDistance(dt);
		curAnimation->Update(dt);
		if (this->StateName == DEAD)
		{
			this->dx = this->dy = 0;

			/*if (isFrozenEnemies)
			{
				curAnimation->Update(dt);
			}*/

			if (curAnimation->isLastFrame)
			{
				this->isDead = true;
			}
		}
	}
	virtual void ChangeType(int type) {}
	virtual bool DetectGround(std::unordered_set<Platform*> grounds) {
		auto rbp = this->GetRect();					//rect broading-phase
		auto bottom = rbp.y - rbp.height;
		rbp.y = rbp.y + dy;
		rbp.height = rbp.height - dy;

		if (rbp.isContain(groundBound.rect) && (bottom >= groundBound.rect.y))
			return true;

		for (auto g : grounds)
		{
			if (rbp.isContain(g->rect) && (bottom >= g->rect.y))
			{
				groundBound = *g;
				return true;
			}
		}
		return false;
	}
	virtual bool CheckGround(std::unordered_set<Platform*> grounds) {
		auto rbp = this->GetRect();					//rect broading-phase
		auto bottom = rbp.y - rbp.height;
		rbp.y = rbp.y + dy;
		rbp.height = rbp.height - dy;
		for (auto g : grounds)
		{
			if (rbp.isContain(g->rect) && g->type != 6)
			{
				groundBound = *g;
				return true;
			}
		}
		return false;
	}
	virtual void CheckGroundCollision(std::unordered_set<Platform*> grounds) {
		// Trên không
		if (this->vy)
		{
			this->isOnGround = false;
		}
		// Tìm được vùng đất va chạm
		if (DetectGround(grounds))
		{
			if (this->vy < 0)
			{
				this->isOnGround = true;
				this->vy = this->dy = 0;
				this->posY = groundBound.rect.y + (this->height >> 1);
			}
		}
	}
	void ChangeState(State StateName)
	{
		this->StateName = StateName;

		switch (StateName)
		{
		case ACTIVE:
		{
			curAnimation = activeAnimation;
			this->isDead = false;
			break;
		}

		case DEAD:
		{
			curAnimation = deadAnimation;
			break;
		}
		}
	}
};