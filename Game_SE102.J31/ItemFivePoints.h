#pragma once
#include "Item.h"

class ItemFivePoint : public Item {
public:
	ItemFivePoint() {
		this->type = FIVEPOINT;
		this->sprite = SpriteManager::GetInstance()->GetSprite(ITEM, 0);
	}
};