#pragma once
#include "Item.h"

class ItemEnergyBig : public Item {
public:
	ItemEnergyBig() {
		this->type = ENERGYX10;
		this->animations[STANDING] = new Animation(ITEM, 2);
		this->curAnimation = animations[STANDING];
	}
};