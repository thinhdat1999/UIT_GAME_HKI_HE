#pragma once
#include "Item.h"

class ItemPowerStone : public Item {
public:
	ItemPowerStone() {
		this->type = POWERSTONE;
		this->sprite = SpriteManager::GetInstance()->GetSprite(ITEM, 2);
	}
};