#include "PlayerDashingState.h"

PlayerDashingState::PlayerDashingState()
{
	player->vx = player->isReverse ? PLAYER_RUNNING_SPEED * 2 : -PLAYER_RUNNING_SPEED * 2;
	player->_allow[JUMPING] = true;
	player->vy = 0;
	if (player->isHoldingShield)
		player->_allow[THROWING] = true;
	StateName = DASHING;
	player->dashingTime = 400;
}

void PlayerDashingState::Update(float dt)
{
	this->HandleKeyboard();
	if (player->dashingTime > 0) {
		player->dashingTime -= dt;
	}
	else {
		player->ChangeState(new PlayerStandingState());
	}
}

void PlayerDashingState::HandleKeyboard()
{
	if (keyCode[DIK_RIGHT])
	{
		player->isReverse = true;
		player->vx = PLAYER_RUNNING_SPEED *2;
	}
	else if (keyCode[DIK_LEFT])
	{
		player->isReverse = false;
		player->vx = -PLAYER_RUNNING_SPEED*2;
	}
	else if (keyCode[DIK_SPACE]) {
		player->ChangeState(new PlayerJumpingState());
	}
	else {
		player->ChangeState(new PlayerStandingState());
	}
}
