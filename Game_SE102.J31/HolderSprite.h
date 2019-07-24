#pragma once
#pragma once
#include "Sprite.h"

class HolderSprite : public CSprite
{
public:
	Type type;
	HolderSprite() {};
	HolderSprite(Type type, int left, int top, int right, int bottom)
	{
		this->tag = HOLDER;
		this->type = type;

		texture = TextureManager::GetInstance()->GetTexture(tag);
		rect.top = top;
		rect.left = left;
		rect.right = right;
		rect.bottom = bottom;
		center = D3DXVECTOR3((right - left) >> 1, (bottom - top) >> 1, 0);
	}
};