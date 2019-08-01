#pragma once
#include "Item.h"

class ItemEnergy : public Item {
public:
	ItemEnergy() {
		this->type = ENERGY;
		this->animations[STANDING] = new Animation(ITEM, 1);
		this->curAnimation = animations[STANDING];
	}
};