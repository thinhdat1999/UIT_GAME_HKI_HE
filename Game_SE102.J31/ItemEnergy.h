#pragma once
#include "Item.h"

class ItemEnergy : public Item {
public:
	ItemEnergy() {
		this->type = ENERGY;
		this->sprite = SpriteManager::GetInstance()->GetSprite(ITEM, 1);
	}
};