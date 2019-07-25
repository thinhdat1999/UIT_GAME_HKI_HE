#pragma once
#include "Player.h"
#include <unordered_set>
#include <map>

class Weapon : public Object
{
protected:
	unordered_map<State, Animation*> animations;
	Animation *curAnimation;
	State stateName;
public:
	bool isOut, isBack;

	Weapon()
	{
		tag = WEAPON;
	}

	~Weapon()
	{
		if (type == SHIELD)
		{
			player->_allow[THROWING] = true;
		}
	}

	virtual void Update(float dt) {
		if (!isOut) {
			this->posX = player->posX;
			this->posY = player->posY;
			switch (player->stateName) {
			case SHIELD_UP:
				stateName = SHIELD_UP;
				this->posY += 16;
				this->posX += (player->isReverse ? 2 : -2);
				break;
			case SHIELD_DOWN:
				stateName = SHIELD_DOWN;
				break;
				// player->isOnGround == false -> JUMPING
			case JUMPING: case FALLING:
				stateName = JUMPING;
				this->posY = player->posY + 10;
				this->posX += (player->isReverse ? -5 : 5);
				break;
			case ATTACKING_SIT:
				stateName = JUMPING;
				this->posX += (player->isReverse ? -2 : 2);
				this->posY += -4;
				break;
			default:
				stateName = STANDING;
				this->posY += (player->stateName != SITTING) ? 6 : -4;
				this->posX += (player->isReverse ? 9 : -9);
				break;
			}
		}


		curAnimation = animations[stateName];
		curAnimation->isReverse = player->isReverse;
		curAnimation->Update(dt);

	}			// Update thông số của Object sau khoảng thời gian delta-time

	virtual void Render(float cameraX = 0, float cameraY = 0)
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

	virtual void Update(float dt, std::unordered_set<Object*> ColliableObjects)
	{
		UpdateDistance(dt);
		if (isOut)
		{
			stateName = SHIELD_UP;
			this->posX += dx;
			if (isBack) this->posY += dy;
		}
		//else {
		//	this->posX = player->posX;
		//	this->posY = player->posY;
		//	switch (player->stateName) {
		//	case SHIELD_UP:
		//		stateName = SHIELD_UP;
		//		this->posY += 16;
		//		this->posX += (player->isReverse ? 2 : -2);
		//		break;
		//	case SHIELD_DOWN:
		//		stateName = SHIELD_DOWN;
		//		break;
		//		// player->isOnGround == false -> JUMPING
		//	case JUMPING: case FALLING:
		//		stateName = JUMPING;
		//		this->posY = player->posY + 10;
		//		this->posX += (player->isReverse ? -5 : 5);
		//		break;
		//	default:
		//		stateName = STANDING;
		//		this->posY += (player->stateName != SITTING) ? 6 : -3;
		//		this->posX += (player->isReverse ? 11 : -11);
		//		break;
		//	}
		//}
	
		
		curAnimation = animations[stateName];
		curAnimation->isReverse = player->isReverse;
		curAnimation->Update(dt);
		
		auto rect = this->GetRect();
		for (auto obj : ColliableObjects)
		{
			if (rect.isContain(obj->GetRect()))
			{
				switch (obj->tag)
				{
				case HOLDER:
				{
					auto h = (Holder*)obj;
					h->isAttacked = true;
					break;
				}
				}
			}
		}
	}
};