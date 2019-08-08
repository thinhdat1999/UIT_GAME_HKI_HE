#include "MapManager.h"

MapManager* MapManager::_instance = NULL;

void MapManager::LoadResources()
{
	for (int i = 1; i <= NUMBER_MAP_LEVEL; ++i)
	{
		_maps.push_back(new Map(i));
	}
}

Map * MapManager::GetMap(int level)
{
	return _maps[level - 1];
}

MapManager * MapManager::GetInstance()
{
	if (_instance == NULL)
		_instance = new MapManager();
	return _instance;
}