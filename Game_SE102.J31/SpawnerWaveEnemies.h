#pragma once
#include "EnemyManager.h"
#include "BulletManager.h"
#include "Camera.h"
class SpawnerWaveEnemies {
private:
	int spawnedCount;
	int numPerSpawn;
	vector<Object*> spawnObjects;
public:
	int totalObjects;
	bool waveSpawn;
	bool isSpawning;
	SpawnerWaveEnemies();
	void Update(float dt);
	void Spawn();

};