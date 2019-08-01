#pragma once
#include "Item.h"

class ItemPowerStoneBig : public Item {
public:
	ItemPowerStoneBig() {
		this->type = POWERSTONEX10;
		this->animations[STANDING] = new Animation(ITEM, 5, 6, DEFAULT_TPF >> 1);
		this->curAnimation = animations[STANDING];
	}
};