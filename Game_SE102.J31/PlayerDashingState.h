#pragma once
#include "Player.h"
#include "PlayerState.h"

class PlayerDashingState : public PlayerState {
public:
	PlayerDashingState();
	void Update(float dt);
	void HandleKeyboard();
};