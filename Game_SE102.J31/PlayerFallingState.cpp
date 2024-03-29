﻿#include "PlayerFallingState.h"

// Khởi tạo State Falling
PlayerFallingState::PlayerFallingState()
{
	_reverse = player->isReverse;
	player->_allow[ATTACKING] = true;
	player->_allow[CLINGING] = true;
	player->_allow[THROWING] = false;
	player->_allow[SHIELD_UP] = false;
	player->vy = -PLAYER_FALLING_SPEED;
	player->height = PLAYER_STANDING_HEIGHT;
	StateName = FALLING;
}

// Nếu đã rơi xuống điểm va chạm -> _curState về trạng thái RUNNING
void PlayerFallingState::Update(float dt)
{
	if (player->vy == 0 )
	{
		player->ChangeState(new PlayerSittingState());
		return;
	}
	this->HandleKeyboard();
}

void PlayerFallingState::HandleKeyboard()
{
	if (!player->isOnGround) {
		if (keyCode[DIK_LEFT])
		{
			player->vx = _reverse ? -PLAYER_RUNNING_SPEED : -PLAYER_RUNNING_SPEED;
			player->isReverse = false;
		}

		else if (keyCode[DIK_RIGHT])
		{
			player->vx = _reverse ? PLAYER_RUNNING_SPEED : PLAYER_RUNNING_SPEED;
			player->isReverse = true;
		}
		else
		{
			player->vx = 0;
		}
		if (keyCode[DIK_DOWN] && player->_allow[SHIELD_DOWN]) {
			player->ChangeState(new PlayerShieldDownState());
		}
	}

}