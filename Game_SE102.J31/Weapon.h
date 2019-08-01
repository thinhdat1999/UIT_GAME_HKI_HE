#pragma once
#include "Player.h"
#include "EnemyManager.h"
#include <unordered_set>
#include <map>

class Weapon : public Object
{
protected:
	unordered_map<State, Animation*> animations;
	Animation *curAnimation;
	State stateName;
public:
	bool isOut, isBack, isRender;

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
		curAnimation = animations[stateName];
		curAnimation->isReverse = player->isReverse;

		if (!isOut) {
			this->posX = player->posX;
			this->posY = player->posY;
			switch (player->stateName) {
			case SHIELD_UP:
				stateName = SHIELD_UP;
				this->posY += 16;
				this->posX += (player->isReverse ? 2 : -2);
				isRender = true;
				break;
			case SHIELD_DOWN:
				stateName = SHIELD_DOWN;
				isRender = true;
				break;
				// player->isOnGround == false -> JUMPING
			case JUMPING: case FALLING:
				stateName = JUMPING;
				this->posY = player->posY + 10;
				this->posX += (player->isReverse ? -5 : 5);
				isRender = true;
				break;
			case ATTACKING_JUMP:
				stateName = STANDING;
				this->posX += (player->isReverse ? -18 : 18);
				isRender = true;
				break;
			case ATTACKING_SIT:
				stateName = JUMPING;
				this->posX += (player->isReverse ? -2 : 2);
				this->posY += -4;
				isRender = true;
				break;
			case SPINNING:
				isRender = false;
				break;
			default:
				stateName = STANDING;
				this->posY += (player->stateName != SITTING) ? 6 : -4;
				this->posX += (player->isReverse ? 9 : -9);
				isRender = true;
				break;
			}
		}
		curAnimation->Update(dt);
	}			// Update thông số của Object sau khoảng thời gian delta-time

	virtual void Render(float cameraX = 0, float cameraY = 0)
	{
		screenX = this->posX - cameraX;
		screenY = cameraY - this->posY;
		curAnimation->isReverse = this->isReverse;
		if (isRender)
			curAnimation->Render(screenX, screenY);
		else
			curAnimation->AlphaRender(screenX, screenY, D3DCOLOR_ARGB(0, 255, 255, 255), NULL);
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
				case ENEMY:
				{
					if (obj->type != BOSS1)
					{
						auto e = (Enemy*)obj;
						e->ChangeState(DEAD);
					}
					else
					{
						auto e = (EnemyWizard*)obj;
						e->SubtractHealth();

					}
					break;
				}
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