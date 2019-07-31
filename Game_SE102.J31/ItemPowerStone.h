#pragma once
#include "Item.h"

class ItemPowerStone : public Item {
public:
	ItemPowerStone() {
		this->type = POWERSTONE;
		this->animations[STANDING] = new Animation(ITEM, 3);
		this->curAnimation = animations[STANDING];
	}
};