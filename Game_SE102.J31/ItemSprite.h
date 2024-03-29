#pragma once
#include "Sprite.h"

class ItemSprite : public CSprite
{
public:
	Type type;
	ItemSprite() {};
	ItemSprite(Type type, int left, int top, int right, int bottom, int alpha = 255)
	{
		this->tag = ITEM;
		this->type = type;
		this->alpha = alpha;
		texture = TextureManager::GetInstance()->GetTexture(PLAYER);
		rect.top = top;
		rect.left = left;
		rect.right = right;
		rect.bottom = bottom;
		center = D3DXVECTOR3((right - left) >> 1, (bottom - top) >> 1, 0);
	}
};