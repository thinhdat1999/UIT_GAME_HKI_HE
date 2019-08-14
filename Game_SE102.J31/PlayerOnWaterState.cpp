#include "PlayerOnWaterState.h"

PlayerOnWaterState::PlayerOnWaterState()
{
	player->_allow[THROWING] = false;
	player->_allow[ATTACKING] = false;
	player->_allow[SHIELD_UP] = false;
	player->_allow[SHIELD_DOWN] = false;
	player->_allow[JUMPING] = true;
	player->height = PLAYER_SITTING_HEIGHT;
	player->vx = 0;
	player->vy = 0;
	StateName = WATER_FALLING;
	prevState = WATER_FALLING;
}

void PlayerOnWaterState::Update(float dt)
{
	player->vx = PLAYER_ONWATER_SPEED;
	player->posX += PLAYER_ONWATER_SPEED * dt;
	
	//if (this->StateName == WATER_FALLING && player->curAnimation->isLastFrame) {
	//	StateName = WATER_DIVING;
	//}
	//player->ChangeAnimation(StateName);
	this->HandleKeyboard();
}

void PlayerOnWaterState::HandleKeyboard()
{
	if (keyCode[DIK_LEFT])
	{
		player->isReverse = false;
		player->vx = PLAYER_ONWATER_SPEED * 1.5;
		player->ChangeAnimation(WATER_RUNNING);
		prevState = WATER_RUNNING;
	}

	else if (keyCode[DIK_RIGHT])
	{
		player->isReverse = true;
		player->vx = -PLAYER_ONWATER_SPEED * 2;
		player->ChangeAnimation(WATER_RUNNING);
		prevState = WATER_RUNNING;
	}
	else if (keyCode[DIK_UP] || !keyCode[DIK_DOWN]) {
		player->ChangeAnimation(ONWATER);
		prevState = ONWATER;
	}
	else if (keyCode[DIK_DOWN]) {
		if (prevState != WATER_DIVING && prevState != INWATER) {
			player->ChangeAnimation(WATER_DIVING);
			prevState = WATER_DIVING;
		}
		else if (prevState == WATER_DIVING && player->curAnimation->isLastFrame) {
			player->ChangeAnimation(INWATER);
			prevState = INWATER;
		}
	}
	else {
		if (prevState == WATER_RUNNING) {
			player->ChangeAnimation(WATER_FALLING);
			prevState = WATER_FALLING;
		}
		if (prevState == WATER_FALLING && player->curAnimation->isLastFrame) {
			player->ChangeAnimation(WATER_DIVING);
			prevState = WATER_DIVING;
		}
		else if (prevState == WATER_DIVING && player->curAnimation->isLastFrame) {
			player->ChangeAnimation(ONWATER);
			prevState = ONWATER;
		}
	}
}
