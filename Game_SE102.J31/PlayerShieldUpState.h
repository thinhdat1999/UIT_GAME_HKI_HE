#pragma once
#include "Player.h"
#include "PlayerState.h"
#include "PlayerStandingState.h"
#include "PlayerRunningState.h"

class PlayerShieldUpState : public PlayerState
{
public:
	PlayerShieldUpState();
	void Update(float dt);
	void HandleKeyboard();
};