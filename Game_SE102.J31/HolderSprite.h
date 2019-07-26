#pragma once
#pragma once
#include "Sprite.h"

class HolderSprite : public CSprite
{
public:
	HolderSprite() {};
	HolderSprite(State state, int left, int top, int right, int bottom)
	{
		this->tag = HOLDER;

		texture = TextureManager::GetInstance()->GetTexture(ENEMY);
		rect.top = top;
		rect.left = left;
		rect.right = right;
		rect.bottom = bottom;
		center = D3DXVECTOR3((right - left) >> 1, (bottom - top) >> 1, 0);
	}
};