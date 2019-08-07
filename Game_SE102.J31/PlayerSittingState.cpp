#include "PlayerSittingState.h"

// Khởi tạo trạng thái SITTING
PlayerSittingState::PlayerSittingState()
{
	player->_allow[JUMPING] = true;
	player->_allow[THROWING] = false;
	player->_allow[ATTACKING] = true;
	player->_allow[SHIELD_UP] = false;
	player->_allow[SHIELD_DOWN] = false;
	player->_allow[RUNNING] = true;
	player->vx = 0;
	player->vy = 0;
	player->posY -= 8;
	player->height = PLAYER_SITTING_HEIGHT;
	StateName = SITTING;
}

void PlayerSittingState::Update(float dt)
{
	this->HandleKeyboard();
}

// Xử lí sự kiện bàn phím cho trạng thái ngồi
void PlayerSittingState::HandleKeyboard()
{
	//check có thả nút Down ra không
	if (keyCode[DIK_LEFT] || keyCode[DIK_RIGHT])
	{
		player->height = PLAYER_STANDING_HEIGHT;
		player->posY += 8;
		player->ChangeState(new PlayerRunningState());
	}

	else if (!keyCode[DIK_DOWN])
	{
		player->height = PLAYER_STANDING_HEIGHT;
		player->posY += 8;
		player->ChangeState(new PlayerStandingState());
	}
	
}