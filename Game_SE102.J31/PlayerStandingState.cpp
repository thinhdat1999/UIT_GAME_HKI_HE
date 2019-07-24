﻿#include "PlayerStandingState.h"

// Khởi tạo State đang đứng của nhân vật
PlayerStandingState::PlayerStandingState()
{
	player->vx = 0;
	player->vy = 0;
	player->_allow[RUNNING] = true;
	player->_allow[JUMPING] = true;
	player->_allow[SITTING] = true;
	StateName = STANDING;
	if (player->isHoldingShield) player->_allow[THROWING] = true;
}

void PlayerStandingState::Update(float dt)
{
	this->HandleKeyboard();
}

// Xử lí các sự kiện bàn phím cho nhân vật
void PlayerStandingState::HandleKeyboard()
{
	// Nhấn phím di chuyển -> RUNNING
	if (keyCode[DIK_LEFT] || keyCode[DIK_RIGHT])
	{
		player->ChangeState(new PlayerRunningState());
	}
	/* Nhấn phím DOWN -> SITTING*/
	else if (keyCode[DIK_DOWN])
	{
		player->ChangeState(new PlayerSittingState());
	}
}