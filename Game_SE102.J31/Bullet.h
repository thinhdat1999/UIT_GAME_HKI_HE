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

public:
	State StateName;
	int bulletType;	
	Bullet()
	{
		this->tag = BULLET;
		deadAnimation = new Animation(WEAPON, 0, 2, 85);
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