#pragma once
#include "Item.h"

class ItemKey : public Item {
public:
	ItemKey() {
		this->type = KEY;
		this->animations[STANDING] = new Animation(ITEM, 7, 8, DEFAULT_TPF >> 1);
		this->curAnimation = animations[STANDING];
	}
};