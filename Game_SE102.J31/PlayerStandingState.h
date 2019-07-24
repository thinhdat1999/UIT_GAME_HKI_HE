#pragma once
#include "Player.h"
#include "PlayerState.h"
#include "PlayerSittingState.h"
#include "PlayerRunningState.h"

class PlayerStandingState : public PlayerState
{
public:
	PlayerStandingState();
	~PlayerStandingState() {}
	void Update(float dt);
	void HandleKeyboard();
};