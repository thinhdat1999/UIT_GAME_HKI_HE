#include "PlayerSittingState.h"

// Khởi tạo trạng thái SITTING
PlayerSittingState::PlayerSittingState()
{
	player->_allow[JUMPING] = false;
	player->_allow[THROWING] = false;
	player->_allow[ATTACKING] = true;
	player->vx = 0;
	player->vy = 0;
	player->posY -= 8;
	player->height -= 8;
	StateName = SITTING;
}

void PlayerSittingState::Update(float dt)
{
	this->HandleKeyboard();
}

// Xử lí sự kiện bàn phím cho trạng thái ngồi
void PlayerSittingState::HandleKeyboard()
{
	if (!keyCode[DIK_DOWN])
	{
		player->_allow[JUMPING] = true;
		player->height += 8;
		player->posY += 8;

		if (keyCode[DIK_LEFT] || keyCode[DIK_RIGHT])
		{
			player->ChangeState(new PlayerRunningState());
		}
		else
		{
			player->ChangeState(new PlayerStandingState());
		}
		player->ChangeState(new PlayerStandingState());
	}
}