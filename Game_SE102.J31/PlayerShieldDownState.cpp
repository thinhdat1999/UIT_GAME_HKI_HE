#include "PlayerShieldDownState.h"

// Khởi tạo trạng thái JUMPING với Vector JUMPING dùng để giảm tốc
// Xem vận tốc ban đầu = -Gravity_Speed
PlayerShieldDownState::PlayerShieldDownState()
{
	_reverse = player->isReverse;
	player->_allow[ATTACKING] = true;
	player->_allow[CLINGING] = true;
	player->_allow[THROWING] = false;
	player->_allow[JUMPING] = true;
	player->_allow[SHIELD_DOWN] = false;
	player->vy = -PLAYER_FALLING_SPEED;
	player->height = PLAYER_SITTING_HEIGHT;
	StateName = SHIELD_DOWN;
}

void PlayerShieldDownState::Update(float dt)
{
	//if (player->isOnGround) {
	//	player->ChangeState(new PlayerStandingState());
	//	return;
	//}
	this->HandleKeyboard();
}

void PlayerShieldDownState::HandleKeyboard()
{
	player->vx = 0;

	if (!player->isOnGround) {
		if (keyCode[DIK_LEFT])
		{
			player->isReverse = false;
			player->vx = _reverse ? -PLAYER_RUNNING_SPEED : -PLAYER_RUNNING_SPEED;
			return;
		}

		else if (keyCode[DIK_RIGHT])
		{
			player->isReverse = true;
			player->vx = _reverse ? PLAYER_RUNNING_SPEED : PLAYER_RUNNING_SPEED;
			return;
		}
		if (!keyCode[DIK_DOWN]) {
			player->height = PLAYER_STANDING_HEIGHT;
			player->ChangeState(new PlayerFallingState());

		}
	}
	//Khi ngồi trên đất-> đi, đứng, 
	else {
		if (keyCode[DIK_LEFT] || keyCode[DIK_RIGHT])
		{
			player->height = PLAYER_STANDING_HEIGHT;
			player->posY += 8;
			player->ChangeState(new PlayerRunningState());
		}
		else if(keyCode[DIK_UP] || !keyCode[DIK_DOWN])
		{
			player->height = PLAYER_STANDING_HEIGHT;
			player->posY += 8;
			player->ChangeState(new PlayerStandingState());
		}
	}

}