#pragma once
#include "Scene.h"
#include "Player.h"
#include "SceneManager.h"
#include "WeaponShield.h"
#include "GameMap.h"
#include "Grid.h"

class PlayScene : public Scene
{
private:
	Grid *grid;
	GameMap *mMap;
	Player *p;
	Weapon *weapon;
	
	

	float _timeCounter;	
	int MapWidth, MapHeight;
	std::unordered_set<Object*> visibleObjects;
	// Counter nhằm Update Scene sau một khoảng thời gian
public:

	PlayScene();		// Load các resources cần thiết để khởi tạo Scene
	~PlayScene();

	void LoadMap(const char *filePath);
	void Update(float dt);	// Update các thông số các đối tượng trong Scene
	void UpdateObjects(float dt);
	void UpdatePlayer(float dt);
	void Render();									// Tải Scene lên màn hình
	void UpdateVisibleObjects();
	void OnKeyDown(int key);
	void OnKeyUp(int key);
};