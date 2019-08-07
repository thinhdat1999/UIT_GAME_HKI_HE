#include "PlayerJumpingState.h"

// Khởi tạo trạng thái JUMPING với Vector JUMPING dùng để giảm tốc
// Xem vận tốc ban đầu = -Gravity_Speed
PlayerJumpingState::PlayerJumpingState()
{
	_reverse = player->isReverse;
	player->_allow[ATTACKING] = true;
	player->_allow[CLINGING] = true;
	player->_allow[THROWING] = false;
	player->_allow[SHIELD_UP] = false;
	player->_allow[JUMPING] = false;
	holdingTime = 0;
	prevState = player->state->StateName;
	if (prevState == RUNNING || prevState == STANDING || prevState == CLINGING || prevState == SITTING || prevState == SHIELD_DOWN || prevState == ONWATER || prevState == WATER_FALLING) {
		player->height = PLAYER_STANDING_HEIGHT;
		player->vy = PLAYER_JUMPING_SPEED;
	}
	StateName = JUMPING;
}

void PlayerJumpingState::Update(float dt)
{
	// Cập nhật tốc độ vy đến khi vy >= 0 -> FALLING
	player->vy -= GRAVITY_SPEED;
	if (holdingTime <= 200) {
		holdingTime += dt;
	}

	if (player->vy <= 0)
	{
		player->ChangeState(new PlayerFallingState());
		return;
	}
	this->HandleKeyboard();
}

void PlayerJumpingState::HandleKeyboard()
{
	player->vx = 0;

	if (keyCode[DIK_LEFT])
	{
		player->isReverse = false;
		player->vx = _reverse ? -PLAYER_RUNNING_SPEED : -PLAYER_RUNNING_SPEED ;
	}

	else if (keyCode[DIK_RIGHT])
	{
		player->isReverse = true;
		player->vx = _reverse ? PLAYER_RUNNING_SPEED : PLAYER_RUNNING_SPEED;
	}
	if (keyCode[DIK_X]) {
		if (holdingTime < 200) {
			if(!player->groundBound.type != 2 || prevState == SHIELD_DOWN)
				player->vy += 0.02f;
		}
		else {
			if (player->groundBound.type != 2 || (prevState == SHIELD_DOWN))
   				player->ChangeState(new PlayerSpinningState());
		}
	}
}