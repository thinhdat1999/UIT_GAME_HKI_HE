#pragma once
#include <unordered_set>
#include <vector>
#include "Camera.h"
#include "Cell.h"
#include "Player.h"
#include "Holder.h"
#include "ItemManager.h"
#include "EnemyWizard.h"
#include "BulletManager.h"
#include <fstream>

class Grid
{
private:
	int rows;
	int columns;

public:
	Rect viewPort;
	Grid(int mapWidth, int mapHeight);
	~Grid();
	std::vector<std::vector<Cell*>> cells;
	std::vector<Cell*> visibleCells;
	std::unordered_set<Object*> respawnObjects;

	void Update();
	void RespawnEnemies();

	void MoveObject(Object* obj, float posX, float posY);
	void RemoveObject(Object* obj);
	void AddObject(Object* obj);
	void AddGround(Platform *g);
	void AddWall(Wall *w);
	void UpdateVisibleCells();

	std::unordered_set<Object*> GetVisibleObjects();
	std::unordered_set<Wall*> GetVisibleWalls();
	std::unordered_set<Platform*> GetVisibleGrounds();

	std::unordered_set<Wall*> GetColliableWalls(Object* obj);
	std::unordered_set<Platform*> GetColliableGrounds(Object* obj);
	std::unordered_set<Object*> GetColliableObjects(Object* obj);
};