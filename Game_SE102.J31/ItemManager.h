#pragma once
#include "ItemFivePoints.h"
#include "ItemEnergy.h"
#include "ItemPowerStone.h"
#include "ItemEnergyBig.h"
#include "ItemPowerStoneBig.h"
#include "ItemKey.h"


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
			return new ItemEnergyBig();
		case 4:
			return new ItemPowerStone();
		case 5:
			return new ItemPowerStoneBig();
		case 6: 
			return new ItemKey();
		default: 
			return NULL;
		}
	}
};