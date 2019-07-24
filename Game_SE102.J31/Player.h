#pragma once
#include "Object.h"
#include <unordered_set>
#include "PlayerState.h"
#include "PlayerStandingState.h"
#include "PlayerJumpingState.h"
#include "PlayerShieldUpState.h"
#include "PlayerAttackingState.h"

class Player : public Object
{
private:
	unordered_map<State, Animation*> animations;		// Danh sách các Animation tương ứng với từng State
	static Player* _instance;
	bool DetectGround(std::unordered_set<Rect*> grounds);
	bool DetectWall(std::unordered_set<Wall*> walls);
public:
	Player();
	~Player();

	static Player* GetInstance();

	Rect groundBound;
	Wall wallBound;
	PlayerState* state;
	State stateName;
	Animation* curAnimation;								// Animation hiện tại
	Type weaponType;
	unordered_map<State, bool> _allow;
	bool isThrowing, isAttacking, isHoldingShield;
	bool isOnGround, isOnWall;


	void Respawn();
	void CheckGroundCollision(std::unordered_set<Rect*> grounds);
	void CheckWallCollision(std::unordered_set<Wall*> walls);
	void ChangeState(PlayerState* newState);
	void Update(float dt);
	void Render(float cameraX = 0, float cameraY = 0);
	void OnKeyDown(int keyCode);
	void OnKeyUp(int keyCode);
};