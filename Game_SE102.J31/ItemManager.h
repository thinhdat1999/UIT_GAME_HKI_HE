#pragma once
#include "ItemFivePoints.h"
#include "ItemEnergy.h"
#include "ItemPowerStone.h"

class ItemManager {
public:
	ItemManager() {}
	~ItemManager() {}
	static Item *CreateItem(int type) {
		switch (type) {
		case 1:
			return new ItemFivePoint();
		case 2:
			return new ItemEnergy();
		case 3:
			return new ItemPowerStone();
		default: 
			return NULL;
		}
	}
};