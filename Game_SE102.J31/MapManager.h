#pragma once
#include "Map.h"

class MapManager
{
private:
	std::vector<Map*> _maps;
	static MapManager* _instance;

public:
	void LoadResources();
	Map* GetMap(int level);
	static MapManager* GetInstance();
};