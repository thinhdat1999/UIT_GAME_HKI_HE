#pragma once
#include "Item.h"

class ItemFivePoint : public Item {
public:
	ItemFivePoint() {
		this->type = FIVEPOINT;
		this->animations[STANDING] = new Animation(ITEM, 0, 1, DEFAULT_TPF >> 1);
		this->curAnimation = animations[STANDING];
	}
};