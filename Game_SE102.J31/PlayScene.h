#pragma once
#include "Scene.h"
#include "Player.h"
#include "SceneManager.h"
#include "WeaponShield.h"
#include "GameMap.h"
#include "Grid.h"
#include "BulletManager.h"
#include "Sound.h"
#include "MapManager.h"

class PlayScene : public Scene
{
private:
	Grid *grid;
	Player *p;
	Weapon *weapon;
	Map *map;
	int level;
	Rect endRect;
	float delayRestart;
	std::unordered_set<Object*> visibleObjects;
	vector<Rect> lightbuttons;
	// Counter nhằm Update Scene sau một khoảng thời gian
public:

	// Load các resources cần thiết để khởi tạo Scene
	PlayScene(int level);
	~PlayScene();

	void Update(float dt);	// Update các thông số các đối tượng trong Scene
	void UpdateObjects(float dt);
	void UpdateVisibleObjects();
	void UpdatePlayer(float dt);
	void Render();									// Tải Scene lên màn hình
	void UpdateScene();

	void SetRestartScene();

	void RestartScene();
	void OnKeyDown(int key);
	void OnKeyUp(int key);
};