#include "SpawnerWaveEnemies.h"

void SpawnerWaveEnemies::Update(float dt)
{
	if (isSpawning) {
		if (spawnedCount >= totalObjects) {
			isSpawning = false;
			
		}
		else {
			Spawn();
		}
	}
}

void SpawnerWaveEnemies::Spawn()
{
	spawnedCount++;

}
