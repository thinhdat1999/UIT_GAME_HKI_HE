#pragma once
#include "Scene.h"
#include "Player.h"
#include "SceneManager.h"
#include "WeaponShield.h"
#include "GameMap.h"
class PlayScene : public Scene
{
private:
	float _timeCounter;
	GameMap *mMap;
	int MapWidth, MapHeight;
	Player *p;
	Weapon *weapon;
	// Counter nhằm Update Scene sau một khoảng thời gian
public:

	PlayScene();		// Load các resources cần thiết để khởi tạo Scene
	~PlayScene();

	void LoadMap(const char *filePath);
	void Update(float dt);	// Update các thông số các đối tượng trong Scene
	void UpdateObject(float dt);
	void UpdatePlayer(float dt);
	void Render();									// Tải Scene lên màn hình
	void UpdateVisibleObjects();
	void OnKeyDown(int key);
	void OnKeyUp(int key);
};