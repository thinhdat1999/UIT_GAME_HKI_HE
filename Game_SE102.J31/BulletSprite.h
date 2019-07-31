#pragma once
#include "Sprite.h"

class BulletSprite : public CSprite
{
public:
	Type type;
	BulletSprite() {};

	BulletSprite(Type type, int left, int top, int right, int bottom)
	{
		this->tag = BULLET;
		this->type = type;
		switch (type) {
		case BOSS1:
			texture = TextureManager::GetInstance()->GetTexture(WIZARD);
			break;
		case BOSS2:
			texture = TextureManager::GetInstance()->GetTexture(MINIBOSS);
			break;
		default:
			texture = TextureManager::GetInstance()->GetTexture(ENEMY);
			break;
		}
		rect.top = top;
		rect.left = left;
		rect.right = right;
		rect.bottom = bottom;
		center = D3DXVECTOR3((right - left) >> 1, (bottom - top) >> 1, 0);
	}
};