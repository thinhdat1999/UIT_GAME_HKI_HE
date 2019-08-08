#pragma once
#include "Object.h"
#include <unordered_set>
#include "PlayerState.h"
#include "PlayerStandingState.h"
#include "PlayerJumpingState.h"
#include "PlayerShieldUpState.h"
#include "PlayerAttackingState.h"
#include "PlayerInjuredState.h"
#include "PlayerOnWaterState.h"
#include "Holder.h"
#include "BulletManager.h"
#include "Sound.h"

#include "ScoreBoard.h"
class Player : public Object
{
private:
	unordered_map<State, Animation*> animations;		// Danh sách các Animation tương ứng với từng State
	static Player* _instance;
	bool DetectGround(std::unordered_set<Platform*> grounds);
	bool DetectWall(std::unordered_set<Wall*> walls);
public:
	Player();
	~Player();

	static Player* GetInstance();

	int health, MaxHealth;
	int power;

	LPDIRECT3DTEXTURE9 curTexture;
	LPDIRECT3DTEXTURE9 originalTexture = TextureManager::GetInstance()->GetTexture(PLAYER);
	LPDIRECT3DTEXTURE9 flashTexture = TextureManager::GetInstance()->GetTexture(PLAYERFLASHING);
	Platform groundBound;
	Wall wallBound;
	PlayerState* state;
	State stateName;
	Animation* curAnimation;								// Animation hiện tại
	Type weaponType;
	bool isHasKey;
	unordered_map<State, bool> _allow;

	bool isThrowing, isAttacking, isHoldingShield;
	bool isOnGround, isOnWall, isOnWater, isOnMovingPlatform;
	int timeOfFirstButton, dashingTime;
	bool buttonPressed = false;
	int FirstButton;

	void Respawn();
	void DetectSpawnY(unordered_set<Platform*> grounds);
	void CheckGroundCollision(std::unordered_set<Platform*> grounds);
	void CheckWallCollision(std::unordered_set<Wall*> walls);
	void ChangeState(PlayerState* newState);
	void ChangeAnimation(State stateName);
	void Update(float dt, std::unordered_set<Object*> ColliableObjects);
	void UpdateTexture();
	void Render(float cameraX = 0, float cameraY = 0);
	void OnKeyDown(int keyCode);
	void OnKeyUp(int keyCode);

	void SetHealth(int health);
	void SetPower(int Power);
	void SetKey();
};